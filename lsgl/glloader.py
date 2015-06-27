
#!/usr/bin/python

__author__ = 'Miles Lacey'

import os
import re
import jinja2


#------------------------------------------------------------------------------
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

    _INCLUDE_PATH_PATTERN = re.compile(r'\bGL(ES)?(\d?)\\gl(\d{1,2})?\.h$')
    # Match group 0 Determines the OpenGL header include path
    # Match group 1 Finds the OpenGL folder (None for GL, or 'ES' for GLES)
    # Match group 2 Identifies the GLES major version ('', '2', or '3')
    # Match group 3 Finds the GLES minor version ('2', '3', or '31')

    def __init__(self, gl_path):
        self.include = None  # Formatted as <GL[ES[2,3]]/gl[2,3,31].h>
        self.include_path = None  # Absolute or relative path to gl[2,3].h
        self.folder = None  # Formatted as GL[ES[2,3]]
        self.version = None  # One of GL_DESKTOP, or a GL_ES_# variant
        self.ext_include = None  # Formatted as <GL[ES[2,3]]/gl[2,3]ext.h>
        self.ext_path = None  # Absolute or relative path to gl[2,3]ext.h

        self._parse_gl_header(gl_path)
        self._parse_gl_ext_header(gl_path)

    def _parse_gl_header(self, gl_path):
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

        assert self.version is not None, "OpenGL header path not found in %r!" % gl_path
        self.include_path = gl_path

    def _parse_gl_ext_header(self, gl_path):
        self.ext_include = self.include

        if self.version != GLHeaderInfo.GL_DESKTOP:
            version = GLHeaderInfo.GL_ES_2
        else:
            version = GLHeaderInfo.GL_DESKTOP

        prefix = self.include[:self.include.rindex('l') + 1]
        self.ext_include = '%s%sext.h>' % (prefix, version)

        prefix = gl_path[:gl_path.rindex('l') + 1]
        self.ext_path = '%s%sext.h' % (prefix, version)

    def _parse_desktop_header(self, folder='GL'):
        self.folder = folder
        self.version = GLHeaderInfo.GL_DESKTOP

    def _parse_mobile_header(self, folder, maj_ver, min_ver):
        if not maj_ver:
            assert not min_ver, 'OpenGL ES 1.0 header not found!'
            self.version = GLHeaderInfo.GL_ES_1

        elif maj_ver == GLHeaderInfo.GL_ES_2:
            assert min_ver ==GLHeaderInfo. GL_ES_2, \
                'OpenGL ES 2.0 header not found!'
            self.version = GLHeaderInfo.GL_ES_2

        elif maj_ver == GLHeaderInfo.GL_ES_3:
            if min_ver == GLHeaderInfo.GL_ES_3:
                self.version = GLHeaderInfo.GL_ES_3

            elif min_ver == GLHeaderInfo.GL_ES_3_1:
                self.version = GLHeaderInfo.GL_ES_3_1
            assert self.version, 'OpenGL ES 3.0 or 3.1 header not found!'

        self.folder = folder


#------------------------------------------------------------------------------
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
        """
        with open(filename, 'rb') as f:
            lines = f.readlines()
        return lines

    @staticmethod
    def write_gl_loader_sources(out_folder, inc_data, src_data):
        """
        Write all header and source file information to a folder, specified at
        runtime.
        """
        def write_data(folder, extension, data):
            with open('%s/lsgl%s' % (folder, extension), 'wb') as f:
                f.write(data)

        write_data(out_folder, '.h', inc_data)
        write_data(out_folder, '.c', src_data)


#------------------------------------------------------------------------------
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
        for ext in self.blacklist:
            if gl_func.endswith(ext):
                return True

    def _get_gl_api_funcs(self, file_lines):
        functions = []
        in_ext_block = False
        func_api_pattern = re.compile(r'(?<=APIENTRY\ )(\w+)(?=\ \()')
        # Matches the name of an OpenGL function within an OpenGL header file.

        for line in file_lines:
            if line.startswith('#ifdef GL_GLEXT_PROTOTYPES'):
                in_ext_block = True
                continue

            # Only function prototypes within the "GL_GLEXT_PROTOTYPES" #define
            # blocks should be retrieved. Otherwise the resulting loader library
            # will redeclare functions provided by the OS.
            if (line.startswith('#endif') and in_ext_block) or not in_ext_block:
                in_ext_block = False
                continue

            match = func_api_pattern.search(line)

            if not match:
                continue

            func = match.group(0)

            if not self._is_ext_blacklisted(func):
                functions.append(func)

        return functions

    def generate_loadfile(self, gl_header_path, out_folder):
        info = GLHeaderInfo(gl_header_path)
        funcs = GLLoaderIO.load_gl_header(gl_header_path)
        ext_funcs = GLLoaderIO.load_gl_header(info.ext_path)

        gl_funcs = self._get_gl_api_funcs(funcs + ext_funcs)
        cwd = os.path.abspath(os.path.dirname(__file__))
        pkg = jinja2.FileSystemLoader('%s/templates' % cwd, encoding='ascii')
        env = jinja2.Environment(loader=pkg)

        def populate_template(extension):
            tmp_file = 'lsgl_template%s' % extension
            template = env.get_template(tmp_file)
            return template.render(glheader=info.include,
                                   glextheader=info.ext_include,
                                   glfolder=info.folder,
                                   glversion=info.version,
                                   glfunctions=gl_funcs)

        inc_data = populate_template('.h')
        src_data = populate_template('.c')
        GLLoaderIO.write_gl_loader_sources(out_folder, inc_data, src_data)

#------------------------------------------------------------------------------
PROGRAM_NAME = 'glloader'

PROGRAM_DESC = 'The LSGL command-line utility can be used to generate an ' \
               'OpenGL loader library using only the path to an OpenGL ' \
               'header file.'

PROGRAM_USAGE = """glloader.py [-h] -i PATH_TO_GL_HEADER [-o OUTPUT_DIRECTORY] [-w WHITELISTED_EXTENSIONS]

-i/--input:     The input parameter should be the absolute or relative path to
                your OpenGL header file. For example:
                    -i /usr/include/GL/gl.h
                    -i /usr/include/GLES2/gl2.h
                This directory should also contain the appropriate GL/glext.h
                (or GLES2/gl2ext.h, or similar) header file containing OpenGL
                extensions provided by Khronos.

-o/--output     The absolute or relative path to a directory which will contain
                a generated source and header file. These files can be used to
                dynamically load all standardized OpenGL functions available
                on a machine at runtime.

-w/--whitelist  Remove one or more vendor extensions from the list of
                blacklisted vendor-specific OpenGL functions. Vendor-specific
                functions are disabled by default in order to provide a uniform
                set of standardized OpenGL functions across all target
                platforms. For example, passing '-i /usr/include/GLES2/gl2.h
                -w EXT ARB' will allow all available OpenGL functions suffixed
                with 'EXT' or 'ARB' (contained within
                '/usr/include/GLES2/gl2ext.h') to appear in the generated
                'lsgl.h' and 'lsgl.c' source files. The default blacklist
                includes the following extensions (as function suffixes):\n
                %s

-h              Print this help documentation.

""" % '\n                '.join(GLLoader().blacklist)

#------------------------------------------------------------------------------
def run_command_line():
    import argparse

    default_output = os.path.abspath(os.path.dirname(__file__)) + '/build'
    default_output = default_output.replace('\\', '/')

    parser = argparse.ArgumentParser(prog=PROGRAM_NAME,
                                     description=PROGRAM_DESC,
                                     usage=PROGRAM_USAGE)

    parser.add_argument('-i', '--input', nargs=1, required=True, type=str)
    parser.add_argument('-o', '--output', nargs=1, default=default_output,
                        type=str)
    parser.add_argument('-w', '--whitelist', nargs='*', type=str)

    args = parser.parse_args()

    if not args.input:
        parser.print_usage()
        return

    i = args.input if isinstance(args.input, str) else args.input[0]
    o = args.output if isinstance(args.output, str) else args.output[0]

    print "Generating an OpenGL loading library."
    print "Input header file:   %r." % i
    print "Output directory:    %r." % o

    loader = GLLoader()
    if args.whitelist:
        print "OpenGL extensions white-listed: ", args.whitelist
        for extension in args.whitelist:
            loader.blacklist.remove(extension)

    loader.generate_loadfile(i, o)

    print "OpenGL extension loading library generated!"

if __name__ == '__main__':
    run_command_line()
