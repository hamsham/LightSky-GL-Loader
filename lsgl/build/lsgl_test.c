
/*
 * gcc --std=c99 -pedantic -pedantic-errors -Wall -Werror -Wextra -O2 -I./ -g lsgl_test.c -o lsgl_test -L./ -llsgl_d -lSDL2main -lSDL2 -lopengl32
 */

#include <stdio.h>
#include <stdint.h>

#ifndef SDL_MAIN_HANDLED
    #define SDL_MAIN_HANDLED
#endif

#include <SDL2/SDL.h>

#include "lsgl.h"

/*-------------------------------------
 * SDL2 Initialization
-------------------------------------*/
int init_sdl()
{
    const uint32_t sdlInitFlags = SDL_INIT_VIDEO;

    SDL_SetMainReady();

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

    if (SDL_Init(sdlInitFlags) < 0)
    {
        printf("Unable to initialize SDL due to error %s.\n", SDL_GetError());
        return 0;
    }

    printf("Successfully initialized SDL. Status: %s.\n", SDL_GetError());

    SDL_ClearError();

    return 1;
}

/*-------------------------------------
 * SDL2 Termination
-------------------------------------*/
void terminate_sdl()
{
    if (SDL_WasInit(0))
    {
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        SDL_Quit();
    }
}

/*-------------------------------------
 * Create a window
-------------------------------------*/
SDL_Window* init_display(int w, int h)
{
    SDL_Window* pWindow = NULL;
    const char title[] = "LS GL Test";

    printf("Attempting to create an OpenGL 3.3-compatible display through SDL.\n");

    // Create the window
    pWindow = SDL_CreateWindow
    (
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        w, h,
        SDL_WINDOW_OPENGL
    );

    if (!pWindow) {
        printf("\tUnable to create a display object. Reason: %s.\n", SDL_GetError());
        return NULL;
    }
    else {
        printf("\tSuccessfully created a window through SDL.\n");
    }

    return pWindow;
}

/*-------------------------------------
 * Terminate a window
-------------------------------------*/
void terminate_display(SDL_Window* const pWindow)
{
    SDL_DestroyWindow(pWindow);
}

/*-------------------------------------
 * Create an OpenGL-compatible context
-------------------------------------*/
SDL_GLContext* init_context(SDL_Window* const pWindow)
{
    SDL_GLContext* pContext = NULL;

    // Attach the OpenGL context to our window handle
    printf("Initializing an OpenGL rendering context.\n");

    pContext = SDL_GL_CreateContext(pWindow);

    if (!pContext)
    {
        printf("\tUnable to create an OpenGL-compatible context through SDL. ");
        printf("Reason: %s.\n", SDL_GetError());
        return NULL;
    }

    printf("\tSuccessfully initialized a OpenGL 3.3-compatible render context.\n");

    // Quick setup in order to normalize OpenGL to the display coordinates.
    SDL_GL_MakeCurrent(pWindow, pContext);

    // Set the default back buffer color
    glClearColor(1.f, 0.f, 1.f, 1.f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    printf("\tSuccessfully initialized a OpenGL 3.3-compatible render context.\n");

    return pContext;
}

/*-------------------------------------
 * Terminate an OpenGL context
-------------------------------------*/
void terminate_context(SDL_GLContext* const pContext)
{
    SDL_GL_DeleteContext(pContext);
}

/*-------------------------------------
 * Main
-------------------------------------*/
int main()
{
    SDL_Window* pWindow = NULL;
    SDL_GLContext* pContext = NULL;
    int func_count = 0;

    if (!init_sdl()
    || !(pWindow = init_display(640, 480))
    || !(pContext = init_context(pWindow))
    ) {
        goto terminate;
    }

    func_count = lsgl_init();

    if (func_count > 0)
    {
        printf("Successfully initialized the LightSky OpenGL API with %d functions.\n", func_count);
    }
    else
    {
        printf("Failed to initialize the LightSky OpenGL API\n");
    }

    terminate:
    terminate_context(pContext);
    terminate_display(pWindow);
    terminate_sdl();

    return 0;
}
