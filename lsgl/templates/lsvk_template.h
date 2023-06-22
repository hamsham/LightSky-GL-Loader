
/*
 * gcc --std=c99 -pedantic -pedantic-errors -Wall -Werror -Wextra -O2 -I./ -g -c lsgl.c -o lsgl_d.o
 *
 * ar rcs liblsgl_d.a lsgl_d.o
 */

#ifndef LS_VK_LOADER_H
#define LS_VK_LOADER_H



#ifndef VK_NO_PROTOTYPES
    #define VK_NO_PROTOTYPES 1
#endif

#include {{ vkheader }}

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------
 * Vulkan Function Declarations (extern)
-------------------------------------*/
{% for func in vkfunctions %}extern PFN_{{ func }} {{ func }};
{% endfor %}

#ifdef __cplusplus
}
#endif

#endif /* LS_VK_LOADER_H */

