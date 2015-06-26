
/*
 * gcc --std=c99 -pedantic -pedantic-errors -Wall -Werror -Wextra -O2 -I./ -g -c lsgl.c -o lsgl.o
 *
 * ar rcs liblsgl_d.a lsgl.o
 */

#include <stdint.h>
#include <stdio.h>

#include "lsgl.h"

#ifdef _WIN32
    #include <GLES3/wglext.h>
#elif defined (__unix__)
    #include <GLES3/glx.h>
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

    glActiveTexture = (PFNGLACTIVETEXTUREPROC)get_gl_function("glActiveTexture");
    if (!glActiveTexture)
    {
        printf("Failed to load the OpenGL function \"glActiveTexture\".\n");
        /* ret = GL_FALSE; */
    }

    glAttachShader = (PFNGLATTACHSHADERPROC)get_gl_function("glAttachShader");
    if (!glAttachShader)
    {
        printf("Failed to load the OpenGL function \"glAttachShader\".\n");
        /* ret = GL_FALSE; */
    }

    glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)get_gl_function("glBindAttribLocation");
    if (!glBindAttribLocation)
    {
        printf("Failed to load the OpenGL function \"glBindAttribLocation\".\n");
        /* ret = GL_FALSE; */
    }

    glBindBuffer = (PFNGLBINDBUFFERPROC)get_gl_function("glBindBuffer");
    if (!glBindBuffer)
    {
        printf("Failed to load the OpenGL function \"glBindBuffer\".\n");
        /* ret = GL_FALSE; */
    }

    glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)get_gl_function("glBindFramebuffer");
    if (!glBindFramebuffer)
    {
        printf("Failed to load the OpenGL function \"glBindFramebuffer\".\n");
        /* ret = GL_FALSE; */
    }

    glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)get_gl_function("glBindRenderbuffer");
    if (!glBindRenderbuffer)
    {
        printf("Failed to load the OpenGL function \"glBindRenderbuffer\".\n");
        /* ret = GL_FALSE; */
    }

    glBindTexture = (PFNGLBINDTEXTUREPROC)get_gl_function("glBindTexture");
    if (!glBindTexture)
    {
        printf("Failed to load the OpenGL function \"glBindTexture\".\n");
        /* ret = GL_FALSE; */
    }

    glBlendColor = (PFNGLBLENDCOLORPROC)get_gl_function("glBlendColor");
    if (!glBlendColor)
    {
        printf("Failed to load the OpenGL function \"glBlendColor\".\n");
        /* ret = GL_FALSE; */
    }

    glBlendEquation = (PFNGLBLENDEQUATIONPROC)get_gl_function("glBlendEquation");
    if (!glBlendEquation)
    {
        printf("Failed to load the OpenGL function \"glBlendEquation\".\n");
        /* ret = GL_FALSE; */
    }

    glBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATEPROC)get_gl_function("glBlendEquationSeparate");
    if (!glBlendEquationSeparate)
    {
        printf("Failed to load the OpenGL function \"glBlendEquationSeparate\".\n");
        /* ret = GL_FALSE; */
    }

    glBlendFunc = (PFNGLBLENDFUNCPROC)get_gl_function("glBlendFunc");
    if (!glBlendFunc)
    {
        printf("Failed to load the OpenGL function \"glBlendFunc\".\n");
        /* ret = GL_FALSE; */
    }

    glBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC)get_gl_function("glBlendFuncSeparate");
    if (!glBlendFuncSeparate)
    {
        printf("Failed to load the OpenGL function \"glBlendFuncSeparate\".\n");
        /* ret = GL_FALSE; */
    }

    glBufferData = (PFNGLBUFFERDATAPROC)get_gl_function("glBufferData");
    if (!glBufferData)
    {
        printf("Failed to load the OpenGL function \"glBufferData\".\n");
        /* ret = GL_FALSE; */
    }

    glBufferSubData = (PFNGLBUFFERSUBDATAPROC)get_gl_function("glBufferSubData");
    if (!glBufferSubData)
    {
        printf("Failed to load the OpenGL function \"glBufferSubData\".\n");
        /* ret = GL_FALSE; */
    }

    glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)get_gl_function("glCheckFramebufferStatus");
    if (!glCheckFramebufferStatus)
    {
        printf("Failed to load the OpenGL function \"glCheckFramebufferStatus\".\n");
        /* ret = GL_FALSE; */
    }

    glClear = (PFNGLCLEARPROC)get_gl_function("glClear");
    if (!glClear)
    {
        printf("Failed to load the OpenGL function \"glClear\".\n");
        /* ret = GL_FALSE; */
    }

    glClearColor = (PFNGLCLEARCOLORPROC)get_gl_function("glClearColor");
    if (!glClearColor)
    {
        printf("Failed to load the OpenGL function \"glClearColor\".\n");
        /* ret = GL_FALSE; */
    }

    glClearDepthf = (PFNGLCLEARDEPTHFPROC)get_gl_function("glClearDepthf");
    if (!glClearDepthf)
    {
        printf("Failed to load the OpenGL function \"glClearDepthf\".\n");
        /* ret = GL_FALSE; */
    }

    glClearStencil = (PFNGLCLEARSTENCILPROC)get_gl_function("glClearStencil");
    if (!glClearStencil)
    {
        printf("Failed to load the OpenGL function \"glClearStencil\".\n");
        /* ret = GL_FALSE; */
    }

    glColorMask = (PFNGLCOLORMASKPROC)get_gl_function("glColorMask");
    if (!glColorMask)
    {
        printf("Failed to load the OpenGL function \"glColorMask\".\n");
        /* ret = GL_FALSE; */
    }

    glCompileShader = (PFNGLCOMPILESHADERPROC)get_gl_function("glCompileShader");
    if (!glCompileShader)
    {
        printf("Failed to load the OpenGL function \"glCompileShader\".\n");
        /* ret = GL_FALSE; */
    }

    glCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC)get_gl_function("glCompressedTexImage2D");
    if (!glCompressedTexImage2D)
    {
        printf("Failed to load the OpenGL function \"glCompressedTexImage2D\".\n");
        /* ret = GL_FALSE; */
    }

    glCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)get_gl_function("glCompressedTexSubImage2D");
    if (!glCompressedTexSubImage2D)
    {
        printf("Failed to load the OpenGL function \"glCompressedTexSubImage2D\".\n");
        /* ret = GL_FALSE; */
    }

    glCopyTexImage2D = (PFNGLCOPYTEXIMAGE2DPROC)get_gl_function("glCopyTexImage2D");
    if (!glCopyTexImage2D)
    {
        printf("Failed to load the OpenGL function \"glCopyTexImage2D\".\n");
        /* ret = GL_FALSE; */
    }

    glCopyTexSubImage2D = (PFNGLCOPYTEXSUBIMAGE2DPROC)get_gl_function("glCopyTexSubImage2D");
    if (!glCopyTexSubImage2D)
    {
        printf("Failed to load the OpenGL function \"glCopyTexSubImage2D\".\n");
        /* ret = GL_FALSE; */
    }

    glCreateProgram = (PFNGLCREATEPROGRAMPROC)get_gl_function("glCreateProgram");
    if (!glCreateProgram)
    {
        printf("Failed to load the OpenGL function \"glCreateProgram\".\n");
        /* ret = GL_FALSE; */
    }

    glCreateShader = (PFNGLCREATESHADERPROC)get_gl_function("glCreateShader");
    if (!glCreateShader)
    {
        printf("Failed to load the OpenGL function \"glCreateShader\".\n");
        /* ret = GL_FALSE; */
    }

    glCullFace = (PFNGLCULLFACEPROC)get_gl_function("glCullFace");
    if (!glCullFace)
    {
        printf("Failed to load the OpenGL function \"glCullFace\".\n");
        /* ret = GL_FALSE; */
    }

    glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)get_gl_function("glDeleteBuffers");
    if (!glDeleteBuffers)
    {
        printf("Failed to load the OpenGL function \"glDeleteBuffers\".\n");
        /* ret = GL_FALSE; */
    }

    glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)get_gl_function("glDeleteFramebuffers");
    if (!glDeleteFramebuffers)
    {
        printf("Failed to load the OpenGL function \"glDeleteFramebuffers\".\n");
        /* ret = GL_FALSE; */
    }

    glDeleteProgram = (PFNGLDELETEPROGRAMPROC)get_gl_function("glDeleteProgram");
    if (!glDeleteProgram)
    {
        printf("Failed to load the OpenGL function \"glDeleteProgram\".\n");
        /* ret = GL_FALSE; */
    }

    glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)get_gl_function("glDeleteRenderbuffers");
    if (!glDeleteRenderbuffers)
    {
        printf("Failed to load the OpenGL function \"glDeleteRenderbuffers\".\n");
        /* ret = GL_FALSE; */
    }

    glDeleteShader = (PFNGLDELETESHADERPROC)get_gl_function("glDeleteShader");
    if (!glDeleteShader)
    {
        printf("Failed to load the OpenGL function \"glDeleteShader\".\n");
        /* ret = GL_FALSE; */
    }

    glDeleteTextures = (PFNGLDELETETEXTURESPROC)get_gl_function("glDeleteTextures");
    if (!glDeleteTextures)
    {
        printf("Failed to load the OpenGL function \"glDeleteTextures\".\n");
        /* ret = GL_FALSE; */
    }

    glDepthFunc = (PFNGLDEPTHFUNCPROC)get_gl_function("glDepthFunc");
    if (!glDepthFunc)
    {
        printf("Failed to load the OpenGL function \"glDepthFunc\".\n");
        /* ret = GL_FALSE; */
    }

    glDepthMask = (PFNGLDEPTHMASKPROC)get_gl_function("glDepthMask");
    if (!glDepthMask)
    {
        printf("Failed to load the OpenGL function \"glDepthMask\".\n");
        /* ret = GL_FALSE; */
    }

    glDepthRangef = (PFNGLDEPTHRANGEFPROC)get_gl_function("glDepthRangef");
    if (!glDepthRangef)
    {
        printf("Failed to load the OpenGL function \"glDepthRangef\".\n");
        /* ret = GL_FALSE; */
    }

    glDetachShader = (PFNGLDETACHSHADERPROC)get_gl_function("glDetachShader");
    if (!glDetachShader)
    {
        printf("Failed to load the OpenGL function \"glDetachShader\".\n");
        /* ret = GL_FALSE; */
    }

    glDisable = (PFNGLDISABLEPROC)get_gl_function("glDisable");
    if (!glDisable)
    {
        printf("Failed to load the OpenGL function \"glDisable\".\n");
        /* ret = GL_FALSE; */
    }

    glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)get_gl_function("glDisableVertexAttribArray");
    if (!glDisableVertexAttribArray)
    {
        printf("Failed to load the OpenGL function \"glDisableVertexAttribArray\".\n");
        /* ret = GL_FALSE; */
    }

    glDrawArrays = (PFNGLDRAWARRAYSPROC)get_gl_function("glDrawArrays");
    if (!glDrawArrays)
    {
        printf("Failed to load the OpenGL function \"glDrawArrays\".\n");
        /* ret = GL_FALSE; */
    }

    glDrawElements = (PFNGLDRAWELEMENTSPROC)get_gl_function("glDrawElements");
    if (!glDrawElements)
    {
        printf("Failed to load the OpenGL function \"glDrawElements\".\n");
        /* ret = GL_FALSE; */
    }

    glEnable = (PFNGLENABLEPROC)get_gl_function("glEnable");
    if (!glEnable)
    {
        printf("Failed to load the OpenGL function \"glEnable\".\n");
        /* ret = GL_FALSE; */
    }

    glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)get_gl_function("glEnableVertexAttribArray");
    if (!glEnableVertexAttribArray)
    {
        printf("Failed to load the OpenGL function \"glEnableVertexAttribArray\".\n");
        /* ret = GL_FALSE; */
    }

    glFinish = (PFNGLFINISHPROC)get_gl_function("glFinish");
    if (!glFinish)
    {
        printf("Failed to load the OpenGL function \"glFinish\".\n");
        /* ret = GL_FALSE; */
    }

    glFlush = (PFNGLFLUSHPROC)get_gl_function("glFlush");
    if (!glFlush)
    {
        printf("Failed to load the OpenGL function \"glFlush\".\n");
        /* ret = GL_FALSE; */
    }

    glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)get_gl_function("glFramebufferRenderbuffer");
    if (!glFramebufferRenderbuffer)
    {
        printf("Failed to load the OpenGL function \"glFramebufferRenderbuffer\".\n");
        /* ret = GL_FALSE; */
    }

    glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)get_gl_function("glFramebufferTexture2D");
    if (!glFramebufferTexture2D)
    {
        printf("Failed to load the OpenGL function \"glFramebufferTexture2D\".\n");
        /* ret = GL_FALSE; */
    }

    glFrontFace = (PFNGLFRONTFACEPROC)get_gl_function("glFrontFace");
    if (!glFrontFace)
    {
        printf("Failed to load the OpenGL function \"glFrontFace\".\n");
        /* ret = GL_FALSE; */
    }

    glGenBuffers = (PFNGLGENBUFFERSPROC)get_gl_function("glGenBuffers");
    if (!glGenBuffers)
    {
        printf("Failed to load the OpenGL function \"glGenBuffers\".\n");
        /* ret = GL_FALSE; */
    }

    glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)get_gl_function("glGenerateMipmap");
    if (!glGenerateMipmap)
    {
        printf("Failed to load the OpenGL function \"glGenerateMipmap\".\n");
        /* ret = GL_FALSE; */
    }

    glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)get_gl_function("glGenFramebuffers");
    if (!glGenFramebuffers)
    {
        printf("Failed to load the OpenGL function \"glGenFramebuffers\".\n");
        /* ret = GL_FALSE; */
    }

    glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)get_gl_function("glGenRenderbuffers");
    if (!glGenRenderbuffers)
    {
        printf("Failed to load the OpenGL function \"glGenRenderbuffers\".\n");
        /* ret = GL_FALSE; */
    }

    glGenTextures = (PFNGLGENTEXTURESPROC)get_gl_function("glGenTextures");
    if (!glGenTextures)
    {
        printf("Failed to load the OpenGL function \"glGenTextures\".\n");
        /* ret = GL_FALSE; */
    }

    glGetActiveAttrib = (PFNGLGETACTIVEATTRIBPROC)get_gl_function("glGetActiveAttrib");
    if (!glGetActiveAttrib)
    {
        printf("Failed to load the OpenGL function \"glGetActiveAttrib\".\n");
        /* ret = GL_FALSE; */
    }

    glGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC)get_gl_function("glGetActiveUniform");
    if (!glGetActiveUniform)
    {
        printf("Failed to load the OpenGL function \"glGetActiveUniform\".\n");
        /* ret = GL_FALSE; */
    }

    glGetAttachedShaders = (PFNGLGETATTACHEDSHADERSPROC)get_gl_function("glGetAttachedShaders");
    if (!glGetAttachedShaders)
    {
        printf("Failed to load the OpenGL function \"glGetAttachedShaders\".\n");
        /* ret = GL_FALSE; */
    }

    glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)get_gl_function("glGetAttribLocation");
    if (!glGetAttribLocation)
    {
        printf("Failed to load the OpenGL function \"glGetAttribLocation\".\n");
        /* ret = GL_FALSE; */
    }

    glGetBooleanv = (PFNGLGETBOOLEANVPROC)get_gl_function("glGetBooleanv");
    if (!glGetBooleanv)
    {
        printf("Failed to load the OpenGL function \"glGetBooleanv\".\n");
        /* ret = GL_FALSE; */
    }

    glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC)get_gl_function("glGetBufferParameteriv");
    if (!glGetBufferParameteriv)
    {
        printf("Failed to load the OpenGL function \"glGetBufferParameteriv\".\n");
        /* ret = GL_FALSE; */
    }

    glGetError = (PFNGLGETERRORPROC)get_gl_function("glGetError");
    if (!glGetError)
    {
        printf("Failed to load the OpenGL function \"glGetError\".\n");
        /* ret = GL_FALSE; */
    }

    glGetFloatv = (PFNGLGETFLOATVPROC)get_gl_function("glGetFloatv");
    if (!glGetFloatv)
    {
        printf("Failed to load the OpenGL function \"glGetFloatv\".\n");
        /* ret = GL_FALSE; */
    }

    glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)get_gl_function("glGetFramebufferAttachmentParameteriv");
    if (!glGetFramebufferAttachmentParameteriv)
    {
        printf("Failed to load the OpenGL function \"glGetFramebufferAttachmentParameteriv\".\n");
        /* ret = GL_FALSE; */
    }

    glGetIntegerv = (PFNGLGETINTEGERVPROC)get_gl_function("glGetIntegerv");
    if (!glGetIntegerv)
    {
        printf("Failed to load the OpenGL function \"glGetIntegerv\".\n");
        /* ret = GL_FALSE; */
    }

    glGetProgramiv = (PFNGLGETPROGRAMIVPROC)get_gl_function("glGetProgramiv");
    if (!glGetProgramiv)
    {
        printf("Failed to load the OpenGL function \"glGetProgramiv\".\n");
        /* ret = GL_FALSE; */
    }

    glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)get_gl_function("glGetProgramInfoLog");
    if (!glGetProgramInfoLog)
    {
        printf("Failed to load the OpenGL function \"glGetProgramInfoLog\".\n");
        /* ret = GL_FALSE; */
    }

    glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC)get_gl_function("glGetRenderbufferParameteriv");
    if (!glGetRenderbufferParameteriv)
    {
        printf("Failed to load the OpenGL function \"glGetRenderbufferParameteriv\".\n");
        /* ret = GL_FALSE; */
    }

    glGetShaderiv = (PFNGLGETSHADERIVPROC)get_gl_function("glGetShaderiv");
    if (!glGetShaderiv)
    {
        printf("Failed to load the OpenGL function \"glGetShaderiv\".\n");
        /* ret = GL_FALSE; */
    }

    glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)get_gl_function("glGetShaderInfoLog");
    if (!glGetShaderInfoLog)
    {
        printf("Failed to load the OpenGL function \"glGetShaderInfoLog\".\n");
        /* ret = GL_FALSE; */
    }

    glGetShaderPrecisionFormat = (PFNGLGETSHADERPRECISIONFORMATPROC)get_gl_function("glGetShaderPrecisionFormat");
    if (!glGetShaderPrecisionFormat)
    {
        printf("Failed to load the OpenGL function \"glGetShaderPrecisionFormat\".\n");
        /* ret = GL_FALSE; */
    }

    glGetShaderSource = (PFNGLGETSHADERSOURCEPROC)get_gl_function("glGetShaderSource");
    if (!glGetShaderSource)
    {
        printf("Failed to load the OpenGL function \"glGetShaderSource\".\n");
        /* ret = GL_FALSE; */
    }

    glGetString = (PFNGLGETSTRINGPROC)get_gl_function("glGetString");
    if (!glGetString)
    {
        printf("Failed to load the OpenGL function \"glGetString\".\n");
        /* ret = GL_FALSE; */
    }

    glGetTexParameterfv = (PFNGLGETTEXPARAMETERFVPROC)get_gl_function("glGetTexParameterfv");
    if (!glGetTexParameterfv)
    {
        printf("Failed to load the OpenGL function \"glGetTexParameterfv\".\n");
        /* ret = GL_FALSE; */
    }

    glGetTexParameteriv = (PFNGLGETTEXPARAMETERIVPROC)get_gl_function("glGetTexParameteriv");
    if (!glGetTexParameteriv)
    {
        printf("Failed to load the OpenGL function \"glGetTexParameteriv\".\n");
        /* ret = GL_FALSE; */
    }

    glGetUniformfv = (PFNGLGETUNIFORMFVPROC)get_gl_function("glGetUniformfv");
    if (!glGetUniformfv)
    {
        printf("Failed to load the OpenGL function \"glGetUniformfv\".\n");
        /* ret = GL_FALSE; */
    }

    glGetUniformiv = (PFNGLGETUNIFORMIVPROC)get_gl_function("glGetUniformiv");
    if (!glGetUniformiv)
    {
        printf("Failed to load the OpenGL function \"glGetUniformiv\".\n");
        /* ret = GL_FALSE; */
    }

    glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)get_gl_function("glGetUniformLocation");
    if (!glGetUniformLocation)
    {
        printf("Failed to load the OpenGL function \"glGetUniformLocation\".\n");
        /* ret = GL_FALSE; */
    }

    glGetVertexAttribfv = (PFNGLGETVERTEXATTRIBFVPROC)get_gl_function("glGetVertexAttribfv");
    if (!glGetVertexAttribfv)
    {
        printf("Failed to load the OpenGL function \"glGetVertexAttribfv\".\n");
        /* ret = GL_FALSE; */
    }

    glGetVertexAttribiv = (PFNGLGETVERTEXATTRIBIVPROC)get_gl_function("glGetVertexAttribiv");
    if (!glGetVertexAttribiv)
    {
        printf("Failed to load the OpenGL function \"glGetVertexAttribiv\".\n");
        /* ret = GL_FALSE; */
    }

    glGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERVPROC)get_gl_function("glGetVertexAttribPointerv");
    if (!glGetVertexAttribPointerv)
    {
        printf("Failed to load the OpenGL function \"glGetVertexAttribPointerv\".\n");
        /* ret = GL_FALSE; */
    }

    glHint = (PFNGLHINTPROC)get_gl_function("glHint");
    if (!glHint)
    {
        printf("Failed to load the OpenGL function \"glHint\".\n");
        /* ret = GL_FALSE; */
    }

    glIsBuffer = (PFNGLISBUFFERPROC)get_gl_function("glIsBuffer");
    if (!glIsBuffer)
    {
        printf("Failed to load the OpenGL function \"glIsBuffer\".\n");
        /* ret = GL_FALSE; */
    }

    glIsEnabled = (PFNGLISENABLEDPROC)get_gl_function("glIsEnabled");
    if (!glIsEnabled)
    {
        printf("Failed to load the OpenGL function \"glIsEnabled\".\n");
        /* ret = GL_FALSE; */
    }

    glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC)get_gl_function("glIsFramebuffer");
    if (!glIsFramebuffer)
    {
        printf("Failed to load the OpenGL function \"glIsFramebuffer\".\n");
        /* ret = GL_FALSE; */
    }

    glIsProgram = (PFNGLISPROGRAMPROC)get_gl_function("glIsProgram");
    if (!glIsProgram)
    {
        printf("Failed to load the OpenGL function \"glIsProgram\".\n");
        /* ret = GL_FALSE; */
    }

    glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC)get_gl_function("glIsRenderbuffer");
    if (!glIsRenderbuffer)
    {
        printf("Failed to load the OpenGL function \"glIsRenderbuffer\".\n");
        /* ret = GL_FALSE; */
    }

    glIsShader = (PFNGLISSHADERPROC)get_gl_function("glIsShader");
    if (!glIsShader)
    {
        printf("Failed to load the OpenGL function \"glIsShader\".\n");
        /* ret = GL_FALSE; */
    }

    glIsTexture = (PFNGLISTEXTUREPROC)get_gl_function("glIsTexture");
    if (!glIsTexture)
    {
        printf("Failed to load the OpenGL function \"glIsTexture\".\n");
        /* ret = GL_FALSE; */
    }

    glLineWidth = (PFNGLLINEWIDTHPROC)get_gl_function("glLineWidth");
    if (!glLineWidth)
    {
        printf("Failed to load the OpenGL function \"glLineWidth\".\n");
        /* ret = GL_FALSE; */
    }

    glLinkProgram = (PFNGLLINKPROGRAMPROC)get_gl_function("glLinkProgram");
    if (!glLinkProgram)
    {
        printf("Failed to load the OpenGL function \"glLinkProgram\".\n");
        /* ret = GL_FALSE; */
    }

    glPixelStorei = (PFNGLPIXELSTOREIPROC)get_gl_function("glPixelStorei");
    if (!glPixelStorei)
    {
        printf("Failed to load the OpenGL function \"glPixelStorei\".\n");
        /* ret = GL_FALSE; */
    }

    glPolygonOffset = (PFNGLPOLYGONOFFSETPROC)get_gl_function("glPolygonOffset");
    if (!glPolygonOffset)
    {
        printf("Failed to load the OpenGL function \"glPolygonOffset\".\n");
        /* ret = GL_FALSE; */
    }

    glReadPixels = (PFNGLREADPIXELSPROC)get_gl_function("glReadPixels");
    if (!glReadPixels)
    {
        printf("Failed to load the OpenGL function \"glReadPixels\".\n");
        /* ret = GL_FALSE; */
    }

    glReleaseShaderCompiler = (PFNGLRELEASESHADERCOMPILERPROC)get_gl_function("glReleaseShaderCompiler");
    if (!glReleaseShaderCompiler)
    {
        printf("Failed to load the OpenGL function \"glReleaseShaderCompiler\".\n");
        /* ret = GL_FALSE; */
    }

    glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)get_gl_function("glRenderbufferStorage");
    if (!glRenderbufferStorage)
    {
        printf("Failed to load the OpenGL function \"glRenderbufferStorage\".\n");
        /* ret = GL_FALSE; */
    }

    glSampleCoverage = (PFNGLSAMPLECOVERAGEPROC)get_gl_function("glSampleCoverage");
    if (!glSampleCoverage)
    {
        printf("Failed to load the OpenGL function \"glSampleCoverage\".\n");
        /* ret = GL_FALSE; */
    }

    glScissor = (PFNGLSCISSORPROC)get_gl_function("glScissor");
    if (!glScissor)
    {
        printf("Failed to load the OpenGL function \"glScissor\".\n");
        /* ret = GL_FALSE; */
    }

    glShaderBinary = (PFNGLSHADERBINARYPROC)get_gl_function("glShaderBinary");
    if (!glShaderBinary)
    {
        printf("Failed to load the OpenGL function \"glShaderBinary\".\n");
        /* ret = GL_FALSE; */
    }

    glShaderSource = (PFNGLSHADERSOURCEPROC)get_gl_function("glShaderSource");
    if (!glShaderSource)
    {
        printf("Failed to load the OpenGL function \"glShaderSource\".\n");
        /* ret = GL_FALSE; */
    }

    glStencilFunc = (PFNGLSTENCILFUNCPROC)get_gl_function("glStencilFunc");
    if (!glStencilFunc)
    {
        printf("Failed to load the OpenGL function \"glStencilFunc\".\n");
        /* ret = GL_FALSE; */
    }

    glStencilFuncSeparate = (PFNGLSTENCILFUNCSEPARATEPROC)get_gl_function("glStencilFuncSeparate");
    if (!glStencilFuncSeparate)
    {
        printf("Failed to load the OpenGL function \"glStencilFuncSeparate\".\n");
        /* ret = GL_FALSE; */
    }

    glStencilMask = (PFNGLSTENCILMASKPROC)get_gl_function("glStencilMask");
    if (!glStencilMask)
    {
        printf("Failed to load the OpenGL function \"glStencilMask\".\n");
        /* ret = GL_FALSE; */
    }

    glStencilMaskSeparate = (PFNGLSTENCILMASKSEPARATEPROC)get_gl_function("glStencilMaskSeparate");
    if (!glStencilMaskSeparate)
    {
        printf("Failed to load the OpenGL function \"glStencilMaskSeparate\".\n");
        /* ret = GL_FALSE; */
    }

    glStencilOp = (PFNGLSTENCILOPPROC)get_gl_function("glStencilOp");
    if (!glStencilOp)
    {
        printf("Failed to load the OpenGL function \"glStencilOp\".\n");
        /* ret = GL_FALSE; */
    }

    glStencilOpSeparate = (PFNGLSTENCILOPSEPARATEPROC)get_gl_function("glStencilOpSeparate");
    if (!glStencilOpSeparate)
    {
        printf("Failed to load the OpenGL function \"glStencilOpSeparate\".\n");
        /* ret = GL_FALSE; */
    }

    glTexImage2D = (PFNGLTEXIMAGE2DPROC)get_gl_function("glTexImage2D");
    if (!glTexImage2D)
    {
        printf("Failed to load the OpenGL function \"glTexImage2D\".\n");
        /* ret = GL_FALSE; */
    }

    glTexParameterf = (PFNGLTEXPARAMETERFPROC)get_gl_function("glTexParameterf");
    if (!glTexParameterf)
    {
        printf("Failed to load the OpenGL function \"glTexParameterf\".\n");
        /* ret = GL_FALSE; */
    }

    glTexParameterfv = (PFNGLTEXPARAMETERFVPROC)get_gl_function("glTexParameterfv");
    if (!glTexParameterfv)
    {
        printf("Failed to load the OpenGL function \"glTexParameterfv\".\n");
        /* ret = GL_FALSE; */
    }

    glTexParameteri = (PFNGLTEXPARAMETERIPROC)get_gl_function("glTexParameteri");
    if (!glTexParameteri)
    {
        printf("Failed to load the OpenGL function \"glTexParameteri\".\n");
        /* ret = GL_FALSE; */
    }

    glTexParameteriv = (PFNGLTEXPARAMETERIVPROC)get_gl_function("glTexParameteriv");
    if (!glTexParameteriv)
    {
        printf("Failed to load the OpenGL function \"glTexParameteriv\".\n");
        /* ret = GL_FALSE; */
    }

    glTexSubImage2D = (PFNGLTEXSUBIMAGE2DPROC)get_gl_function("glTexSubImage2D");
    if (!glTexSubImage2D)
    {
        printf("Failed to load the OpenGL function \"glTexSubImage2D\".\n");
        /* ret = GL_FALSE; */
    }

    glUniform1f = (PFNGLUNIFORM1FPROC)get_gl_function("glUniform1f");
    if (!glUniform1f)
    {
        printf("Failed to load the OpenGL function \"glUniform1f\".\n");
        /* ret = GL_FALSE; */
    }

    glUniform1fv = (PFNGLUNIFORM1FVPROC)get_gl_function("glUniform1fv");
    if (!glUniform1fv)
    {
        printf("Failed to load the OpenGL function \"glUniform1fv\".\n");
        /* ret = GL_FALSE; */
    }

    glUniform1i = (PFNGLUNIFORM1IPROC)get_gl_function("glUniform1i");
    if (!glUniform1i)
    {
        printf("Failed to load the OpenGL function \"glUniform1i\".\n");
        /* ret = GL_FALSE; */
    }

    glUniform1iv = (PFNGLUNIFORM1IVPROC)get_gl_function("glUniform1iv");
    if (!glUniform1iv)
    {
        printf("Failed to load the OpenGL function \"glUniform1iv\".\n");
        /* ret = GL_FALSE; */
    }

    glUniform2f = (PFNGLUNIFORM2FPROC)get_gl_function("glUniform2f");
    if (!glUniform2f)
    {
        printf("Failed to load the OpenGL function \"glUniform2f\".\n");
        /* ret = GL_FALSE; */
    }

    glUniform2fv = (PFNGLUNIFORM2FVPROC)get_gl_function("glUniform2fv");
    if (!glUniform2fv)
    {
        printf("Failed to load the OpenGL function \"glUniform2fv\".\n");
        /* ret = GL_FALSE; */
    }

    glUniform2i = (PFNGLUNIFORM2IPROC)get_gl_function("glUniform2i");
    if (!glUniform2i)
    {
        printf("Failed to load the OpenGL function \"glUniform2i\".\n");
        /* ret = GL_FALSE; */
    }

    glUniform2iv = (PFNGLUNIFORM2IVPROC)get_gl_function("glUniform2iv");
    if (!glUniform2iv)
    {
        printf("Failed to load the OpenGL function \"glUniform2iv\".\n");
        /* ret = GL_FALSE; */
    }

    glUniform3f = (PFNGLUNIFORM3FPROC)get_gl_function("glUniform3f");
    if (!glUniform3f)
    {
        printf("Failed to load the OpenGL function \"glUniform3f\".\n");
        /* ret = GL_FALSE; */
    }

    glUniform3fv = (PFNGLUNIFORM3FVPROC)get_gl_function("glUniform3fv");
    if (!glUniform3fv)
    {
        printf("Failed to load the OpenGL function \"glUniform3fv\".\n");
        /* ret = GL_FALSE; */
    }

    glUniform3i = (PFNGLUNIFORM3IPROC)get_gl_function("glUniform3i");
    if (!glUniform3i)
    {
        printf("Failed to load the OpenGL function \"glUniform3i\".\n");
        /* ret = GL_FALSE; */
    }

    glUniform3iv = (PFNGLUNIFORM3IVPROC)get_gl_function("glUniform3iv");
    if (!glUniform3iv)
    {
        printf("Failed to load the OpenGL function \"glUniform3iv\".\n");
        /* ret = GL_FALSE; */
    }

    glUniform4f = (PFNGLUNIFORM4FPROC)get_gl_function("glUniform4f");
    if (!glUniform4f)
    {
        printf("Failed to load the OpenGL function \"glUniform4f\".\n");
        /* ret = GL_FALSE; */
    }

    glUniform4fv = (PFNGLUNIFORM4FVPROC)get_gl_function("glUniform4fv");
    if (!glUniform4fv)
    {
        printf("Failed to load the OpenGL function \"glUniform4fv\".\n");
        /* ret = GL_FALSE; */
    }

    glUniform4i = (PFNGLUNIFORM4IPROC)get_gl_function("glUniform4i");
    if (!glUniform4i)
    {
        printf("Failed to load the OpenGL function \"glUniform4i\".\n");
        /* ret = GL_FALSE; */
    }

    glUniform4iv = (PFNGLUNIFORM4IVPROC)get_gl_function("glUniform4iv");
    if (!glUniform4iv)
    {
        printf("Failed to load the OpenGL function \"glUniform4iv\".\n");
        /* ret = GL_FALSE; */
    }

    glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC)get_gl_function("glUniformMatrix2fv");
    if (!glUniformMatrix2fv)
    {
        printf("Failed to load the OpenGL function \"glUniformMatrix2fv\".\n");
        /* ret = GL_FALSE; */
    }

    glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)get_gl_function("glUniformMatrix3fv");
    if (!glUniformMatrix3fv)
    {
        printf("Failed to load the OpenGL function \"glUniformMatrix3fv\".\n");
        /* ret = GL_FALSE; */
    }

    glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)get_gl_function("glUniformMatrix4fv");
    if (!glUniformMatrix4fv)
    {
        printf("Failed to load the OpenGL function \"glUniformMatrix4fv\".\n");
        /* ret = GL_FALSE; */
    }

    glUseProgram = (PFNGLUSEPROGRAMPROC)get_gl_function("glUseProgram");
    if (!glUseProgram)
    {
        printf("Failed to load the OpenGL function \"glUseProgram\".\n");
        /* ret = GL_FALSE; */
    }

    glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)get_gl_function("glValidateProgram");
    if (!glValidateProgram)
    {
        printf("Failed to load the OpenGL function \"glValidateProgram\".\n");
        /* ret = GL_FALSE; */
    }

    glVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC)get_gl_function("glVertexAttrib1f");
    if (!glVertexAttrib1f)
    {
        printf("Failed to load the OpenGL function \"glVertexAttrib1f\".\n");
        /* ret = GL_FALSE; */
    }

    glVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC)get_gl_function("glVertexAttrib1fv");
    if (!glVertexAttrib1fv)
    {
        printf("Failed to load the OpenGL function \"glVertexAttrib1fv\".\n");
        /* ret = GL_FALSE; */
    }

    glVertexAttrib2f = (PFNGLVERTEXATTRIB2FPROC)get_gl_function("glVertexAttrib2f");
    if (!glVertexAttrib2f)
    {
        printf("Failed to load the OpenGL function \"glVertexAttrib2f\".\n");
        /* ret = GL_FALSE; */
    }

    glVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC)get_gl_function("glVertexAttrib2fv");
    if (!glVertexAttrib2fv)
    {
        printf("Failed to load the OpenGL function \"glVertexAttrib2fv\".\n");
        /* ret = GL_FALSE; */
    }

    glVertexAttrib3f = (PFNGLVERTEXATTRIB3FPROC)get_gl_function("glVertexAttrib3f");
    if (!glVertexAttrib3f)
    {
        printf("Failed to load the OpenGL function \"glVertexAttrib3f\".\n");
        /* ret = GL_FALSE; */
    }

    glVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC)get_gl_function("glVertexAttrib3fv");
    if (!glVertexAttrib3fv)
    {
        printf("Failed to load the OpenGL function \"glVertexAttrib3fv\".\n");
        /* ret = GL_FALSE; */
    }

    glVertexAttrib4f = (PFNGLVERTEXATTRIB4FPROC)get_gl_function("glVertexAttrib4f");
    if (!glVertexAttrib4f)
    {
        printf("Failed to load the OpenGL function \"glVertexAttrib4f\".\n");
        /* ret = GL_FALSE; */
    }

    glVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC)get_gl_function("glVertexAttrib4fv");
    if (!glVertexAttrib4fv)
    {
        printf("Failed to load the OpenGL function \"glVertexAttrib4fv\".\n");
        /* ret = GL_FALSE; */
    }

    glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)get_gl_function("glVertexAttribPointer");
    if (!glVertexAttribPointer)
    {
        printf("Failed to load the OpenGL function \"glVertexAttribPointer\".\n");
        /* ret = GL_FALSE; */
    }

    glViewport = (PFNGLVIEWPORTPROC)get_gl_function("glViewport");
    if (!glViewport)
    {
        printf("Failed to load the OpenGL function \"glViewport\".\n");
        /* ret = GL_FALSE; */
    }

    glReadBuffer = (PFNGLREADBUFFERPROC)get_gl_function("glReadBuffer");
    if (!glReadBuffer)
    {
        printf("Failed to load the OpenGL function \"glReadBuffer\".\n");
        /* ret = GL_FALSE; */
    }

    glDrawRangeElements = (PFNGLDRAWRANGEELEMENTSPROC)get_gl_function("glDrawRangeElements");
    if (!glDrawRangeElements)
    {
        printf("Failed to load the OpenGL function \"glDrawRangeElements\".\n");
        /* ret = GL_FALSE; */
    }

    glTexImage3D = (PFNGLTEXIMAGE3DPROC)get_gl_function("glTexImage3D");
    if (!glTexImage3D)
    {
        printf("Failed to load the OpenGL function \"glTexImage3D\".\n");
        /* ret = GL_FALSE; */
    }

    glTexSubImage3D = (PFNGLTEXSUBIMAGE3DPROC)get_gl_function("glTexSubImage3D");
    if (!glTexSubImage3D)
    {
        printf("Failed to load the OpenGL function \"glTexSubImage3D\".\n");
        /* ret = GL_FALSE; */
    }

    glCopyTexSubImage3D = (PFNGLCOPYTEXSUBIMAGE3DPROC)get_gl_function("glCopyTexSubImage3D");
    if (!glCopyTexSubImage3D)
    {
        printf("Failed to load the OpenGL function \"glCopyTexSubImage3D\".\n");
        /* ret = GL_FALSE; */
    }

    glCompressedTexImage3D = (PFNGLCOMPRESSEDTEXIMAGE3DPROC)get_gl_function("glCompressedTexImage3D");
    if (!glCompressedTexImage3D)
    {
        printf("Failed to load the OpenGL function \"glCompressedTexImage3D\".\n");
        /* ret = GL_FALSE; */
    }

    glCompressedTexSubImage3D = (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)get_gl_function("glCompressedTexSubImage3D");
    if (!glCompressedTexSubImage3D)
    {
        printf("Failed to load the OpenGL function \"glCompressedTexSubImage3D\".\n");
        /* ret = GL_FALSE; */
    }

    glGenQueries = (PFNGLGENQUERIESPROC)get_gl_function("glGenQueries");
    if (!glGenQueries)
    {
        printf("Failed to load the OpenGL function \"glGenQueries\".\n");
        /* ret = GL_FALSE; */
    }

    glDeleteQueries = (PFNGLDELETEQUERIESPROC)get_gl_function("glDeleteQueries");
    if (!glDeleteQueries)
    {
        printf("Failed to load the OpenGL function \"glDeleteQueries\".\n");
        /* ret = GL_FALSE; */
    }

    glIsQuery = (PFNGLISQUERYPROC)get_gl_function("glIsQuery");
    if (!glIsQuery)
    {
        printf("Failed to load the OpenGL function \"glIsQuery\".\n");
        /* ret = GL_FALSE; */
    }

    glBeginQuery = (PFNGLBEGINQUERYPROC)get_gl_function("glBeginQuery");
    if (!glBeginQuery)
    {
        printf("Failed to load the OpenGL function \"glBeginQuery\".\n");
        /* ret = GL_FALSE; */
    }

    glEndQuery = (PFNGLENDQUERYPROC)get_gl_function("glEndQuery");
    if (!glEndQuery)
    {
        printf("Failed to load the OpenGL function \"glEndQuery\".\n");
        /* ret = GL_FALSE; */
    }

    glGetQueryiv = (PFNGLGETQUERYIVPROC)get_gl_function("glGetQueryiv");
    if (!glGetQueryiv)
    {
        printf("Failed to load the OpenGL function \"glGetQueryiv\".\n");
        /* ret = GL_FALSE; */
    }

    glGetQueryObjectuiv = (PFNGLGETQUERYOBJECTUIVPROC)get_gl_function("glGetQueryObjectuiv");
    if (!glGetQueryObjectuiv)
    {
        printf("Failed to load the OpenGL function \"glGetQueryObjectuiv\".\n");
        /* ret = GL_FALSE; */
    }

    glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)get_gl_function("glUnmapBuffer");
    if (!glUnmapBuffer)
    {
        printf("Failed to load the OpenGL function \"glUnmapBuffer\".\n");
        /* ret = GL_FALSE; */
    }

    glGetBufferPointerv = (PFNGLGETBUFFERPOINTERVPROC)get_gl_function("glGetBufferPointerv");
    if (!glGetBufferPointerv)
    {
        printf("Failed to load the OpenGL function \"glGetBufferPointerv\".\n");
        /* ret = GL_FALSE; */
    }

    glDrawBuffers = (PFNGLDRAWBUFFERSPROC)get_gl_function("glDrawBuffers");
    if (!glDrawBuffers)
    {
        printf("Failed to load the OpenGL function \"glDrawBuffers\".\n");
        /* ret = GL_FALSE; */
    }

    glUniformMatrix2x3fv = (PFNGLUNIFORMMATRIX2X3FVPROC)get_gl_function("glUniformMatrix2x3fv");
    if (!glUniformMatrix2x3fv)
    {
        printf("Failed to load the OpenGL function \"glUniformMatrix2x3fv\".\n");
        /* ret = GL_FALSE; */
    }

    glUniformMatrix3x2fv = (PFNGLUNIFORMMATRIX3X2FVPROC)get_gl_function("glUniformMatrix3x2fv");
    if (!glUniformMatrix3x2fv)
    {
        printf("Failed to load the OpenGL function \"glUniformMatrix3x2fv\".\n");
        /* ret = GL_FALSE; */
    }

    glUniformMatrix2x4fv = (PFNGLUNIFORMMATRIX2X4FVPROC)get_gl_function("glUniformMatrix2x4fv");
    if (!glUniformMatrix2x4fv)
    {
        printf("Failed to load the OpenGL function \"glUniformMatrix2x4fv\".\n");
        /* ret = GL_FALSE; */
    }

    glUniformMatrix4x2fv = (PFNGLUNIFORMMATRIX4X2FVPROC)get_gl_function("glUniformMatrix4x2fv");
    if (!glUniformMatrix4x2fv)
    {
        printf("Failed to load the OpenGL function \"glUniformMatrix4x2fv\".\n");
        /* ret = GL_FALSE; */
    }

    glUniformMatrix3x4fv = (PFNGLUNIFORMMATRIX3X4FVPROC)get_gl_function("glUniformMatrix3x4fv");
    if (!glUniformMatrix3x4fv)
    {
        printf("Failed to load the OpenGL function \"glUniformMatrix3x4fv\".\n");
        /* ret = GL_FALSE; */
    }

    glUniformMatrix4x3fv = (PFNGLUNIFORMMATRIX4X3FVPROC)get_gl_function("glUniformMatrix4x3fv");
    if (!glUniformMatrix4x3fv)
    {
        printf("Failed to load the OpenGL function \"glUniformMatrix4x3fv\".\n");
        /* ret = GL_FALSE; */
    }

    glBlitFramebuffer = (PFNGLBLITFRAMEBUFFERPROC)get_gl_function("glBlitFramebuffer");
    if (!glBlitFramebuffer)
    {
        printf("Failed to load the OpenGL function \"glBlitFramebuffer\".\n");
        /* ret = GL_FALSE; */
    }

    glRenderbufferStorageMultisample = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC)get_gl_function("glRenderbufferStorageMultisample");
    if (!glRenderbufferStorageMultisample)
    {
        printf("Failed to load the OpenGL function \"glRenderbufferStorageMultisample\".\n");
        /* ret = GL_FALSE; */
    }

    glFramebufferTextureLayer = (PFNGLFRAMEBUFFERTEXTURELAYERPROC)get_gl_function("glFramebufferTextureLayer");
    if (!glFramebufferTextureLayer)
    {
        printf("Failed to load the OpenGL function \"glFramebufferTextureLayer\".\n");
        /* ret = GL_FALSE; */
    }

    glMapBufferRange = (PFNGLMAPBUFFERRANGEPROC)get_gl_function("glMapBufferRange");
    if (!glMapBufferRange)
    {
        printf("Failed to load the OpenGL function \"glMapBufferRange\".\n");
        /* ret = GL_FALSE; */
    }

    glFlushMappedBufferRange = (PFNGLFLUSHMAPPEDBUFFERRANGEPROC)get_gl_function("glFlushMappedBufferRange");
    if (!glFlushMappedBufferRange)
    {
        printf("Failed to load the OpenGL function \"glFlushMappedBufferRange\".\n");
        /* ret = GL_FALSE; */
    }

    glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)get_gl_function("glBindVertexArray");
    if (!glBindVertexArray)
    {
        printf("Failed to load the OpenGL function \"glBindVertexArray\".\n");
        /* ret = GL_FALSE; */
    }

    glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)get_gl_function("glDeleteVertexArrays");
    if (!glDeleteVertexArrays)
    {
        printf("Failed to load the OpenGL function \"glDeleteVertexArrays\".\n");
        /* ret = GL_FALSE; */
    }

    glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)get_gl_function("glGenVertexArrays");
    if (!glGenVertexArrays)
    {
        printf("Failed to load the OpenGL function \"glGenVertexArrays\".\n");
        /* ret = GL_FALSE; */
    }

    glIsVertexArray = (PFNGLISVERTEXARRAYPROC)get_gl_function("glIsVertexArray");
    if (!glIsVertexArray)
    {
        printf("Failed to load the OpenGL function \"glIsVertexArray\".\n");
        /* ret = GL_FALSE; */
    }

    glGetIntegeri_v = (PFNGLGETINTEGERI_VPROC)get_gl_function("glGetIntegeri_v");
    if (!glGetIntegeri_v)
    {
        printf("Failed to load the OpenGL function \"glGetIntegeri_v\".\n");
        /* ret = GL_FALSE; */
    }

    glBeginTransformFeedback = (PFNGLBEGINTRANSFORMFEEDBACKPROC)get_gl_function("glBeginTransformFeedback");
    if (!glBeginTransformFeedback)
    {
        printf("Failed to load the OpenGL function \"glBeginTransformFeedback\".\n");
        /* ret = GL_FALSE; */
    }

    glEndTransformFeedback = (PFNGLENDTRANSFORMFEEDBACKPROC)get_gl_function("glEndTransformFeedback");
    if (!glEndTransformFeedback)
    {
        printf("Failed to load the OpenGL function \"glEndTransformFeedback\".\n");
        /* ret = GL_FALSE; */
    }

    glBindBufferRange = (PFNGLBINDBUFFERRANGEPROC)get_gl_function("glBindBufferRange");
    if (!glBindBufferRange)
    {
        printf("Failed to load the OpenGL function \"glBindBufferRange\".\n");
        /* ret = GL_FALSE; */
    }

    glBindBufferBase = (PFNGLBINDBUFFERBASEPROC)get_gl_function("glBindBufferBase");
    if (!glBindBufferBase)
    {
        printf("Failed to load the OpenGL function \"glBindBufferBase\".\n");
        /* ret = GL_FALSE; */
    }

    glTransformFeedbackVaryings = (PFNGLTRANSFORMFEEDBACKVARYINGSPROC)get_gl_function("glTransformFeedbackVaryings");
    if (!glTransformFeedbackVaryings)
    {
        printf("Failed to load the OpenGL function \"glTransformFeedbackVaryings\".\n");
        /* ret = GL_FALSE; */
    }

    glGetTransformFeedbackVarying = (PFNGLGETTRANSFORMFEEDBACKVARYINGPROC)get_gl_function("glGetTransformFeedbackVarying");
    if (!glGetTransformFeedbackVarying)
    {
        printf("Failed to load the OpenGL function \"glGetTransformFeedbackVarying\".\n");
        /* ret = GL_FALSE; */
    }

    glVertexAttribIPointer = (PFNGLVERTEXATTRIBIPOINTERPROC)get_gl_function("glVertexAttribIPointer");
    if (!glVertexAttribIPointer)
    {
        printf("Failed to load the OpenGL function \"glVertexAttribIPointer\".\n");
        /* ret = GL_FALSE; */
    }

    glGetVertexAttribIiv = (PFNGLGETVERTEXATTRIBIIVPROC)get_gl_function("glGetVertexAttribIiv");
    if (!glGetVertexAttribIiv)
    {
        printf("Failed to load the OpenGL function \"glGetVertexAttribIiv\".\n");
        /* ret = GL_FALSE; */
    }

    glGetVertexAttribIuiv = (PFNGLGETVERTEXATTRIBIUIVPROC)get_gl_function("glGetVertexAttribIuiv");
    if (!glGetVertexAttribIuiv)
    {
        printf("Failed to load the OpenGL function \"glGetVertexAttribIuiv\".\n");
        /* ret = GL_FALSE; */
    }

    glVertexAttribI4i = (PFNGLVERTEXATTRIBI4IPROC)get_gl_function("glVertexAttribI4i");
    if (!glVertexAttribI4i)
    {
        printf("Failed to load the OpenGL function \"glVertexAttribI4i\".\n");
        /* ret = GL_FALSE; */
    }

    glVertexAttribI4ui = (PFNGLVERTEXATTRIBI4UIPROC)get_gl_function("glVertexAttribI4ui");
    if (!glVertexAttribI4ui)
    {
        printf("Failed to load the OpenGL function \"glVertexAttribI4ui\".\n");
        /* ret = GL_FALSE; */
    }

    glVertexAttribI4iv = (PFNGLVERTEXATTRIBI4IVPROC)get_gl_function("glVertexAttribI4iv");
    if (!glVertexAttribI4iv)
    {
        printf("Failed to load the OpenGL function \"glVertexAttribI4iv\".\n");
        /* ret = GL_FALSE; */
    }

    glVertexAttribI4uiv = (PFNGLVERTEXATTRIBI4UIVPROC)get_gl_function("glVertexAttribI4uiv");
    if (!glVertexAttribI4uiv)
    {
        printf("Failed to load the OpenGL function \"glVertexAttribI4uiv\".\n");
        /* ret = GL_FALSE; */
    }

    glGetUniformuiv = (PFNGLGETUNIFORMUIVPROC)get_gl_function("glGetUniformuiv");
    if (!glGetUniformuiv)
    {
        printf("Failed to load the OpenGL function \"glGetUniformuiv\".\n");
        /* ret = GL_FALSE; */
    }

    glGetFragDataLocation = (PFNGLGETFRAGDATALOCATIONPROC)get_gl_function("glGetFragDataLocation");
    if (!glGetFragDataLocation)
    {
        printf("Failed to load the OpenGL function \"glGetFragDataLocation\".\n");
        /* ret = GL_FALSE; */
    }

    glUniform1ui = (PFNGLUNIFORM1UIPROC)get_gl_function("glUniform1ui");
    if (!glUniform1ui)
    {
        printf("Failed to load the OpenGL function \"glUniform1ui\".\n");
        /* ret = GL_FALSE; */
    }

    glUniform2ui = (PFNGLUNIFORM2UIPROC)get_gl_function("glUniform2ui");
    if (!glUniform2ui)
    {
        printf("Failed to load the OpenGL function \"glUniform2ui\".\n");
        /* ret = GL_FALSE; */
    }

    glUniform3ui = (PFNGLUNIFORM3UIPROC)get_gl_function("glUniform3ui");
    if (!glUniform3ui)
    {
        printf("Failed to load the OpenGL function \"glUniform3ui\".\n");
        /* ret = GL_FALSE; */
    }

    glUniform4ui = (PFNGLUNIFORM4UIPROC)get_gl_function("glUniform4ui");
    if (!glUniform4ui)
    {
        printf("Failed to load the OpenGL function \"glUniform4ui\".\n");
        /* ret = GL_FALSE; */
    }

    glUniform1uiv = (PFNGLUNIFORM1UIVPROC)get_gl_function("glUniform1uiv");
    if (!glUniform1uiv)
    {
        printf("Failed to load the OpenGL function \"glUniform1uiv\".\n");
        /* ret = GL_FALSE; */
    }

    glUniform2uiv = (PFNGLUNIFORM2UIVPROC)get_gl_function("glUniform2uiv");
    if (!glUniform2uiv)
    {
        printf("Failed to load the OpenGL function \"glUniform2uiv\".\n");
        /* ret = GL_FALSE; */
    }

    glUniform3uiv = (PFNGLUNIFORM3UIVPROC)get_gl_function("glUniform3uiv");
    if (!glUniform3uiv)
    {
        printf("Failed to load the OpenGL function \"glUniform3uiv\".\n");
        /* ret = GL_FALSE; */
    }

    glUniform4uiv = (PFNGLUNIFORM4UIVPROC)get_gl_function("glUniform4uiv");
    if (!glUniform4uiv)
    {
        printf("Failed to load the OpenGL function \"glUniform4uiv\".\n");
        /* ret = GL_FALSE; */
    }

    glClearBufferiv = (PFNGLCLEARBUFFERIVPROC)get_gl_function("glClearBufferiv");
    if (!glClearBufferiv)
    {
        printf("Failed to load the OpenGL function \"glClearBufferiv\".\n");
        /* ret = GL_FALSE; */
    }

    glClearBufferuiv = (PFNGLCLEARBUFFERUIVPROC)get_gl_function("glClearBufferuiv");
    if (!glClearBufferuiv)
    {
        printf("Failed to load the OpenGL function \"glClearBufferuiv\".\n");
        /* ret = GL_FALSE; */
    }

    glClearBufferfv = (PFNGLCLEARBUFFERFVPROC)get_gl_function("glClearBufferfv");
    if (!glClearBufferfv)
    {
        printf("Failed to load the OpenGL function \"glClearBufferfv\".\n");
        /* ret = GL_FALSE; */
    }

    glClearBufferfi = (PFNGLCLEARBUFFERFIPROC)get_gl_function("glClearBufferfi");
    if (!glClearBufferfi)
    {
        printf("Failed to load the OpenGL function \"glClearBufferfi\".\n");
        /* ret = GL_FALSE; */
    }

    glGetStringi = (PFNGLGETSTRINGIPROC)get_gl_function("glGetStringi");
    if (!glGetStringi)
    {
        printf("Failed to load the OpenGL function \"glGetStringi\".\n");
        /* ret = GL_FALSE; */
    }

    glCopyBufferSubData = (PFNGLCOPYBUFFERSUBDATAPROC)get_gl_function("glCopyBufferSubData");
    if (!glCopyBufferSubData)
    {
        printf("Failed to load the OpenGL function \"glCopyBufferSubData\".\n");
        /* ret = GL_FALSE; */
    }

    glGetUniformIndices = (PFNGLGETUNIFORMINDICESPROC)get_gl_function("glGetUniformIndices");
    if (!glGetUniformIndices)
    {
        printf("Failed to load the OpenGL function \"glGetUniformIndices\".\n");
        /* ret = GL_FALSE; */
    }

    glGetActiveUniformsiv = (PFNGLGETACTIVEUNIFORMSIVPROC)get_gl_function("glGetActiveUniformsiv");
    if (!glGetActiveUniformsiv)
    {
        printf("Failed to load the OpenGL function \"glGetActiveUniformsiv\".\n");
        /* ret = GL_FALSE; */
    }

    glGetUniformBlockIndex = (PFNGLGETUNIFORMBLOCKINDEXPROC)get_gl_function("glGetUniformBlockIndex");
    if (!glGetUniformBlockIndex)
    {
        printf("Failed to load the OpenGL function \"glGetUniformBlockIndex\".\n");
        /* ret = GL_FALSE; */
    }

    glGetActiveUniformBlockiv = (PFNGLGETACTIVEUNIFORMBLOCKIVPROC)get_gl_function("glGetActiveUniformBlockiv");
    if (!glGetActiveUniformBlockiv)
    {
        printf("Failed to load the OpenGL function \"glGetActiveUniformBlockiv\".\n");
        /* ret = GL_FALSE; */
    }

    glGetActiveUniformBlockName = (PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC)get_gl_function("glGetActiveUniformBlockName");
    if (!glGetActiveUniformBlockName)
    {
        printf("Failed to load the OpenGL function \"glGetActiveUniformBlockName\".\n");
        /* ret = GL_FALSE; */
    }

    glUniformBlockBinding = (PFNGLUNIFORMBLOCKBINDINGPROC)get_gl_function("glUniformBlockBinding");
    if (!glUniformBlockBinding)
    {
        printf("Failed to load the OpenGL function \"glUniformBlockBinding\".\n");
        /* ret = GL_FALSE; */
    }

    glDrawArraysInstanced = (PFNGLDRAWARRAYSINSTANCEDPROC)get_gl_function("glDrawArraysInstanced");
    if (!glDrawArraysInstanced)
    {
        printf("Failed to load the OpenGL function \"glDrawArraysInstanced\".\n");
        /* ret = GL_FALSE; */
    }

    glDrawElementsInstanced = (PFNGLDRAWELEMENTSINSTANCEDPROC)get_gl_function("glDrawElementsInstanced");
    if (!glDrawElementsInstanced)
    {
        printf("Failed to load the OpenGL function \"glDrawElementsInstanced\".\n");
        /* ret = GL_FALSE; */
    }

    glFenceSync = (PFNGLFENCESYNCPROC)get_gl_function("glFenceSync");
    if (!glFenceSync)
    {
        printf("Failed to load the OpenGL function \"glFenceSync\".\n");
        /* ret = GL_FALSE; */
    }

    glIsSync = (PFNGLISSYNCPROC)get_gl_function("glIsSync");
    if (!glIsSync)
    {
        printf("Failed to load the OpenGL function \"glIsSync\".\n");
        /* ret = GL_FALSE; */
    }

    glDeleteSync = (PFNGLDELETESYNCPROC)get_gl_function("glDeleteSync");
    if (!glDeleteSync)
    {
        printf("Failed to load the OpenGL function \"glDeleteSync\".\n");
        /* ret = GL_FALSE; */
    }

    glClientWaitSync = (PFNGLCLIENTWAITSYNCPROC)get_gl_function("glClientWaitSync");
    if (!glClientWaitSync)
    {
        printf("Failed to load the OpenGL function \"glClientWaitSync\".\n");
        /* ret = GL_FALSE; */
    }

    glWaitSync = (PFNGLWAITSYNCPROC)get_gl_function("glWaitSync");
    if (!glWaitSync)
    {
        printf("Failed to load the OpenGL function \"glWaitSync\".\n");
        /* ret = GL_FALSE; */
    }

    glGetInteger64v = (PFNGLGETINTEGER64VPROC)get_gl_function("glGetInteger64v");
    if (!glGetInteger64v)
    {
        printf("Failed to load the OpenGL function \"glGetInteger64v\".\n");
        /* ret = GL_FALSE; */
    }

    glGetSynciv = (PFNGLGETSYNCIVPROC)get_gl_function("glGetSynciv");
    if (!glGetSynciv)
    {
        printf("Failed to load the OpenGL function \"glGetSynciv\".\n");
        /* ret = GL_FALSE; */
    }

    glGetInteger64i_v = (PFNGLGETINTEGER64I_VPROC)get_gl_function("glGetInteger64i_v");
    if (!glGetInteger64i_v)
    {
        printf("Failed to load the OpenGL function \"glGetInteger64i_v\".\n");
        /* ret = GL_FALSE; */
    }

    glGetBufferParameteri64v = (PFNGLGETBUFFERPARAMETERI64VPROC)get_gl_function("glGetBufferParameteri64v");
    if (!glGetBufferParameteri64v)
    {
        printf("Failed to load the OpenGL function \"glGetBufferParameteri64v\".\n");
        /* ret = GL_FALSE; */
    }

    glGenSamplers = (PFNGLGENSAMPLERSPROC)get_gl_function("glGenSamplers");
    if (!glGenSamplers)
    {
        printf("Failed to load the OpenGL function \"glGenSamplers\".\n");
        /* ret = GL_FALSE; */
    }

    glDeleteSamplers = (PFNGLDELETESAMPLERSPROC)get_gl_function("glDeleteSamplers");
    if (!glDeleteSamplers)
    {
        printf("Failed to load the OpenGL function \"glDeleteSamplers\".\n");
        /* ret = GL_FALSE; */
    }

    glIsSampler = (PFNGLISSAMPLERPROC)get_gl_function("glIsSampler");
    if (!glIsSampler)
    {
        printf("Failed to load the OpenGL function \"glIsSampler\".\n");
        /* ret = GL_FALSE; */
    }

    glBindSampler = (PFNGLBINDSAMPLERPROC)get_gl_function("glBindSampler");
    if (!glBindSampler)
    {
        printf("Failed to load the OpenGL function \"glBindSampler\".\n");
        /* ret = GL_FALSE; */
    }

    glSamplerParameteri = (PFNGLSAMPLERPARAMETERIPROC)get_gl_function("glSamplerParameteri");
    if (!glSamplerParameteri)
    {
        printf("Failed to load the OpenGL function \"glSamplerParameteri\".\n");
        /* ret = GL_FALSE; */
    }

    glSamplerParameteriv = (PFNGLSAMPLERPARAMETERIVPROC)get_gl_function("glSamplerParameteriv");
    if (!glSamplerParameteriv)
    {
        printf("Failed to load the OpenGL function \"glSamplerParameteriv\".\n");
        /* ret = GL_FALSE; */
    }

    glSamplerParameterf = (PFNGLSAMPLERPARAMETERFPROC)get_gl_function("glSamplerParameterf");
    if (!glSamplerParameterf)
    {
        printf("Failed to load the OpenGL function \"glSamplerParameterf\".\n");
        /* ret = GL_FALSE; */
    }

    glSamplerParameterfv = (PFNGLSAMPLERPARAMETERFVPROC)get_gl_function("glSamplerParameterfv");
    if (!glSamplerParameterfv)
    {
        printf("Failed to load the OpenGL function \"glSamplerParameterfv\".\n");
        /* ret = GL_FALSE; */
    }

    glGetSamplerParameteriv = (PFNGLGETSAMPLERPARAMETERIVPROC)get_gl_function("glGetSamplerParameteriv");
    if (!glGetSamplerParameteriv)
    {
        printf("Failed to load the OpenGL function \"glGetSamplerParameteriv\".\n");
        /* ret = GL_FALSE; */
    }

    glGetSamplerParameterfv = (PFNGLGETSAMPLERPARAMETERFVPROC)get_gl_function("glGetSamplerParameterfv");
    if (!glGetSamplerParameterfv)
    {
        printf("Failed to load the OpenGL function \"glGetSamplerParameterfv\".\n");
        /* ret = GL_FALSE; */
    }

    glVertexAttribDivisor = (PFNGLVERTEXATTRIBDIVISORPROC)get_gl_function("glVertexAttribDivisor");
    if (!glVertexAttribDivisor)
    {
        printf("Failed to load the OpenGL function \"glVertexAttribDivisor\".\n");
        /* ret = GL_FALSE; */
    }

    glBindTransformFeedback = (PFNGLBINDTRANSFORMFEEDBACKPROC)get_gl_function("glBindTransformFeedback");
    if (!glBindTransformFeedback)
    {
        printf("Failed to load the OpenGL function \"glBindTransformFeedback\".\n");
        /* ret = GL_FALSE; */
    }

    glDeleteTransformFeedbacks = (PFNGLDELETETRANSFORMFEEDBACKSPROC)get_gl_function("glDeleteTransformFeedbacks");
    if (!glDeleteTransformFeedbacks)
    {
        printf("Failed to load the OpenGL function \"glDeleteTransformFeedbacks\".\n");
        /* ret = GL_FALSE; */
    }

    glGenTransformFeedbacks = (PFNGLGENTRANSFORMFEEDBACKSPROC)get_gl_function("glGenTransformFeedbacks");
    if (!glGenTransformFeedbacks)
    {
        printf("Failed to load the OpenGL function \"glGenTransformFeedbacks\".\n");
        /* ret = GL_FALSE; */
    }

    glIsTransformFeedback = (PFNGLISTRANSFORMFEEDBACKPROC)get_gl_function("glIsTransformFeedback");
    if (!glIsTransformFeedback)
    {
        printf("Failed to load the OpenGL function \"glIsTransformFeedback\".\n");
        /* ret = GL_FALSE; */
    }

    glPauseTransformFeedback = (PFNGLPAUSETRANSFORMFEEDBACKPROC)get_gl_function("glPauseTransformFeedback");
    if (!glPauseTransformFeedback)
    {
        printf("Failed to load the OpenGL function \"glPauseTransformFeedback\".\n");
        /* ret = GL_FALSE; */
    }

    glResumeTransformFeedback = (PFNGLRESUMETRANSFORMFEEDBACKPROC)get_gl_function("glResumeTransformFeedback");
    if (!glResumeTransformFeedback)
    {
        printf("Failed to load the OpenGL function \"glResumeTransformFeedback\".\n");
        /* ret = GL_FALSE; */
    }

    glGetProgramBinary = (PFNGLGETPROGRAMBINARYPROC)get_gl_function("glGetProgramBinary");
    if (!glGetProgramBinary)
    {
        printf("Failed to load the OpenGL function \"glGetProgramBinary\".\n");
        /* ret = GL_FALSE; */
    }

    glProgramBinary = (PFNGLPROGRAMBINARYPROC)get_gl_function("glProgramBinary");
    if (!glProgramBinary)
    {
        printf("Failed to load the OpenGL function \"glProgramBinary\".\n");
        /* ret = GL_FALSE; */
    }

    glProgramParameteri = (PFNGLPROGRAMPARAMETERIPROC)get_gl_function("glProgramParameteri");
    if (!glProgramParameteri)
    {
        printf("Failed to load the OpenGL function \"glProgramParameteri\".\n");
        /* ret = GL_FALSE; */
    }

    glInvalidateFramebuffer = (PFNGLINVALIDATEFRAMEBUFFERPROC)get_gl_function("glInvalidateFramebuffer");
    if (!glInvalidateFramebuffer)
    {
        printf("Failed to load the OpenGL function \"glInvalidateFramebuffer\".\n");
        /* ret = GL_FALSE; */
    }

    glInvalidateSubFramebuffer = (PFNGLINVALIDATESUBFRAMEBUFFERPROC)get_gl_function("glInvalidateSubFramebuffer");
    if (!glInvalidateSubFramebuffer)
    {
        printf("Failed to load the OpenGL function \"glInvalidateSubFramebuffer\".\n");
        /* ret = GL_FALSE; */
    }

    glTexStorage2D = (PFNGLTEXSTORAGE2DPROC)get_gl_function("glTexStorage2D");
    if (!glTexStorage2D)
    {
        printf("Failed to load the OpenGL function \"glTexStorage2D\".\n");
        /* ret = GL_FALSE; */
    }

    glTexStorage3D = (PFNGLTEXSTORAGE3DPROC)get_gl_function("glTexStorage3D");
    if (!glTexStorage3D)
    {
        printf("Failed to load the OpenGL function \"glTexStorage3D\".\n");
        /* ret = GL_FALSE; */
    }

    glGetInternalformativ = (PFNGLGETINTERNALFORMATIVPROC)get_gl_function("glGetInternalformativ");
    if (!glGetInternalformativ)
    {
        printf("Failed to load the OpenGL function \"glGetInternalformativ\".\n");
        /* ret = GL_FALSE; */
    }

    
    return ret;
}

/*-------------------------------------
 * OpenGL Function Declarations (static)
-------------------------------------*/
PFNGLACTIVETEXTUREPROC glActiveTexture;

PFNGLATTACHSHADERPROC glAttachShader;

PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;

PFNGLBINDBUFFERPROC glBindBuffer;

PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;

PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer;

PFNGLBINDTEXTUREPROC glBindTexture;

PFNGLBLENDCOLORPROC glBlendColor;

PFNGLBLENDEQUATIONPROC glBlendEquation;

PFNGLBLENDEQUATIONSEPARATEPROC glBlendEquationSeparate;

PFNGLBLENDFUNCPROC glBlendFunc;

PFNGLBLENDFUNCSEPARATEPROC glBlendFuncSeparate;

PFNGLBUFFERDATAPROC glBufferData;

PFNGLBUFFERSUBDATAPROC glBufferSubData;

PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus;

PFNGLCLEARPROC glClear;

PFNGLCLEARCOLORPROC glClearColor;

PFNGLCLEARDEPTHFPROC glClearDepthf;

PFNGLCLEARSTENCILPROC glClearStencil;

PFNGLCOLORMASKPROC glColorMask;

PFNGLCOMPILESHADERPROC glCompileShader;

PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D;

PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glCompressedTexSubImage2D;

PFNGLCOPYTEXIMAGE2DPROC glCopyTexImage2D;

PFNGLCOPYTEXSUBIMAGE2DPROC glCopyTexSubImage2D;

PFNGLCREATEPROGRAMPROC glCreateProgram;

PFNGLCREATESHADERPROC glCreateShader;

PFNGLCULLFACEPROC glCullFace;

PFNGLDELETEBUFFERSPROC glDeleteBuffers;

PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers;

PFNGLDELETEPROGRAMPROC glDeleteProgram;

PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffers;

PFNGLDELETESHADERPROC glDeleteShader;

PFNGLDELETETEXTURESPROC glDeleteTextures;

PFNGLDEPTHFUNCPROC glDepthFunc;

PFNGLDEPTHMASKPROC glDepthMask;

PFNGLDEPTHRANGEFPROC glDepthRangef;

PFNGLDETACHSHADERPROC glDetachShader;

PFNGLDISABLEPROC glDisable;

PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;

PFNGLDRAWARRAYSPROC glDrawArrays;

PFNGLDRAWELEMENTSPROC glDrawElements;

PFNGLENABLEPROC glEnable;

PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;

PFNGLFINISHPROC glFinish;

PFNGLFLUSHPROC glFlush;

PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer;

PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D;

PFNGLFRONTFACEPROC glFrontFace;

PFNGLGENBUFFERSPROC glGenBuffers;

PFNGLGENERATEMIPMAPPROC glGenerateMipmap;

PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;

PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers;

PFNGLGENTEXTURESPROC glGenTextures;

PFNGLGETACTIVEATTRIBPROC glGetActiveAttrib;

PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform;

PFNGLGETATTACHEDSHADERSPROC glGetAttachedShaders;

PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;

PFNGLGETBOOLEANVPROC glGetBooleanv;

PFNGLGETBUFFERPARAMETERIVPROC glGetBufferParameteriv;

PFNGLGETERRORPROC glGetError;

PFNGLGETFLOATVPROC glGetFloatv;

PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glGetFramebufferAttachmentParameteriv;

PFNGLGETINTEGERVPROC glGetIntegerv;

PFNGLGETPROGRAMIVPROC glGetProgramiv;

PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;

PFNGLGETRENDERBUFFERPARAMETERIVPROC glGetRenderbufferParameteriv;

PFNGLGETSHADERIVPROC glGetShaderiv;

PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;

PFNGLGETSHADERPRECISIONFORMATPROC glGetShaderPrecisionFormat;

PFNGLGETSHADERSOURCEPROC glGetShaderSource;

PFNGLGETSTRINGPROC glGetString;

PFNGLGETTEXPARAMETERFVPROC glGetTexParameterfv;

PFNGLGETTEXPARAMETERIVPROC glGetTexParameteriv;

PFNGLGETUNIFORMFVPROC glGetUniformfv;

PFNGLGETUNIFORMIVPROC glGetUniformiv;

PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;

PFNGLGETVERTEXATTRIBFVPROC glGetVertexAttribfv;

PFNGLGETVERTEXATTRIBIVPROC glGetVertexAttribiv;

PFNGLGETVERTEXATTRIBPOINTERVPROC glGetVertexAttribPointerv;

PFNGLHINTPROC glHint;

PFNGLISBUFFERPROC glIsBuffer;

PFNGLISENABLEDPROC glIsEnabled;

PFNGLISFRAMEBUFFERPROC glIsFramebuffer;

PFNGLISPROGRAMPROC glIsProgram;

PFNGLISRENDERBUFFERPROC glIsRenderbuffer;

PFNGLISSHADERPROC glIsShader;

PFNGLISTEXTUREPROC glIsTexture;

PFNGLLINEWIDTHPROC glLineWidth;

PFNGLLINKPROGRAMPROC glLinkProgram;

PFNGLPIXELSTOREIPROC glPixelStorei;

PFNGLPOLYGONOFFSETPROC glPolygonOffset;

PFNGLREADPIXELSPROC glReadPixels;

PFNGLRELEASESHADERCOMPILERPROC glReleaseShaderCompiler;

PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage;

PFNGLSAMPLECOVERAGEPROC glSampleCoverage;

PFNGLSCISSORPROC glScissor;

PFNGLSHADERBINARYPROC glShaderBinary;

PFNGLSHADERSOURCEPROC glShaderSource;

PFNGLSTENCILFUNCPROC glStencilFunc;

PFNGLSTENCILFUNCSEPARATEPROC glStencilFuncSeparate;

PFNGLSTENCILMASKPROC glStencilMask;

PFNGLSTENCILMASKSEPARATEPROC glStencilMaskSeparate;

PFNGLSTENCILOPPROC glStencilOp;

PFNGLSTENCILOPSEPARATEPROC glStencilOpSeparate;

PFNGLTEXIMAGE2DPROC glTexImage2D;

PFNGLTEXPARAMETERFPROC glTexParameterf;

PFNGLTEXPARAMETERFVPROC glTexParameterfv;

PFNGLTEXPARAMETERIPROC glTexParameteri;

PFNGLTEXPARAMETERIVPROC glTexParameteriv;

PFNGLTEXSUBIMAGE2DPROC glTexSubImage2D;

PFNGLUNIFORM1FPROC glUniform1f;

PFNGLUNIFORM1FVPROC glUniform1fv;

PFNGLUNIFORM1IPROC glUniform1i;

PFNGLUNIFORM1IVPROC glUniform1iv;

PFNGLUNIFORM2FPROC glUniform2f;

PFNGLUNIFORM2FVPROC glUniform2fv;

PFNGLUNIFORM2IPROC glUniform2i;

PFNGLUNIFORM2IVPROC glUniform2iv;

PFNGLUNIFORM3FPROC glUniform3f;

PFNGLUNIFORM3FVPROC glUniform3fv;

PFNGLUNIFORM3IPROC glUniform3i;

PFNGLUNIFORM3IVPROC glUniform3iv;

PFNGLUNIFORM4FPROC glUniform4f;

PFNGLUNIFORM4FVPROC glUniform4fv;

PFNGLUNIFORM4IPROC glUniform4i;

PFNGLUNIFORM4IVPROC glUniform4iv;

PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv;

PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv;

PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;

PFNGLUSEPROGRAMPROC glUseProgram;

PFNGLVALIDATEPROGRAMPROC glValidateProgram;

PFNGLVERTEXATTRIB1FPROC glVertexAttrib1f;

PFNGLVERTEXATTRIB1FVPROC glVertexAttrib1fv;

PFNGLVERTEXATTRIB2FPROC glVertexAttrib2f;

PFNGLVERTEXATTRIB2FVPROC glVertexAttrib2fv;

PFNGLVERTEXATTRIB3FPROC glVertexAttrib3f;

PFNGLVERTEXATTRIB3FVPROC glVertexAttrib3fv;

PFNGLVERTEXATTRIB4FPROC glVertexAttrib4f;

PFNGLVERTEXATTRIB4FVPROC glVertexAttrib4fv;

PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;

PFNGLVIEWPORTPROC glViewport;

PFNGLREADBUFFERPROC glReadBuffer;

PFNGLDRAWRANGEELEMENTSPROC glDrawRangeElements;

PFNGLTEXIMAGE3DPROC glTexImage3D;

PFNGLTEXSUBIMAGE3DPROC glTexSubImage3D;

PFNGLCOPYTEXSUBIMAGE3DPROC glCopyTexSubImage3D;

PFNGLCOMPRESSEDTEXIMAGE3DPROC glCompressedTexImage3D;

PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC glCompressedTexSubImage3D;

PFNGLGENQUERIESPROC glGenQueries;

PFNGLDELETEQUERIESPROC glDeleteQueries;

PFNGLISQUERYPROC glIsQuery;

PFNGLBEGINQUERYPROC glBeginQuery;

PFNGLENDQUERYPROC glEndQuery;

PFNGLGETQUERYIVPROC glGetQueryiv;

PFNGLGETQUERYOBJECTUIVPROC glGetQueryObjectuiv;

PFNGLUNMAPBUFFERPROC glUnmapBuffer;

PFNGLGETBUFFERPOINTERVPROC glGetBufferPointerv;

PFNGLDRAWBUFFERSPROC glDrawBuffers;

PFNGLUNIFORMMATRIX2X3FVPROC glUniformMatrix2x3fv;

PFNGLUNIFORMMATRIX3X2FVPROC glUniformMatrix3x2fv;

PFNGLUNIFORMMATRIX2X4FVPROC glUniformMatrix2x4fv;

PFNGLUNIFORMMATRIX4X2FVPROC glUniformMatrix4x2fv;

PFNGLUNIFORMMATRIX3X4FVPROC glUniformMatrix3x4fv;

PFNGLUNIFORMMATRIX4X3FVPROC glUniformMatrix4x3fv;

PFNGLBLITFRAMEBUFFERPROC glBlitFramebuffer;

PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC glRenderbufferStorageMultisample;

PFNGLFRAMEBUFFERTEXTURELAYERPROC glFramebufferTextureLayer;

PFNGLMAPBUFFERRANGEPROC glMapBufferRange;

PFNGLFLUSHMAPPEDBUFFERRANGEPROC glFlushMappedBufferRange;

PFNGLBINDVERTEXARRAYPROC glBindVertexArray;

PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;

PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;

PFNGLISVERTEXARRAYPROC glIsVertexArray;

PFNGLGETINTEGERI_VPROC glGetIntegeri_v;

PFNGLBEGINTRANSFORMFEEDBACKPROC glBeginTransformFeedback;

PFNGLENDTRANSFORMFEEDBACKPROC glEndTransformFeedback;

PFNGLBINDBUFFERRANGEPROC glBindBufferRange;

PFNGLBINDBUFFERBASEPROC glBindBufferBase;

PFNGLTRANSFORMFEEDBACKVARYINGSPROC glTransformFeedbackVaryings;

PFNGLGETTRANSFORMFEEDBACKVARYINGPROC glGetTransformFeedbackVarying;

PFNGLVERTEXATTRIBIPOINTERPROC glVertexAttribIPointer;

PFNGLGETVERTEXATTRIBIIVPROC glGetVertexAttribIiv;

PFNGLGETVERTEXATTRIBIUIVPROC glGetVertexAttribIuiv;

PFNGLVERTEXATTRIBI4IPROC glVertexAttribI4i;

PFNGLVERTEXATTRIBI4UIPROC glVertexAttribI4ui;

PFNGLVERTEXATTRIBI4IVPROC glVertexAttribI4iv;

PFNGLVERTEXATTRIBI4UIVPROC glVertexAttribI4uiv;

PFNGLGETUNIFORMUIVPROC glGetUniformuiv;

PFNGLGETFRAGDATALOCATIONPROC glGetFragDataLocation;

PFNGLUNIFORM1UIPROC glUniform1ui;

PFNGLUNIFORM2UIPROC glUniform2ui;

PFNGLUNIFORM3UIPROC glUniform3ui;

PFNGLUNIFORM4UIPROC glUniform4ui;

PFNGLUNIFORM1UIVPROC glUniform1uiv;

PFNGLUNIFORM2UIVPROC glUniform2uiv;

PFNGLUNIFORM3UIVPROC glUniform3uiv;

PFNGLUNIFORM4UIVPROC glUniform4uiv;

PFNGLCLEARBUFFERIVPROC glClearBufferiv;

PFNGLCLEARBUFFERUIVPROC glClearBufferuiv;

PFNGLCLEARBUFFERFVPROC glClearBufferfv;

PFNGLCLEARBUFFERFIPROC glClearBufferfi;

PFNGLGETSTRINGIPROC glGetStringi;

PFNGLCOPYBUFFERSUBDATAPROC glCopyBufferSubData;

PFNGLGETUNIFORMINDICESPROC glGetUniformIndices;

PFNGLGETACTIVEUNIFORMSIVPROC glGetActiveUniformsiv;

PFNGLGETUNIFORMBLOCKINDEXPROC glGetUniformBlockIndex;

PFNGLGETACTIVEUNIFORMBLOCKIVPROC glGetActiveUniformBlockiv;

PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC glGetActiveUniformBlockName;

PFNGLUNIFORMBLOCKBINDINGPROC glUniformBlockBinding;

PFNGLDRAWARRAYSINSTANCEDPROC glDrawArraysInstanced;

PFNGLDRAWELEMENTSINSTANCEDPROC glDrawElementsInstanced;

PFNGLFENCESYNCPROC glFenceSync;

PFNGLISSYNCPROC glIsSync;

PFNGLDELETESYNCPROC glDeleteSync;

PFNGLCLIENTWAITSYNCPROC glClientWaitSync;

PFNGLWAITSYNCPROC glWaitSync;

PFNGLGETINTEGER64VPROC glGetInteger64v;

PFNGLGETSYNCIVPROC glGetSynciv;

PFNGLGETINTEGER64I_VPROC glGetInteger64i_v;

PFNGLGETBUFFERPARAMETERI64VPROC glGetBufferParameteri64v;

PFNGLGENSAMPLERSPROC glGenSamplers;

PFNGLDELETESAMPLERSPROC glDeleteSamplers;

PFNGLISSAMPLERPROC glIsSampler;

PFNGLBINDSAMPLERPROC glBindSampler;

PFNGLSAMPLERPARAMETERIPROC glSamplerParameteri;

PFNGLSAMPLERPARAMETERIVPROC glSamplerParameteriv;

PFNGLSAMPLERPARAMETERFPROC glSamplerParameterf;

PFNGLSAMPLERPARAMETERFVPROC glSamplerParameterfv;

PFNGLGETSAMPLERPARAMETERIVPROC glGetSamplerParameteriv;

PFNGLGETSAMPLERPARAMETERFVPROC glGetSamplerParameterfv;

PFNGLVERTEXATTRIBDIVISORPROC glVertexAttribDivisor;

PFNGLBINDTRANSFORMFEEDBACKPROC glBindTransformFeedback;

PFNGLDELETETRANSFORMFEEDBACKSPROC glDeleteTransformFeedbacks;

PFNGLGENTRANSFORMFEEDBACKSPROC glGenTransformFeedbacks;

PFNGLISTRANSFORMFEEDBACKPROC glIsTransformFeedback;

PFNGLPAUSETRANSFORMFEEDBACKPROC glPauseTransformFeedback;

PFNGLRESUMETRANSFORMFEEDBACKPROC glResumeTransformFeedback;

PFNGLGETPROGRAMBINARYPROC glGetProgramBinary;

PFNGLPROGRAMBINARYPROC glProgramBinary;

PFNGLPROGRAMPARAMETERIPROC glProgramParameteri;

PFNGLINVALIDATEFRAMEBUFFERPROC glInvalidateFramebuffer;

PFNGLINVALIDATESUBFRAMEBUFFERPROC glInvalidateSubFramebuffer;

PFNGLTEXSTORAGE2DPROC glTexStorage2D;

PFNGLTEXSTORAGE3DPROC glTexStorage3D;

PFNGLGETINTERNALFORMATIVPROC glGetInternalformativ;


