
/*
 * gcc --std=c99 -pedantic -pedantic-errors -Wall -Werror -Wextra -O2 -I./ -g -c lsgl.c -o lsgl_d.o
 *
 * ar rcs liblsgl_d.a lsgl_d.o
 */

#include <stdint.h>
#include <stdio.h>

#include "lsgl.h"

#ifndef LS_EGL_CONTEXT
    #define LS_EGL_CONTEXT 0
#endif

#ifndef LS_GLX_CONTEXT
    #define LS_GLX_CONTEXT 1
#endif

#ifndef LS_WGL_CONTEXT
    #define LS_WGL_CONTEXT 2
#endif

#ifndef LS_UNKNOWN_CONTEXT
    #define LS_UNKNOWN_CONTEXT -1
#endif

#ifndef LS_GL_CONTEXT
    #define LS_GL_CONTEXT {{ glContext }}
#endif

#if LS_GL_CONTEXT == LS_EGL_CONTEXT
    #include <EGL/egl.h>
    #include <EGL/eglext.h>
#elif LS_GL_CONTEXT == LS_GLX_CONTEXT
    #include <{{ glfolder }}/glx.h>
    #include <{{ glfolder }}/glxext.h>
#elif LS_GL_CONTEXT == LS_WGL_CONTEXT
    #include <{{ glfolder }}/wgl.h>
#else
    #error "An unsupported OS is currently being used."
#endif

/*-----------------------------------------------------------------------------
 * Windows OpenGL Function Loading
-----------------------------------------------------------------------------*/
#if LS_GL_CONTEXT == LS_WGL_CONTEXT

HMODULE get_gl_library()
{
    return LoadLibraryA("opengl32.dll");
}

uintptr_t get_gl_function(const char* const name)
{
    uintptr_t p = (uintptr_t)wglGetProcAddress(name);

    if (p == 0x0
    || (p == 0x1)
    || (p == 0x2)
    || (p == 0x3)
    || (p == (uintptr_t)-1)
    ) {
        const HMODULE ogllib = get_gl_library();
        p = (uintptr_t)GetProcAddress(ogllib, name);
    }

    return p;
}

/*-----------------------------------------------------------------------------
 * Unix-Based OpenGL Function Loading
-----------------------------------------------------------------------------*/
#elif LS_GL_CONTEXT == LS_GLX_CONTEXT

uintptr_t get_gl_function(const char* const name)
{
    uintptr_t p = (uintptr_t)glXGetProcAddress((const unsigned char*)name);

    if (p == 0x0
    || (p == 0x1)
    || (p == 0x2)
    || (p == 0x3)
    || (p == (uintptr_t)-1)
    ) {
        p = (uintptr_t)glXGetProcAddressARB((const unsigned char*)name);
    }

    return p;
}

/*-----------------------------------------------------------------------------
 * EGL-Based OpenGL Function Loading
-----------------------------------------------------------------------------*/
#elif LS_GL_CONTEXT == LS_EGL_CONTEXT

uintptr_t get_gl_function(const char* const name)
{
    uintptr_t p = (uintptr_t)eglGetProcAddress(name);

    if (p == 0x0
    || (p == 0x1)
    || (p == 0x2)
    || (p == 0x3)
    || (p == (uintptr_t)-1)
    ) {
        p = 0;
    }

    return p;
}

/*-----------------------------------------------------------------------------
 * Unknown OS
-----------------------------------------------------------------------------*/
#else
    #error "An unsupported OS is currently being used."
#endif

/*-------------------------------------
 * OpenGL Function Declarations (static)
-------------------------------------*/
{% for func in glfunctions %}PFN{{ func.upper() }}PROC {{ func }};
{% endfor %}

/*-------------------------------------
 * LightSky OpenGL Function Initialization
-------------------------------------*/
int lsgl_init()
{
    /* Contains the number of functions initialized */
    int ret = {{ 1 if not glfunctions else 0 }};

    {% for func in glfunctions %}{{ func }} = (PFN{{ func.upper() }}PROC)get_gl_function("{{ func }}");
    if ({{ func }}) {++ret;}
    {% endfor %}
    return ret;
}

