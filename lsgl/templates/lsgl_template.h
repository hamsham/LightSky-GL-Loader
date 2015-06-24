
/*
 * gcc --std=c99 -pedantic -pedantic-errors -Wall -Werror -Wextra -fPIC -O2 -I./ -g -c gl_loader.c -o gl_loader.o
 *
 * ar rcs libgl_loader_d.a gl_loader.o
 */

#ifndef __LS_GL_LOADER_H__
#define __LS_GL_LOADER_H__

#ifndef GL_GLEXT_PROTOTYPES
    #define GL_GLEXT_PROTOTYPES 1
#endif

#include <GLES3/gl3.h>
#include <GLES3/gl2ext.h>

bool lsgl_loader_init();

#endif /* __LS_GL_LOADER_H__ */
