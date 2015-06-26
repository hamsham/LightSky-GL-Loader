
/*
 * gcc --std=c99 -pedantic -pedantic-errors -Wall -Werror -Wextra -O2 -I./ -g -c lsgl.c -o lsgl.o
 *
 * ar rcs liblsgl_d.a lsgl.o
 */

#include <stdint.h>
#include <stdio.h>

#include "lsgl.h"

#ifdef _WIN32
    #include <{{ glfolder }}/wglext.h>
#elif defined (__unix__)
    #include <{{ glfolder }}/glx.h>
#else
    #error "An unsupported OS is currently being used."
#endif

/*-----------------------------------------------------------------------------
 * Windows OpenGL Function Loading
-----------------------------------------------------------------------------*/
#ifdef _WIN32
/*-------------------------------------
 * OpenGL Library Initialization
-------------------------------------*/
HMODULE get_gl_library()
{
    return LoadLibraryA("opengl32.dll");
}

/*-------------------------------------
 * OpenGL Function Retrieval
-------------------------------------*/
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
#elif defined (__unix__)
/*-------------------------------------
 * OpenGL Function Retrieval
-------------------------------------*/
uintptr_t get_gl_function(const char* const name)
{
    uintptr_t p = (uintptr_t)glXGetProcAddress(name);

    if (p == 0x0
    || (p == 0x1)
    || (p == 0x2)
    || (p == 0x3)
    || (p == (uintptr_t)-1)
    ) {
        p = (uintptr_t)glXGetProcAddressARB(name);
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
 * LightSky OpenGL Function Initialization
-------------------------------------*/
int lsgl_init()
{
    int ret = GL_TRUE;

    {% for func in glfunctions %}{{ func }} = (PFN{{ func.upper() }}PROC)get_gl_function("{{ func }}");
    if (!{{ func }})
    {
        printf("Failed to load the OpenGL function \"{{ func }}\".\n");
        /* ret = GL_FALSE; */
    }

    {% endfor %}
    return ret;
}

/*-------------------------------------
 * OpenGL Function Declarations (static)
-------------------------------------*/
{% for func in glfunctions %}PFN{{ func.upper() }}PROC {{ func }};

{% endfor %}

