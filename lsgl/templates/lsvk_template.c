
/*
 * gcc --std=c99 -pedantic -pedantic-errors -Wall -Werror -Wextra -O2 -I./ -g -c lsgl.c -o lsgl_d.o
 *
 * ar rcs liblsgl_d.a lsgl_d.o
 */

#include <stdint.h>
#include <stdio.h>

#include "lsvk.h"


{% for func_type, func_set in vktypedfuncs.items() %}
/*-------------------------------------
 * {{ func_type }} Function Declarations
-------------------------------------*/
{% for func in func_set %}PFN_{{ func }} {{ func }};
{% endfor %}

{% endfor %}


