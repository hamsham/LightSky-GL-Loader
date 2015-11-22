
import argparse
import os

from .glloader import GLLoader


__author__ = 'Miles Lacey'


# -----------------------------------------------------------------------------
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


# -----------------------------------------------------------------------------
def run_command_line():
    default_output = os.path.abspath(os.path.dirname(__file__)) + '/build'
    default_output = default_output.replace('\\', '/')

    parser = argparse.ArgumentParser(prog=PROGRAM_NAME,
                                     description=PROGRAM_DESC,
                                     usage=PROGRAM_USAGE)

    parser.add_argument('-i', '--input', required=True, type=str)
    parser.add_argument('-o', '--output', default=default_output,
                        type=str)
    parser.add_argument('-w', '--whitelist', nargs='*', type=str)

    args = parser.parse_args()

    if not args.input:
        parser.print_usage()
        return

    i = args.input
    o = args.output

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
