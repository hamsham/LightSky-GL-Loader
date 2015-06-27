
#!/usr/bin/python

__author__ = 'Miles Lacey'

import os
import re
import jinja2

_INCLUDE_PATH_PATTERN = re.compile(r'\bGL(ES)?(\d?)\\gl(\d{1,2})?\.h$')
# match.group(0) Determines the OpenGL header include path
# match.group(1) Locates the OpenGL folder (None for GL, or 'ES' for GLES)
# match.group(2) Identifies the GLES major version ('', '2', or '3')
# match.group(3) Finds the GLES minor version ('2', '3', or '31')

_INCLUDE_EXT_PATH_PATTERN = re.compile(r'\bGL(ES)?(\d?)\\gl\d?ext\.h$')
# for glext.h/gl2ext.h headers

_FUNCTION_API_PATTERN = re.compile(r'(?<=APIENTRY\ )(\w+)(?=\ \()')
# Matches the name of an OpenGL function within an OpenGL header file.

_EXTENSION_BLACKLIST = [
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

""" % '\n                '.join(_EXTENSION_BLACKLIST)

GL_DESKTOP = ''
GL_ES_1 = ''
GL_ES_2 = '2'
GL_ES_3 = '3'
GL_ES_3_1 = '31'


class GLHeaderInfo:
    def __init__(self, gl_path):
        self.include = None
        self.include_path = None
        self.folder = None
        self.version = None
        self.ext_include = None
        self.ext_path = None
        self._parse_gl_header_path(gl_path)
        self._load_gl_extension_header(gl_path)

    def _load_gl_extension_header(self, gl_path):
        self.ext_include = self.include
        version = '2' if self.version != GL_DESKTOP else ''
        prefix = self.include[:self.include.rindex('l') + 1]
        self.ext_include = '%s%sext.h>' % (prefix, version)

        prefix = gl_path[:gl_path.rindex('l') + 1]
        self.ext_path = '%s%sext.h' % (prefix, version)

    def _parse_gl_header_path(self, gl_path):
        match = _INCLUDE_PATH_PATTERN.search(gl_path)
        header = match.group(0)
        platform = match.group(1)
        maj_ver = match.group(2)
        min_ver = match.group(3)

        include_err = "Could not parse the OpenGL [ES] version from %r."
        assert header, include_err % gl_path

        self.include = ('<%s>' % header).replace('\\', '/')

        # break early if Desktop GL was found
        if platform != 'ES':
            self.folder = 'GL'
            self.version = GL_DESKTOP
            return

        if not maj_ver:
            assert not min_ver, 'OpenGL ES 1.0 header not found!'
            self.version = GL_ES_1

        elif maj_ver == GL_ES_2:
            assert min_ver == GL_ES_2, 'OpenGL ES 2.0 header not found!'
            self.version = GL_ES_2

        elif maj_ver == GL_ES_3:
            if min_ver == GL_ES_3:
                self.version = GL_ES_3

            elif min_ver == GL_ES_3_1:
                self.version = GL_ES_3_1

            assert self.version, 'OpenGL ES 3.0 or 3.1 header not found!'

        assert self.version, "OpenGL header path not found!"
        self.folder = 'GL%s%s' % (platform, maj_ver)
        self.include_path = gl_path


class GLLoader:
    def __init__(self):
        pass

    @staticmethod
    def _load_gl_header(filename):
        with open(filename, 'rb') as f:
            lines = f.readlines()
        return lines

    @staticmethod
    def _get_gl_api_funcs(file_lines):
        functions = []
        is_prototype = False

        for line in file_lines:
            if line.startswith('#ifdef GL_GLEXT_PROTOTYPES'):
                is_prototype = True
                continue

            if (line.startswith('#endif') and is_prototype) or not is_prototype:
                is_prototype = False
                continue

            match = _FUNCTION_API_PATTERN.search(line)

            if not match:
                continue

            func = match.group(0)

            blacklisted = False
            for ext in _EXTENSION_BLACKLIST:
                if func.endswith(ext):
                    blacklisted = True
                    break

            if not blacklisted:
                functions.append(func)

        return functions

    @staticmethod
    def _write_loader_files(out_folder, inc_data, src_data):
        def write_data(folder, extension, data):
            with open('%s/lsgl%s' % (folder, extension), 'wb') as f:
                f.write(data)

        write_data(out_folder, '.h', inc_data)
        write_data(out_folder, '.c', src_data)

    @staticmethod
    def generate_loadfile(gl_header_path, out_folder):
        info = GLHeaderInfo(gl_header_path)
        funcs = GLLoader._load_gl_header(gl_header_path)
        ext_funcs = GLLoader._load_gl_header(info.ext_path)

        gl_funcs = GLLoader._get_gl_api_funcs(funcs + ext_funcs)
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
        GLLoader._write_loader_files(out_folder, inc_data, src_data)


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

    if args.whitelist:
        print "OpenGL extensions white-listed: ", args.whitelist
        for extension in args.whitelist:
            _EXTENSION_BLACKLIST.remove(extension)

    GLLoader.generate_loadfile(i, o)

    print "Done."

if __name__ == '__main__':
    run_command_line()
