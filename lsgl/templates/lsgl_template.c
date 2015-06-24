
/*
 * gcc --std=c99 -pedantic -pedantic-errors -Wall -Werror -Wextra -fPIC -O2 -I./ -g -c lsgl.c -o lsgl.o
 *
 * ar rcs lilsgl_d.a lsgl.o
 */

#ifdef _WIN32
    #include <GLES3/wglext.h>
#else
    #error "An unsupported OS is currently being used."
#endif

#include <string.h>
#include "lsgl.h"

#ifndef NULL
    #error "NULL is not defined by the current compiler."
#endif

/*-------------------------------------
-------------------------------------*/
#ifdef _WIN32
/*-------------------------------------
-------------------------------------*/
HMODULE get_gl_library()
{
    static const HMODULE ogllib = LoadLibraryA("opengl32.dll");
    return ogllib;
}

/*-------------------------------------
-------------------------------------*/
void* get_gl_function(const char* const name)
{
    void* const p = (void*)wglGetProcAddress(name);

    if (p == 0
    || (p == (void*)0x1)
    || (p == (void*)0x2)
    || (p == (void*)0x3)
    || (p == (void*)-1))
    {
        const HMODULE ogllib = get_gl_library();
        return (void*)GetProcAddress(ogllib, name);
    }

    return p;
}

/*-------------------------------------
-------------------------------------*/
#else
    #error "An unsupported OS is currently being used."
#endif

/*-------------------------------------
-------------------------------------*/
bool lsgl_loader_init()
{
    {% for loader in loadstrings %}
    {{ loader }}
    {% endfor %}

    return true
}
