
/*
 * gcc --std=c99 -pedantic -pedantic-errors -Wall -Werror -Wextra -O2 -I./ -g -c lsgl.c -o lsgl_d.o
 *
 * ar rcs liblsgl_d.a lsgl_d.o
 */

#include <stdint.h>
#include <stdio.h>

#include "lsvk.h"



/*-------------------------------------
 * Vulkan Function Declarations (static)
-------------------------------------*/
{% for func in vkfunctions %}PFN_{{ func }} {{ func }};
{% endfor %}


