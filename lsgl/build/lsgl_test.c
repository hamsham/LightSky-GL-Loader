
/*
 * gcc --std=c99 -pedantic -pedantic-errors -Wall -Werror -Wextra -O2 -I./ -g lsgl_test.c -o lsgl_test -L./ -llsgl_d -lopengl32
 */

#include <stdio.h>

#include "lsgl.h"

int main()
{
    if (lsgl_init() == GL_TRUE)
    {
        printf("Successfully initialized the LightSky OpenGL API");
    }
    else
    {
        printf("Failed to initialize the LightSky OpenGL API");
    }

    return 0;
}
