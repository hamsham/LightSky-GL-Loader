
/*
 * gcc --std=c99 -pedantic -pedantic-errors -Wall -Werror -Wextra -O2 -I./ -g -c lsgl.c -o lsgl.o
 *
 * ar rcs liblsgl_d.a lsgl.o
 */

#ifndef __LS_GL_LOADER_H__
#define __LS_GL_LOADER_H__

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

#endif /* __LS_GL_LOADER_H__ */

