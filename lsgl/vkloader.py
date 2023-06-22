#!/bin/env python3

import os
import re
import jinja2


__author__ = 'Miles Lacey'


# -----------------------------------------------------------------------------
def expand_abspath(path):
    return os.path.abspath(os.path.expanduser(path))


# -----------------------------------------------------------------------------
class VKHeaderInfo:
    """
    This class helps contain all basic information about a Vulkan header passed
    into the program, along with its version info.
    """
    # Some strings which should help during parsing
    VULKAN_1_0 = '1_0'
    VULKAN_1_1 = '1_1'
    VULKAN_1_2 = '1_2'
    VULKAN_1_3 = '1_3'

    _INCLUDE_PATH_PATTERN = re.compile(r'\b(vulkan)[\\/](vulkan_core\.h)$')

    def __init__(self, vk_path):
        vk_path = expand_abspath(vk_path)

        self.include = None  # Formatted as 'vulkan_core.h'
        self.include_path = None  # Absolute or relative path to vulkan_core.h
        self.folder = None  # Formatted as 'vulkan'
        self.version_maj = 1
        self.version_min = 0

        self._parse_gl_header(vk_path)


    def _parse_gl_header(self, vk_path):
        """
        Parse a Vulkan header. Once parsed, an instance of this class will know
        the include path and version of the Vulkan header.
        header.

        :param vk_path:
        An absolute or relative path to a location on the local filesystem
        which represents the vulkan_core.h header file.
        """
        match = VKHeaderInfo._INCLUDE_PATH_PATTERN.search(vk_path)
        folder = match.group(1)
        header = match.group(2)

        include_err = "Could not parse the Vulkan version from %r."
        assert header and folder, include_err % vk_path

        self.include_path = os.path.realpath(vk_path)
        self.include = header
        self.folder = folder


# -----------------------------------------------------------------------------
class VKLoaderIO:
    """
    This class is simply responsible for reading/Writing any file data regarding
    Vulkan.
    """
    def __init__(self):
        pass

    @staticmethod
    def load_vk_header(filename):
        """
        Load a Vulkan header file and return its contents as a list of strings.

        :param filename:
        A relative or absolute path to the vulkan_core.h header file.

        :return: A list of strings which contain each line of the input header
        file.
        """
        filename = expand_abspath(filename)

        with open(filename, 'r') as f:
            lines = f.readlines()

        return lines


    @staticmethod
    def write_vk_loader_sources(out_folder, inc_data, src_data):
        """
        Write all header and source file information to a folder, specified at
        runtime.

        :param out_folder:
        A string containing the output folder which the generated OpenGL source
        files will be placed.

        :param inc_data:
        A string containing the generated vulkan function loader data which
        will be placed into a C header file.

        :param src_data:
        A string containing the generated vulkan function loader data which
        will be placed into a C source file.
        """
        def write_data(folder, extension, data):
            folder = expand_abspath(folder)
            if not os.path.isdir(folder):
                os.mkdir(folder)
            with open('%s/lsvk%s' % (folder, extension), 'w') as f:
                f.write(data)

        write_data(out_folder, '.h', inc_data)
        write_data(out_folder, '.c', src_data)


# -----------------------------------------------------------------------------
class VKLoader:
    """
    The GLLoader class is the meat and potatoes of this program. Once an OpenGL
    header has been parsed, this class will manage the output of all header and
    source file data which can be used as an OpenGL extension loader library.
    """
    def __init__(self):
        self.blacklist = [
            'AMD',
            'ANDROID',
            'ARM',
            'EXT',
            'FUSCHIA',
            'GGP',
            'GOOGLE',
            'INTEL',
            'KHR',
            'LUNARG',
            'HUAWEI',
            'IMG',
            'MVK',
            'NV',
            'NVX',
            'NN',
            'QCOM',
            'QNX',
            'SEC',
            'VALVE',
        ]

    def _is_ext_blacklisted(self, vk_func):
        """
        Determine if a Vulkan extension type is blacklisted from the list of
        all available functions contained within an instance of this class.

        :param vk_func:
        A string containing the suffix of a Vulkan extension (such as EXT, KHR,
        NV, etc).

        :return: True if the extension is currently blacklisted, None if not.
        By default, all Vulkan extensions are blacklisted in order to provide
        the most portable set of functions possible.
        """
        vk_func = vk_func.upper()

        exts = [ext for ext in self.blacklist if vk_func.endswith(ext)]
        return True if exts else False

    def _get_vk_api_funcs(self, info, file_lines):
        """
        Parse a loaded OpenGL header file and return all the functions
        contained within it.

        :param file_lines:
        A list of strings containing all the individual lines of an Vulkan
        header file.

        :return:
        A list of strings containing only the function declarations extracted
        from an OpenGL header file.
        """
        functions = set()
        in_ext_block = False
        func_api_pattern = re.compile(r'\(VKAPI_PTR\s+\*PFN_(vk[a-zA-Z0-9_-]+)\)')
        func_arg_pattern = re.compile(r'\(VKAPI_PTR\s+\*PFN_vk[a-zA-Z0-9_-]+(\)\(.+\));')
        version_pattern = re.compile(r'(VK_VERSION_(\d+)_(\d+))')
        handle_pattern = re.compile(r'VK_DEFINE_HANDLE\((Vk[a-zA-Z0-9_-]+)\)')
        handle_types = set()
        typed_funcs = {'global': set()}
        define_count = 0
        version_maj = 1
        version_min = 0

        ext_define = '#ifndef VK_NO_PROTOTYPES'
        sys_block = [
            '#define VK_VERSION_1_0',
            '#define VK_VERSION_1_1',
            '#define VK_VERSION_1_2',
            '#define VK_VERSION_1_3',
        ]

        # Matches the name of an OpenGL function within an OpenGL header file.

        for line in file_lines:
            if line.strip() in sys_block:
                match = version_pattern.search(line)
                version_maj = int(match.group(0))
                version_min = int(match.group(1))
                continue

            if line.strip() == ext_define:
                define_count = define_count+1
                in_ext_block = True
                continue

            # Only function prototypes outside the "VK_NO_PROTOTYPES" #ifdef
            # blocks should be retrieved. Otherwise the resulting loader library
            # will include pre-declared functions provided by the header.
            if line.startswith('#endif') and in_ext_block:
                define_count = define_count-1

                if not define_count:
                    in_ext_block = False
                continue

            if in_ext_block:
                continue

            handle_match = handle_pattern.search(line)
            if handle_match:
                handle = handle_match.group(1)
                handle_types.add(handle)
                typed_funcs[handle] = set()
                continue

            func_name_match = func_api_pattern.search(line)
            if not func_name_match:
                continue

            func = func_name_match.group(1)
            if self._is_ext_blacklisted(func):
                continue
            functions.add(func)

            args_match = func_arg_pattern.search(line)
            args = args_match.group(1) if args_match else ''

            for handle in handle_types:
                if f')({handle} ' in args:
                    typed_funcs[handle].add(func)
                    break
            else:
                typed_funcs['global'].add(func)

        self.version_maj = version_maj
        self.version_min = version_min
        return functions, typed_funcs

    def generate_loadfile(self, vk_header_path, out_folder):
        """
        Create a C header and source file which can be used to load a set of
        Vulkan functions contained within a user-provided header file.

        :param vk_header_path:
        The absolute or relative path to an OpenGL header file.

        :param out_folder:
        The absolute or relative path to a folder which will contain the output
        C header and source files.
        """
        vk_header_path = expand_abspath(vk_header_path)
        out_folder = expand_abspath(out_folder)

        info = VKHeaderInfo(vk_header_path)
        funcs = VKLoaderIO.load_vk_header(vk_header_path)

        if info.include.endswith('_core.h'):
            vk_funcs, vk_typed_funcs = self._get_vk_api_funcs(info, funcs)

        cwd = os.path.abspath(os.path.dirname(__file__))
        pkg = jinja2.FileSystemLoader('%s/templates' % cwd, encoding='ascii')
        env = jinja2.Environment(loader=pkg)

        def populate_template(extension):
            tmp_file = 'lsvk_template%s' % extension
            template = env.get_template(tmp_file)
            return template.render(vkheader=info.include,
                                   vkfolder='vulkan',
                                   vkfunctions=vk_funcs,
                                   vktypedfuncs=vk_typed_funcs)

        inc_data = populate_template('.h')
        src_data = populate_template('.c')
        VKLoaderIO.write_vk_loader_sources(out_folder, inc_data, src_data)
