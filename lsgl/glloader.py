#!/bin/env python3

import os
import re
import jinja2


__author__ = 'Miles Lacey'


# -----------------------------------------------------------------------------
def expand_abspath(path):
    return os.path.abspath(os.path.expanduser(path))


# -----------------------------------------------------------------------------
class GLHeaderInfo:
    """
    This class helps contain all basic information about an OpenGL header
    passed into the program. It can be used to determine if the output extension
    library is using desktop or mobile GL, along with its version info.
    """
    # Some strings which should help during parsing
    GL_DESKTOP = ''
    GL_ES_1 = ''
    GL_ES_2 = '2'
    GL_ES_3 = '3'
    GL_ES_3_1 = '31'
    GL_ES_3_2 = '32'

    _INCLUDE_PATH_PATTERN = re.compile(
        r'\bGL(ES)?(\d?)[\\/]gl(corearb|\d+)?\.h$')
    # Match group 0 Determines the OpenGL header include path
    # Match group 1 Finds the OpenGL folder (None for GL, or 'ES' for GLES)
    # Match group 2 Identifies the GLES major version ('', '2', or '3')
    # Match group 3 Finds the GLES minor version ('2', '3', or '31')

    def __init__(self, gl_path):
        gl_path = expand_abspath(gl_path)

        self.include = None  # Formatted as <GL[ES[2,3]]/gl[2,3,31].h>
        self.include_path = None  # Absolute or relative path to gl[2,3].h
        self.folder = None  # Formatted as GL[ES[2,3]]
        self.version = None  # One of GL_DESKTOP, or a GL_ES_# variant
        self.ext_include = None  # Formatted as <GL[ES[2,3]]/gl[2,3]ext.h>
        self.ext_path = None  # Absolute or relative path to gl[2,3]ext.h

        self._parse_gl_header(gl_path)
        self._parse_gl_ext_header(gl_path)

    def _parse_gl_header(self, gl_path):
        """
        Parse an OpenGL header or extension header file located at a particular
        path on the filesystem. Once parsed, an instance of this class will
        know the include path, extension path, and version of the OpenGL
        header.

        :param gl_path:
        An absolute or relative path to a location on the local filesystem
        which represents an OpenGL header file (such as <GL/gl.h>.
        """
        match = GLHeaderInfo._INCLUDE_PATH_PATTERN.search(gl_path)
        header = match.group(0)
        platform = match.group(1)  # desktop or mobile
        maj_ver = match.group(2)
        min_ver = match.group(3)

        include_err = "Could not parse the OpenGL [ES] version from %r."
        assert header, include_err % gl_path

        self.include = ('<%s>' % header).replace('\\', '/')

        # break early if Desktop GL was found
        if platform != 'ES':
            self._parse_desktop_header()
        else:
            folder = 'GL%s%s' % (platform, maj_ver)
            self._parse_mobile_header(folder, maj_ver, min_ver)

        assert self.version is not None, \
            "OpenGL header path not found in %r!" % gl_path
        self.include_path = gl_path

    def _parse_gl_ext_header(self, gl_path):
        """
        Similar to GLLoader._parse_gl_header(...), this function parses an
        OpenGL extension header in order to place extension functions into an
        output C header/source file.

        :param gl_path:
        An absolute or relative path to a location on the local filesystem
        which represents an OpenGL extension header file (such as <GL/glext.h>.
        """
        self.ext_include = self.include
        am_gles3 = False

        if self.version == GLHeaderInfo.GL_DESKTOP:
            version = GLHeaderInfo.GL_DESKTOP
        elif self.version == GLHeaderInfo.GL_ES_1:
            version = GLHeaderInfo.GL_ES_1
        else:
            version = GLHeaderInfo.GL_ES_2
            am_gles3 = self.version is not GLHeaderInfo.GL_ES_2

        prefix = self.include[:self.include.rindex('l') + 1]
        self.ext_include = '%s%sext.h>' % (prefix, version)

        prefix = gl_path[:gl_path.rindex('l') + 1]
        self.ext_path = '%s%sext.h' % (prefix, version)

        # GLES 3+ extension headers are located in the GLES2 directory
        if am_gles3:
            gles3_index_a = self.ext_include.rfind('GLES3')
            gles3_index_b = self.ext_path.rfind('GLES3')
            self.ext_include = \
                self.ext_include[:gles3_index_a] +\
                'GLES2' + \
                self.ext_include[gles3_index_a+5:]
            self.ext_path = \
                self.ext_path[:gles3_index_b] + \
                'GLES2' + \
                self.ext_path[gles3_index_b+5:]

    def _parse_desktop_header(self, folder='GL'):
        """
        Helper function to get meta-information about an OpenGL desktop header.

        :param folder:
        A relative or absolute path to a folder on the local filesystem which
        contains an OpenGL-desktop header.
        """
        self.folder = folder
        self.version = GLHeaderInfo.GL_DESKTOP

    def _parse_mobile_header(self, folder, maj_ver, min_ver):
        """
        Helper function to get meta-information about an OpenGL[ES] mobile
        header.

        :param folder:
        A relative or absolute path to a folder on the local filesystem which
        contains an OpenGL[ES]-mobile header.
        """

        if not maj_ver:
            assert not min_ver, 'OpenGL ES 1.0 header not found!'
            self.version = GLHeaderInfo.GL_ES_1

        elif maj_ver == GLHeaderInfo.GL_ES_2:
            assert min_ver == GLHeaderInfo. GL_ES_2, \
                'OpenGL ES 2.0 header not found!'
            self.version = GLHeaderInfo.GL_ES_2

        elif maj_ver == GLHeaderInfo.GL_ES_3:
            if min_ver == GLHeaderInfo.GL_ES_3:
                self.version = GLHeaderInfo.GL_ES_3

            elif min_ver == GLHeaderInfo.GL_ES_3_1:
                self.version = GLHeaderInfo.GL_ES_3_1

            elif min_ver == GLHeaderInfo.GL_ES_3_2:
                self.version = GLHeaderInfo.GL_ES_3_2
            assert self.version, 'OpenGLES 3.0, 3.1, and 3.2 headers not found!'

        self.folder = folder


# -----------------------------------------------------------------------------
class GLLoaderIO:
    """
    This class is simply responsible for reading/Writing any file data regarding
    OpenGL.
    """
    def __init__(self):
        pass

    @staticmethod
    def load_gl_header(filename):
        """
        Load an OpenGL header file and return its contents as a list of strings.

        :param filename:
        A relative or absolute path to an OpenGL header file (such as <GL/gl.h>

        :return: A list of strings which contain each line of the input header
        file.
        """
        filename = expand_abspath(filename)

        with open(filename, 'r') as f:
            lines = f.readlines()

        return lines

    @staticmethod
    def write_gl_loader_sources(out_folder, inc_data, src_data):
        """
        Write all header and source file information to a folder, specified at
        runtime.

        :param out_folder:
        A string containing the output folder which the generated OpenGL source
        files will be placed.

        :param inc_data:
        A string containing the generated OpenGL function loader data which
        will be placed into a C header file.

        :param src_data:
        A string containing the generated OpenGL function loader data which
        will be placed into a C source file.
        """
        def write_data(folder, extension, data):
            folder = expand_abspath(folder)
            if not os.path.isdir(folder):
                os.mkdir(folder)
            with open('%s/lsgl%s' % (folder, extension), 'w') as f:
                f.write(data)

        write_data(out_folder, '.h', inc_data)
        write_data(out_folder, '.c', src_data)


# -----------------------------------------------------------------------------
class GLLoader:
    """
    The GLLoader class is the meat and potatoes of this program. Once an OpenGL
    header has been parsed, this class will manage the output of all header and
    source file data which can be used as an OpenGL extension loader library.
    """
    def __init__(self):
        self.blacklist = [
            '3DFX',
            '3DLABS',
            'AGL',
            'AMD',
            'ANGLE',
            'APPLE',
            'ARB',
            'ATI',
            'EXT',
            'HP',
            'I3D',
            'IBM',
            'IMG',
            'INGR',
            'INTEL',
            'KHR',
            'GREMEDY',
            'MESA',
            'MTX',
            'NV',
            'NVX',
            'OES',
            'OVR',
            'PGI',
            'QCOM',
            'OML',
            'SGI',
            'SGIS',
            'SGIX',
            'SUN',
            'SUNX',
        ]

    def _is_ext_blacklisted(self, gl_func):
        """
        Determine if an OpenGL extension type is blacklisted from the list of
        all available functions contained within an instance of this class.

        :param gl_func:
        A string containing the suffix of an OpenGL extension (such as EXT,
        ARB, AMD, etc).

        :return: True if the extension is currently blacklisted, None if not.
        By default, all OpenGL extensions are blacklisted in order to provide
        the most portable set of OpenGL functions possible.
        """
        gl_func = gl_func.upper()

        exts = [ext for ext in self.blacklist if gl_func.endswith(ext)]
        return True if exts else False

    def _get_gl_api_funcs(self, info, file_lines):
        """
        Parse a loaded OpenGL header file and return all of the functions
        contained within it.

        :param file_lines:
        A list of strings containing all of the individual lines of an OpenGL
        header file.

        :return:
        A list of strings containing only the function declarations extracted
        from an OpenGL header file.
        """
        functions = []
        in_sys_block = False
        in_ext_block = False
        func_api_pattern = re.compile(r'(?<=APIENTRY )(\w+)(?= \()')
        define_count = 0

        if info.version is GLHeaderInfo.GL_DESKTOP:
            ext_define = '#ifdef GL_GLEXT_PROTOTYPES'
            sys_block = [
                '#ifndef GL_VERSION_1_0',
                '#ifndef GL_VERSION_1_1',
                '#ifndef GL_VERSION_1_2',
                '#ifndef GL_VERSION_1_3',
                '#ifndef GL_VERSION_1_4',
            ]
        else:
            ext_define = ''  # '#if GL_GLES_PROTOTYPES'
            sys_block = []

        # Matches the name of an OpenGL function within an OpenGL header file.

        for line in file_lines:
            if line.strip() in sys_block:
                define_count = define_count+1
                in_sys_block = True
                continue

            if line.strip() == ext_define:
                define_count = define_count+1
                in_ext_block = True
                continue

            if line.startswith('#ifdef') and in_sys_block:
                define_count = define_count+1
                continue

            # Only function prototypes within the "GL_GLEXT_PROTOTYPES" #define
            # blocks should be retrieved. Otherwise the resulting loader library
            # will redeclare functions provided by the OS.
            if line.startswith('#endif') and in_sys_block:
                define_count = define_count-1

                if not define_count:
                    in_sys_block = False
                continue

            if in_sys_block or not in_ext_block:
                continue

            match = func_api_pattern.search(line)

            if not match:
                continue

            func = match.group(0)

            if not self._is_ext_blacklisted(func) and func not in functions:
                functions.append(func)

        return functions

    def generate_loadfile(self, gl_header_path, out_folder):
        """
        Create a C header and source file which can be used to load a set of
        OpenGL functions contained within a user-provided OpenGL header file
        (such as <GL/gl.h>).

        :param gl_header_path:
        The absolute or relative path to an OpenGL header file.

        :param out_folder:
        The absolute or relative path to a folder which will contain the output
        C header and source files.
        """
        gl_header_path = expand_abspath(gl_header_path)
        out_folder = expand_abspath(out_folder)

        info = GLHeaderInfo(gl_header_path)
        funcs = GLLoaderIO.load_gl_header(gl_header_path)
        ext_funcs = GLLoaderIO.load_gl_header(info.ext_path)

        if 'corearb' in info.include:
            gl_funcs = self._get_gl_api_funcs(info, funcs)
        else:
            gl_funcs = self._get_gl_api_funcs(info, funcs+ext_funcs)

        cwd = os.path.abspath(os.path.dirname(__file__))
        pkg = jinja2.FileSystemLoader('%s/templates' % cwd, encoding='ascii')
        env = jinja2.Environment(loader=pkg)

        def populate_template(extension):
            tmp_file = 'lsgl_template%s' % extension
            template = env.get_template(tmp_file)
            return template.render(glheader=info.include,
                                   glextheader=info.ext_include,
                                   glfolder='GL',
                                   glversion=info.version,
                                   glfunctions=gl_funcs)

        inc_data = populate_template('.h')
        src_data = populate_template('.c')
        GLLoaderIO.write_gl_loader_sources(out_folder, inc_data, src_data)
