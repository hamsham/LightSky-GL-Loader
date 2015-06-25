
/*
 * gcc --std=c99 -pedantic -pedantic-errors -Wall -Werror -Wextra -O2 -I./ -g -c lsgl.c -o lsgl.o
 *
 * ar rcs lilsgl_d.a lsgl.o
 */

#ifndef __LS_GL_LOADER_H__
#define __LS_GL_LOADER_H__

#include <GLES3/gl3.h>
#include <GLES3/gl2ext.h>

/*-------------------------------------
 * LightSky OpenGL Function Initializaton
-------------------------------------*/
int lsgl_init();

/*-------------------------------------
 * OpenGL Function Declarations
-------------------------------------*/
{% for func in glfunctions %}extern PFN{{ func.upper() }}PROC {{ func }};

{% endfor %}
#endif /* __LS_GL_LOADER_H__ */

