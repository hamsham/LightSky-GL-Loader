# LightSky OpenGL Extension Loader
### A small OpenGL extension loader generator.


While refactoring LightSky's rendering system, I wanted to learn how extension loaders such as GLEW load OpenGL functions. OpenGL unfortunately has thousands of vendor-specific functions and loading them all by hand would be a massive pain. I decided to make a Python script which could do it all automatically and now want to share it with the Open-Source community!

It's a small script which takes any OpenGL or GL ES header, scans for its associated extensions header, then creates a header and source which can be added to any C/C++ project.

To use the loader, follow the usage below:
```
glloader.py [-h] -i PATH_TO_GL_HEADER [-o OUTPUT_DIRECTORY] [-w WHITELISTED_EXTENSIONS]

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
                includes the following extensions (as function suffixes):
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
                'SUNX'

-h              Print this help documentation.
```
