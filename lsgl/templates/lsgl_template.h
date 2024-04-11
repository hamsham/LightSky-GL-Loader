
/*
 * gcc --std=c99 -pedantic -pedantic-errors -Wall -Werror -Wextra -O2 -I./ -g -c lsgl.c -o lsgl_d.o
 *
 * ar rcs liblsgl_d.a lsgl_d.o
 */

#ifndef LS_GL_LOADER_H
#define LS_GL_LOADER_H

#ifndef GL_GLES_PROTOTYPES
    #define GL_GLES_PROTOTYPES 0
#endif

#include {{ glheader }}
#include {{ glextheader }}

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------
 * LightSky OpenGL Function Initializaton
-------------------------------------*/
int lsgl_init();

/*-------------------------------------
 * OpenGL Function Declarations (extern)
-------------------------------------*/
{% for func in glfunctions %}extern PFN{{ func.upper() }}PROC {{ func }};
{% endfor %}

#ifdef __cplusplus
}
#endif

#endif /* LS_GL_LOADER_H */

