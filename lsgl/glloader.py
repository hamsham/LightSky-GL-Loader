
__author__ = 'Miles Lacey'

import os
import re
import jinja2

class GLLoader:

    DEFAULT_BUILD_DIR = os.path.abspath(os.path.dirname(__file__) + '/build')

    @staticmethod
    def _load_gl_header(filename):
        with open(filename, 'rb') as f:
            lines = f.readlines()
        return lines

    @staticmethod
    def _get_matches_in_list(regex, strlist):
        matches = []

        for strdata in strlist:
            match = re.search(regex, strdata)

            if not match:
                continue

            matches.append(match.group(0))

        return matches

    @staticmethod
    def _get_gl_api_funcs(filelines):
        func_regex = '(?<=GL\_APIENTRY\ )(\w+)(?=\ \()'
        return GLLoader._get_matches_in_list(func_regex, filelines)

    @staticmethod
    def _get_gl_load_strings(func_list):
        loader = '%s = (PFN%sPROC)get_gl_function("%s")'
        return [loader % (func, func.upper(), func) for func in func_list]

    @staticmethod
    def _write_loader_files(outfolder, includedata, srcdata):
        def writedata(folder, extension, data):
            with open('%s/lsgl%s' % (folder, extension), 'wb') as f:
                f.write(data)

        writedata(outfolder, '.h', includedata)
        writedata(outfolder, '.c', srcdata)

    def generate_loadfile(self, glheaderfile, outfolder=DEFAULT_BUILD_DIR):
        lines = GLLoader._load_gl_header(glheaderfile)
        funcs = GLLoader._get_gl_api_funcs(lines)
        loadstrings = GLLoader._get_gl_load_strings(funcs)

        cwd = os.path.abspath(os.path.dirname(__file__))
        pkg = jinja2.FileSystemLoader('%s/templates' % cwd, encoding='ascii')
        env = jinja2.Environment(loader=pkg)

        incfile = 'lsgl_template.h'
        srcfile = 'lsgl_template.c'
        incdata = env.get_template(incfile).render()
        srcdata = env.get_template(srcfile).render(loadstrings=loadstrings)

        GLLoader._write_loader_files(outfolder, incdata, srcdata)

def main():
    glheader = 'C:\\MinGW\\mingw64\\x86_64-w64-mingw32\\include\\GLES3\\gl3.h'
    loader = GLLoader()
    loader.generate_loadfile(glheader)

if __name__ == '__main__':
    main()
