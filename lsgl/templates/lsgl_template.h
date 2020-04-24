
/*
 * gcc --std=c99 -pedantic -pedantic-errors -Wall -Werror -Wextra -O2 -I./ -g -c lsgl.c -o lsgl_d.o
 *
 * ar rcs liblsgl_d.a lsgl_d.o
 */

#ifndef LS_GL_LOADER_H
#define LS_GL_LOADER_H

/*
#ifndef GL_VERSION_1_0
    #define GL_VERSION_1_0
#endif

#ifndef GL_VERSION_1_1
    #define GL_VERSION_1_1
#endif

#ifndef GL_VERSION_1_2
    #define GL_VERSION_1_2
#endif

#ifndef GL_VERSION_1_3
    #define GL_VERSION_1_3
#endif

#ifndef GL_VERSION_1_4
    #define GL_VERSION_1_4
#endif

#ifndef GL_VERSION_1_5
    #define GL_VERSION_1_5
#endif

#ifndef GL_VERSION_2_0
    #define GL_VERSION_2_0
#endif

#ifndef GL_VERSION_2_1
    #define GL_VERSION_2_1
#endif

#ifndef GL_VERSION_3_0
    #define GL_VERSION_3_0
#endif

#ifndef GL_VERSION_3_1
    #define GL_VERSION_3_1
#endif

#ifndef GL_VERSION_3_2
    #define GL_VERSION_3_2
#endif

#ifndef GL_VERSION_3_3
    #define GL_VERSION_3_3
#endif

#ifndef GL_VERSION_4_0
    #define GL_VERSION_4_0
#endif

#ifndef GL_VERSION_4_1
    #define GL_VERSION_4_1
#endif

#ifndef GL_VERSION_4_2
    #define GL_VERSION_4_2
#endif

#ifndef GL_VERSION_4_3
    #define GL_VERSION_4_3
#endif

#ifndef GL_VERSION_4_4
    #define GL_VERSION_4_4
#endif

#ifndef GL_VERSION_4_5
    #define GL_VERSION_4_5
#endif

#ifndef GL_VERSION_4_6
    #define GL_VERSION_4_6
#endif
*/

#ifndef GL_GLES_PROTOTYPES
    #define GL_GLES_PROTOTYPES 0
#endif

#include {{ glheader }}

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

