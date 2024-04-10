#!/bin/env python3

import argparse
import os

from .glloader import GLLoader
from .vkloader import VKLoader


__author__ = 'Miles Lacey'


# -----------------------------------------------------------------------------
PROGRAM_NAME = 'lsgl'

PROGRAM_DESC = 'The LSGL command-line utility can be used to generate an ' \
               'OpenGL or Vulkan loader library using only the path to a ' \
               'header file.'

PROGRAM_USAGE = '''lsgl.py [-h] -i GL_VK_HEADER_PATH [-o OUTPUT_DIRECTORY] [-e ENABLED_EXTENSIONS] [-d DECLARATION_TEMPLATE] [-s SOURCE_TEMPLATE]

-i/--input:     The input parameter should be the absolute or relative path to
                your OpenGL or Vulkan header file. For example:
                    -i /usr/include/GL/gl.h
                    -i /usr/include/GLES2/gl2.h
                    -i /usr/include/vulkan/vulkan_core.h
                When used for OpenGL or GLES function generation, this
                directory should also contain the appropriate GL/glext.h (or
                GLES2/gl2ext.h, or similar) header file containing OpenGL
                extensions provided by Khronos.
                For Vulkan, this path should be to your vulkan/vulkan_core.h
                header file.

-o/--output     The absolute or relative path to a directory which will contain
                a generated source and header file. These files can be used to
                dynamically load all standardized OpenGL, GLES, or Vulkan
                functions available on a machine at runtime.

-e/--extensions Request one or more vendor extensions from the list of all
                available vendor-specific OpenGL functions. Vendor-specific
                functions are disabled by default in order to provide a uniform
                set of standardized OpenGL functions across all target
                platforms. For example, passing '-i /usr/include/GLES2/gl2.h
                -w EXT ARB' will allow all 'EXT' and 'ARB' OpenGLES extensions
                suffixed with 'EXT' or 'ARB' (contained within 'gl2ext.h') to
                appear in the generated 'lsgl.h' and 'lsgl.c' source files.
                Passing '*' into this argument enables all extensions.
                The default blacklist includes the following extensions
                (as function suffixes):\n
                OpenGL extensions disabled by default are: {0}\n
                Vulkan extensions disabled by default are: {1}\n

-d/--declaration Provides a path to a user-defined Jinja2 template which will
                be used for a generated header file.
                
                OpenGL templates are passed the following parameters:
                - glheader:    Formatted as <GL[ES[2,3]]/gl[2,3,31].h>
                - glextheader: Formatted as <GL[ES[2,3]]/gl[2,3]ext.h>
                - glfolder:    Currently 'GL'
                - glversion:   Can be 'GL_DESKTOP' or 'GL_ES_[123][_[12]]'
                - glfunctions: A list of function strings in the form 'glFunc'
                
                Vulkan templates are passed the following parameters:
                - vkheader:         Formatted as 'vulkan_core.h'
                - vkfolder:         Currently 'vulkan'
                - vkfunctions:      A list of all available vulkan functions as strings
                - vktypedfunctions: A mapping of VKHandle types to a list of their corresponding functions.
                
-s/--sources    Provides a path to a user-defined Jinja2 template which will
                be used for a generated source/definition file. 

-h              Print this help documentation.

'''.format(GLLoader().blacklist, VKLoader().blacklist)


# -----------------------------------------------------------------------------
def run_command_line():
    file_path = os.path.abspath(os.path.dirname(__file__))
    default_output = os.path.join(file_path, 'build').replace('\\', '/')

    parser = argparse.ArgumentParser(prog=PROGRAM_NAME,
                                     description=PROGRAM_DESC,
                                     usage=PROGRAM_USAGE)

    parser.add_argument('-i', '--input', required=True, type=str)
    parser.add_argument('-o', '--output', default=default_output, type=str)
    parser.add_argument('-e', '--extensions', nargs='*', type=str, default='*')
    parser.add_argument('-d', '--declarations', type=str)
    parser.add_argument('-s', '--sources', type=str)

    args = parser.parse_args()

    if not args.input:
        parser.print_usage()
        return

    input_header = os.path.realpath(args.input)
    output_dir = os.path.realpath(args.output)
    extensions = args.extensions

    with open(input_header, 'r') as header:
        for line in header.readlines():
            if '#ifndef VULKAN_CORE_H_' in line:
                am_vk = True
                break
        else:
            am_vk = False

    loader = VKLoader() if am_vk else GLLoader()
    flavor = 'Vulkan' if am_vk else 'OpenGL'

    if args.declarations:
        header_template = os.path.realpath(args.declarations)
    else:
        header_template = 'lsvk_template.h' if am_vk else 'lsgl_template.h'
        header_template = os.path.join(file_path, 'templates', header_template)

    if args.sources:
        source_template = os.path.realpath(args.sources)
    else:
        source_template = 'lsvk_template.c' if am_vk else 'lsgl_template.c'
        source_template = os.path.join(file_path, 'templates', source_template)

    if '*' in extensions:
        print(f'All {flavor} extensions enabled.')
        loader.blacklist = []
        extensions = '*'
    elif extensions:
        for extension in extensions:
            try:
                loader.blacklist.remove(extension)
            except ValueError:
                print(f'Unknown extension: {extension}')
                extensions.remove(extension)

    print(f'Render API Detected:    {flavor}')
    print(f'Input header file:      {input_header}')
    print(f'Output directory:       {output_dir}')
    print(f'Extensions enabled:     {extensions!s}')

    loader.generate_loadfile(input_header, output_dir, header_template,
                             source_template)


# -----------------------------------------------------------------------------
if __name__ == '__main__':
    run_command_line()
