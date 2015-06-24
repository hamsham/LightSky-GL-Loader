
/*
 * gcc --std=c99 -pedantic -pedantic-errors -Wall -Werror -Wextra -fPIC -O2 -I./ -g -c gl_loader.c -o gl_loader.o
 *
 * ar rcs libgl_loader_d.a gl_loader.o
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
    
    glActiveTexture = (PFNGLACTIVETEXTUREPROC)get_gl_function("glActiveTexture")
    
    glAttachShader = (PFNGLATTACHSHADERPROC)get_gl_function("glAttachShader")
    
    glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)get_gl_function("glBindAttribLocation")
    
    glBindBuffer = (PFNGLBINDBUFFERPROC)get_gl_function("glBindBuffer")
    
    glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)get_gl_function("glBindFramebuffer")
    
    glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)get_gl_function("glBindRenderbuffer")
    
    glBindTexture = (PFNGLBINDTEXTUREPROC)get_gl_function("glBindTexture")
    
    glBlendColor = (PFNGLBLENDCOLORPROC)get_gl_function("glBlendColor")
    
    glBlendEquation = (PFNGLBLENDEQUATIONPROC)get_gl_function("glBlendEquation")
    
    glBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATEPROC)get_gl_function("glBlendEquationSeparate")
    
    glBlendFunc = (PFNGLBLENDFUNCPROC)get_gl_function("glBlendFunc")
    
    glBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC)get_gl_function("glBlendFuncSeparate")
    
    glBufferData = (PFNGLBUFFERDATAPROC)get_gl_function("glBufferData")
    
    glBufferSubData = (PFNGLBUFFERSUBDATAPROC)get_gl_function("glBufferSubData")
    
    glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)get_gl_function("glCheckFramebufferStatus")
    
    glClear = (PFNGLCLEARPROC)get_gl_function("glClear")
    
    glClearColor = (PFNGLCLEARCOLORPROC)get_gl_function("glClearColor")
    
    glClearDepthf = (PFNGLCLEARDEPTHFPROC)get_gl_function("glClearDepthf")
    
    glClearStencil = (PFNGLCLEARSTENCILPROC)get_gl_function("glClearStencil")
    
    glColorMask = (PFNGLCOLORMASKPROC)get_gl_function("glColorMask")
    
    glCompileShader = (PFNGLCOMPILESHADERPROC)get_gl_function("glCompileShader")
    
    glCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC)get_gl_function("glCompressedTexImage2D")
    
    glCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)get_gl_function("glCompressedTexSubImage2D")
    
    glCopyTexImage2D = (PFNGLCOPYTEXIMAGE2DPROC)get_gl_function("glCopyTexImage2D")
    
    glCopyTexSubImage2D = (PFNGLCOPYTEXSUBIMAGE2DPROC)get_gl_function("glCopyTexSubImage2D")
    
    glCreateProgram = (PFNGLCREATEPROGRAMPROC)get_gl_function("glCreateProgram")
    
    glCreateShader = (PFNGLCREATESHADERPROC)get_gl_function("glCreateShader")
    
    glCullFace = (PFNGLCULLFACEPROC)get_gl_function("glCullFace")
    
    glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)get_gl_function("glDeleteBuffers")
    
    glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)get_gl_function("glDeleteFramebuffers")
    
    glDeleteProgram = (PFNGLDELETEPROGRAMPROC)get_gl_function("glDeleteProgram")
    
    glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)get_gl_function("glDeleteRenderbuffers")
    
    glDeleteShader = (PFNGLDELETESHADERPROC)get_gl_function("glDeleteShader")
    
    glDeleteTextures = (PFNGLDELETETEXTURESPROC)get_gl_function("glDeleteTextures")
    
    glDepthFunc = (PFNGLDEPTHFUNCPROC)get_gl_function("glDepthFunc")
    
    glDepthMask = (PFNGLDEPTHMASKPROC)get_gl_function("glDepthMask")
    
    glDepthRangef = (PFNGLDEPTHRANGEFPROC)get_gl_function("glDepthRangef")
    
    glDetachShader = (PFNGLDETACHSHADERPROC)get_gl_function("glDetachShader")
    
    glDisable = (PFNGLDISABLEPROC)get_gl_function("glDisable")
    
    glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)get_gl_function("glDisableVertexAttribArray")
    
    glDrawArrays = (PFNGLDRAWARRAYSPROC)get_gl_function("glDrawArrays")
    
    glDrawElements = (PFNGLDRAWELEMENTSPROC)get_gl_function("glDrawElements")
    
    glEnable = (PFNGLENABLEPROC)get_gl_function("glEnable")
    
    glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)get_gl_function("glEnableVertexAttribArray")
    
    glFinish = (PFNGLFINISHPROC)get_gl_function("glFinish")
    
    glFlush = (PFNGLFLUSHPROC)get_gl_function("glFlush")
    
    glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)get_gl_function("glFramebufferRenderbuffer")
    
    glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)get_gl_function("glFramebufferTexture2D")
    
    glFrontFace = (PFNGLFRONTFACEPROC)get_gl_function("glFrontFace")
    
    glGenBuffers = (PFNGLGENBUFFERSPROC)get_gl_function("glGenBuffers")
    
    glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)get_gl_function("glGenerateMipmap")
    
    glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)get_gl_function("glGenFramebuffers")
    
    glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)get_gl_function("glGenRenderbuffers")
    
    glGenTextures = (PFNGLGENTEXTURESPROC)get_gl_function("glGenTextures")
    
    glGetActiveAttrib = (PFNGLGETACTIVEATTRIBPROC)get_gl_function("glGetActiveAttrib")
    
    glGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC)get_gl_function("glGetActiveUniform")
    
    glGetAttachedShaders = (PFNGLGETATTACHEDSHADERSPROC)get_gl_function("glGetAttachedShaders")
    
    glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)get_gl_function("glGetAttribLocation")
    
    glGetBooleanv = (PFNGLGETBOOLEANVPROC)get_gl_function("glGetBooleanv")
    
    glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC)get_gl_function("glGetBufferParameteriv")
    
    glGetError = (PFNGLGETERRORPROC)get_gl_function("glGetError")
    
    glGetFloatv = (PFNGLGETFLOATVPROC)get_gl_function("glGetFloatv")
    
    glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)get_gl_function("glGetFramebufferAttachmentParameteriv")
    
    glGetIntegerv = (PFNGLGETINTEGERVPROC)get_gl_function("glGetIntegerv")
    
    glGetProgramiv = (PFNGLGETPROGRAMIVPROC)get_gl_function("glGetProgramiv")
    
    glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)get_gl_function("glGetProgramInfoLog")
    
    glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC)get_gl_function("glGetRenderbufferParameteriv")
    
    glGetShaderiv = (PFNGLGETSHADERIVPROC)get_gl_function("glGetShaderiv")
    
    glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)get_gl_function("glGetShaderInfoLog")
    
    glGetShaderPrecisionFormat = (PFNGLGETSHADERPRECISIONFORMATPROC)get_gl_function("glGetShaderPrecisionFormat")
    
    glGetShaderSource = (PFNGLGETSHADERSOURCEPROC)get_gl_function("glGetShaderSource")
    
    glGetString = (PFNGLGETSTRINGPROC)get_gl_function("glGetString")
    
    glGetTexParameterfv = (PFNGLGETTEXPARAMETERFVPROC)get_gl_function("glGetTexParameterfv")
    
    glGetTexParameteriv = (PFNGLGETTEXPARAMETERIVPROC)get_gl_function("glGetTexParameteriv")
    
    glGetUniformfv = (PFNGLGETUNIFORMFVPROC)get_gl_function("glGetUniformfv")
    
    glGetUniformiv = (PFNGLGETUNIFORMIVPROC)get_gl_function("glGetUniformiv")
    
    glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)get_gl_function("glGetUniformLocation")
    
    glGetVertexAttribfv = (PFNGLGETVERTEXATTRIBFVPROC)get_gl_function("glGetVertexAttribfv")
    
    glGetVertexAttribiv = (PFNGLGETVERTEXATTRIBIVPROC)get_gl_function("glGetVertexAttribiv")
    
    glGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERVPROC)get_gl_function("glGetVertexAttribPointerv")
    
    glHint = (PFNGLHINTPROC)get_gl_function("glHint")
    
    glIsBuffer = (PFNGLISBUFFERPROC)get_gl_function("glIsBuffer")
    
    glIsEnabled = (PFNGLISENABLEDPROC)get_gl_function("glIsEnabled")
    
    glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC)get_gl_function("glIsFramebuffer")
    
    glIsProgram = (PFNGLISPROGRAMPROC)get_gl_function("glIsProgram")
    
    glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC)get_gl_function("glIsRenderbuffer")
    
    glIsShader = (PFNGLISSHADERPROC)get_gl_function("glIsShader")
    
    glIsTexture = (PFNGLISTEXTUREPROC)get_gl_function("glIsTexture")
    
    glLineWidth = (PFNGLLINEWIDTHPROC)get_gl_function("glLineWidth")
    
    glLinkProgram = (PFNGLLINKPROGRAMPROC)get_gl_function("glLinkProgram")
    
    glPixelStorei = (PFNGLPIXELSTOREIPROC)get_gl_function("glPixelStorei")
    
    glPolygonOffset = (PFNGLPOLYGONOFFSETPROC)get_gl_function("glPolygonOffset")
    
    glReadPixels = (PFNGLREADPIXELSPROC)get_gl_function("glReadPixels")
    
    glReleaseShaderCompiler = (PFNGLRELEASESHADERCOMPILERPROC)get_gl_function("glReleaseShaderCompiler")
    
    glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)get_gl_function("glRenderbufferStorage")
    
    glSampleCoverage = (PFNGLSAMPLECOVERAGEPROC)get_gl_function("glSampleCoverage")
    
    glScissor = (PFNGLSCISSORPROC)get_gl_function("glScissor")
    
    glShaderBinary = (PFNGLSHADERBINARYPROC)get_gl_function("glShaderBinary")
    
    glShaderSource = (PFNGLSHADERSOURCEPROC)get_gl_function("glShaderSource")
    
    glStencilFunc = (PFNGLSTENCILFUNCPROC)get_gl_function("glStencilFunc")
    
    glStencilFuncSeparate = (PFNGLSTENCILFUNCSEPARATEPROC)get_gl_function("glStencilFuncSeparate")
    
    glStencilMask = (PFNGLSTENCILMASKPROC)get_gl_function("glStencilMask")
    
    glStencilMaskSeparate = (PFNGLSTENCILMASKSEPARATEPROC)get_gl_function("glStencilMaskSeparate")
    
    glStencilOp = (PFNGLSTENCILOPPROC)get_gl_function("glStencilOp")
    
    glStencilOpSeparate = (PFNGLSTENCILOPSEPARATEPROC)get_gl_function("glStencilOpSeparate")
    
    glTexImage2D = (PFNGLTEXIMAGE2DPROC)get_gl_function("glTexImage2D")
    
    glTexParameterf = (PFNGLTEXPARAMETERFPROC)get_gl_function("glTexParameterf")
    
    glTexParameterfv = (PFNGLTEXPARAMETERFVPROC)get_gl_function("glTexParameterfv")
    
    glTexParameteri = (PFNGLTEXPARAMETERIPROC)get_gl_function("glTexParameteri")
    
    glTexParameteriv = (PFNGLTEXPARAMETERIVPROC)get_gl_function("glTexParameteriv")
    
    glTexSubImage2D = (PFNGLTEXSUBIMAGE2DPROC)get_gl_function("glTexSubImage2D")
    
    glUniform1f = (PFNGLUNIFORM1FPROC)get_gl_function("glUniform1f")
    
    glUniform1fv = (PFNGLUNIFORM1FVPROC)get_gl_function("glUniform1fv")
    
    glUniform1i = (PFNGLUNIFORM1IPROC)get_gl_function("glUniform1i")
    
    glUniform1iv = (PFNGLUNIFORM1IVPROC)get_gl_function("glUniform1iv")
    
    glUniform2f = (PFNGLUNIFORM2FPROC)get_gl_function("glUniform2f")
    
    glUniform2fv = (PFNGLUNIFORM2FVPROC)get_gl_function("glUniform2fv")
    
    glUniform2i = (PFNGLUNIFORM2IPROC)get_gl_function("glUniform2i")
    
    glUniform2iv = (PFNGLUNIFORM2IVPROC)get_gl_function("glUniform2iv")
    
    glUniform3f = (PFNGLUNIFORM3FPROC)get_gl_function("glUniform3f")
    
    glUniform3fv = (PFNGLUNIFORM3FVPROC)get_gl_function("glUniform3fv")
    
    glUniform3i = (PFNGLUNIFORM3IPROC)get_gl_function("glUniform3i")
    
    glUniform3iv = (PFNGLUNIFORM3IVPROC)get_gl_function("glUniform3iv")
    
    glUniform4f = (PFNGLUNIFORM4FPROC)get_gl_function("glUniform4f")
    
    glUniform4fv = (PFNGLUNIFORM4FVPROC)get_gl_function("glUniform4fv")
    
    glUniform4i = (PFNGLUNIFORM4IPROC)get_gl_function("glUniform4i")
    
    glUniform4iv = (PFNGLUNIFORM4IVPROC)get_gl_function("glUniform4iv")
    
    glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC)get_gl_function("glUniformMatrix2fv")
    
    glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)get_gl_function("glUniformMatrix3fv")
    
    glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)get_gl_function("glUniformMatrix4fv")
    
    glUseProgram = (PFNGLUSEPROGRAMPROC)get_gl_function("glUseProgram")
    
    glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)get_gl_function("glValidateProgram")
    
    glVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC)get_gl_function("glVertexAttrib1f")
    
    glVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC)get_gl_function("glVertexAttrib1fv")
    
    glVertexAttrib2f = (PFNGLVERTEXATTRIB2FPROC)get_gl_function("glVertexAttrib2f")
    
    glVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC)get_gl_function("glVertexAttrib2fv")
    
    glVertexAttrib3f = (PFNGLVERTEXATTRIB3FPROC)get_gl_function("glVertexAttrib3f")
    
    glVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC)get_gl_function("glVertexAttrib3fv")
    
    glVertexAttrib4f = (PFNGLVERTEXATTRIB4FPROC)get_gl_function("glVertexAttrib4f")
    
    glVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC)get_gl_function("glVertexAttrib4fv")
    
    glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)get_gl_function("glVertexAttribPointer")
    
    glViewport = (PFNGLVIEWPORTPROC)get_gl_function("glViewport")
    
    glReadBuffer = (PFNGLREADBUFFERPROC)get_gl_function("glReadBuffer")
    
    glDrawRangeElements = (PFNGLDRAWRANGEELEMENTSPROC)get_gl_function("glDrawRangeElements")
    
    glTexImage3D = (PFNGLTEXIMAGE3DPROC)get_gl_function("glTexImage3D")
    
    glTexSubImage3D = (PFNGLTEXSUBIMAGE3DPROC)get_gl_function("glTexSubImage3D")
    
    glCopyTexSubImage3D = (PFNGLCOPYTEXSUBIMAGE3DPROC)get_gl_function("glCopyTexSubImage3D")
    
    glCompressedTexImage3D = (PFNGLCOMPRESSEDTEXIMAGE3DPROC)get_gl_function("glCompressedTexImage3D")
    
    glCompressedTexSubImage3D = (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)get_gl_function("glCompressedTexSubImage3D")
    
    glGenQueries = (PFNGLGENQUERIESPROC)get_gl_function("glGenQueries")
    
    glDeleteQueries = (PFNGLDELETEQUERIESPROC)get_gl_function("glDeleteQueries")
    
    glIsQuery = (PFNGLISQUERYPROC)get_gl_function("glIsQuery")
    
    glBeginQuery = (PFNGLBEGINQUERYPROC)get_gl_function("glBeginQuery")
    
    glEndQuery = (PFNGLENDQUERYPROC)get_gl_function("glEndQuery")
    
    glGetQueryiv = (PFNGLGETQUERYIVPROC)get_gl_function("glGetQueryiv")
    
    glGetQueryObjectuiv = (PFNGLGETQUERYOBJECTUIVPROC)get_gl_function("glGetQueryObjectuiv")
    
    glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)get_gl_function("glUnmapBuffer")
    
    glGetBufferPointerv = (PFNGLGETBUFFERPOINTERVPROC)get_gl_function("glGetBufferPointerv")
    
    glDrawBuffers = (PFNGLDRAWBUFFERSPROC)get_gl_function("glDrawBuffers")
    
    glUniformMatrix2x3fv = (PFNGLUNIFORMMATRIX2X3FVPROC)get_gl_function("glUniformMatrix2x3fv")
    
    glUniformMatrix3x2fv = (PFNGLUNIFORMMATRIX3X2FVPROC)get_gl_function("glUniformMatrix3x2fv")
    
    glUniformMatrix2x4fv = (PFNGLUNIFORMMATRIX2X4FVPROC)get_gl_function("glUniformMatrix2x4fv")
    
    glUniformMatrix4x2fv = (PFNGLUNIFORMMATRIX4X2FVPROC)get_gl_function("glUniformMatrix4x2fv")
    
    glUniformMatrix3x4fv = (PFNGLUNIFORMMATRIX3X4FVPROC)get_gl_function("glUniformMatrix3x4fv")
    
    glUniformMatrix4x3fv = (PFNGLUNIFORMMATRIX4X3FVPROC)get_gl_function("glUniformMatrix4x3fv")
    
    glBlitFramebuffer = (PFNGLBLITFRAMEBUFFERPROC)get_gl_function("glBlitFramebuffer")
    
    glRenderbufferStorageMultisample = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC)get_gl_function("glRenderbufferStorageMultisample")
    
    glFramebufferTextureLayer = (PFNGLFRAMEBUFFERTEXTURELAYERPROC)get_gl_function("glFramebufferTextureLayer")
    
    glMapBufferRange = (PFNGLMAPBUFFERRANGEPROC)get_gl_function("glMapBufferRange")
    
    glFlushMappedBufferRange = (PFNGLFLUSHMAPPEDBUFFERRANGEPROC)get_gl_function("glFlushMappedBufferRange")
    
    glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)get_gl_function("glBindVertexArray")
    
    glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)get_gl_function("glDeleteVertexArrays")
    
    glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)get_gl_function("glGenVertexArrays")
    
    glIsVertexArray = (PFNGLISVERTEXARRAYPROC)get_gl_function("glIsVertexArray")
    
    glGetIntegeri_v = (PFNGLGETINTEGERI_VPROC)get_gl_function("glGetIntegeri_v")
    
    glBeginTransformFeedback = (PFNGLBEGINTRANSFORMFEEDBACKPROC)get_gl_function("glBeginTransformFeedback")
    
    glEndTransformFeedback = (PFNGLENDTRANSFORMFEEDBACKPROC)get_gl_function("glEndTransformFeedback")
    
    glBindBufferRange = (PFNGLBINDBUFFERRANGEPROC)get_gl_function("glBindBufferRange")
    
    glBindBufferBase = (PFNGLBINDBUFFERBASEPROC)get_gl_function("glBindBufferBase")
    
    glTransformFeedbackVaryings = (PFNGLTRANSFORMFEEDBACKVARYINGSPROC)get_gl_function("glTransformFeedbackVaryings")
    
    glGetTransformFeedbackVarying = (PFNGLGETTRANSFORMFEEDBACKVARYINGPROC)get_gl_function("glGetTransformFeedbackVarying")
    
    glVertexAttribIPointer = (PFNGLVERTEXATTRIBIPOINTERPROC)get_gl_function("glVertexAttribIPointer")
    
    glGetVertexAttribIiv = (PFNGLGETVERTEXATTRIBIIVPROC)get_gl_function("glGetVertexAttribIiv")
    
    glGetVertexAttribIuiv = (PFNGLGETVERTEXATTRIBIUIVPROC)get_gl_function("glGetVertexAttribIuiv")
    
    glVertexAttribI4i = (PFNGLVERTEXATTRIBI4IPROC)get_gl_function("glVertexAttribI4i")
    
    glVertexAttribI4ui = (PFNGLVERTEXATTRIBI4UIPROC)get_gl_function("glVertexAttribI4ui")
    
    glVertexAttribI4iv = (PFNGLVERTEXATTRIBI4IVPROC)get_gl_function("glVertexAttribI4iv")
    
    glVertexAttribI4uiv = (PFNGLVERTEXATTRIBI4UIVPROC)get_gl_function("glVertexAttribI4uiv")
    
    glGetUniformuiv = (PFNGLGETUNIFORMUIVPROC)get_gl_function("glGetUniformuiv")
    
    glGetFragDataLocation = (PFNGLGETFRAGDATALOCATIONPROC)get_gl_function("glGetFragDataLocation")
    
    glUniform1ui = (PFNGLUNIFORM1UIPROC)get_gl_function("glUniform1ui")
    
    glUniform2ui = (PFNGLUNIFORM2UIPROC)get_gl_function("glUniform2ui")
    
    glUniform3ui = (PFNGLUNIFORM3UIPROC)get_gl_function("glUniform3ui")
    
    glUniform4ui = (PFNGLUNIFORM4UIPROC)get_gl_function("glUniform4ui")
    
    glUniform1uiv = (PFNGLUNIFORM1UIVPROC)get_gl_function("glUniform1uiv")
    
    glUniform2uiv = (PFNGLUNIFORM2UIVPROC)get_gl_function("glUniform2uiv")
    
    glUniform3uiv = (PFNGLUNIFORM3UIVPROC)get_gl_function("glUniform3uiv")
    
    glUniform4uiv = (PFNGLUNIFORM4UIVPROC)get_gl_function("glUniform4uiv")
    
    glClearBufferiv = (PFNGLCLEARBUFFERIVPROC)get_gl_function("glClearBufferiv")
    
    glClearBufferuiv = (PFNGLCLEARBUFFERUIVPROC)get_gl_function("glClearBufferuiv")
    
    glClearBufferfv = (PFNGLCLEARBUFFERFVPROC)get_gl_function("glClearBufferfv")
    
    glClearBufferfi = (PFNGLCLEARBUFFERFIPROC)get_gl_function("glClearBufferfi")
    
    glGetStringi = (PFNGLGETSTRINGIPROC)get_gl_function("glGetStringi")
    
    glCopyBufferSubData = (PFNGLCOPYBUFFERSUBDATAPROC)get_gl_function("glCopyBufferSubData")
    
    glGetUniformIndices = (PFNGLGETUNIFORMINDICESPROC)get_gl_function("glGetUniformIndices")
    
    glGetActiveUniformsiv = (PFNGLGETACTIVEUNIFORMSIVPROC)get_gl_function("glGetActiveUniformsiv")
    
    glGetUniformBlockIndex = (PFNGLGETUNIFORMBLOCKINDEXPROC)get_gl_function("glGetUniformBlockIndex")
    
    glGetActiveUniformBlockiv = (PFNGLGETACTIVEUNIFORMBLOCKIVPROC)get_gl_function("glGetActiveUniformBlockiv")
    
    glGetActiveUniformBlockName = (PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC)get_gl_function("glGetActiveUniformBlockName")
    
    glUniformBlockBinding = (PFNGLUNIFORMBLOCKBINDINGPROC)get_gl_function("glUniformBlockBinding")
    
    glDrawArraysInstanced = (PFNGLDRAWARRAYSINSTANCEDPROC)get_gl_function("glDrawArraysInstanced")
    
    glDrawElementsInstanced = (PFNGLDRAWELEMENTSINSTANCEDPROC)get_gl_function("glDrawElementsInstanced")
    
    glFenceSync = (PFNGLFENCESYNCPROC)get_gl_function("glFenceSync")
    
    glIsSync = (PFNGLISSYNCPROC)get_gl_function("glIsSync")
    
    glDeleteSync = (PFNGLDELETESYNCPROC)get_gl_function("glDeleteSync")
    
    glClientWaitSync = (PFNGLCLIENTWAITSYNCPROC)get_gl_function("glClientWaitSync")
    
    glWaitSync = (PFNGLWAITSYNCPROC)get_gl_function("glWaitSync")
    
    glGetInteger64v = (PFNGLGETINTEGER64VPROC)get_gl_function("glGetInteger64v")
    
    glGetSynciv = (PFNGLGETSYNCIVPROC)get_gl_function("glGetSynciv")
    
    glGetInteger64i_v = (PFNGLGETINTEGER64I_VPROC)get_gl_function("glGetInteger64i_v")
    
    glGetBufferParameteri64v = (PFNGLGETBUFFERPARAMETERI64VPROC)get_gl_function("glGetBufferParameteri64v")
    
    glGenSamplers = (PFNGLGENSAMPLERSPROC)get_gl_function("glGenSamplers")
    
    glDeleteSamplers = (PFNGLDELETESAMPLERSPROC)get_gl_function("glDeleteSamplers")
    
    glIsSampler = (PFNGLISSAMPLERPROC)get_gl_function("glIsSampler")
    
    glBindSampler = (PFNGLBINDSAMPLERPROC)get_gl_function("glBindSampler")
    
    glSamplerParameteri = (PFNGLSAMPLERPARAMETERIPROC)get_gl_function("glSamplerParameteri")
    
    glSamplerParameteriv = (PFNGLSAMPLERPARAMETERIVPROC)get_gl_function("glSamplerParameteriv")
    
    glSamplerParameterf = (PFNGLSAMPLERPARAMETERFPROC)get_gl_function("glSamplerParameterf")
    
    glSamplerParameterfv = (PFNGLSAMPLERPARAMETERFVPROC)get_gl_function("glSamplerParameterfv")
    
    glGetSamplerParameteriv = (PFNGLGETSAMPLERPARAMETERIVPROC)get_gl_function("glGetSamplerParameteriv")
    
    glGetSamplerParameterfv = (PFNGLGETSAMPLERPARAMETERFVPROC)get_gl_function("glGetSamplerParameterfv")
    
    glVertexAttribDivisor = (PFNGLVERTEXATTRIBDIVISORPROC)get_gl_function("glVertexAttribDivisor")
    
    glBindTransformFeedback = (PFNGLBINDTRANSFORMFEEDBACKPROC)get_gl_function("glBindTransformFeedback")
    
    glDeleteTransformFeedbacks = (PFNGLDELETETRANSFORMFEEDBACKSPROC)get_gl_function("glDeleteTransformFeedbacks")
    
    glGenTransformFeedbacks = (PFNGLGENTRANSFORMFEEDBACKSPROC)get_gl_function("glGenTransformFeedbacks")
    
    glIsTransformFeedback = (PFNGLISTRANSFORMFEEDBACKPROC)get_gl_function("glIsTransformFeedback")
    
    glPauseTransformFeedback = (PFNGLPAUSETRANSFORMFEEDBACKPROC)get_gl_function("glPauseTransformFeedback")
    
    glResumeTransformFeedback = (PFNGLRESUMETRANSFORMFEEDBACKPROC)get_gl_function("glResumeTransformFeedback")
    
    glGetProgramBinary = (PFNGLGETPROGRAMBINARYPROC)get_gl_function("glGetProgramBinary")
    
    glProgramBinary = (PFNGLPROGRAMBINARYPROC)get_gl_function("glProgramBinary")
    
    glProgramParameteri = (PFNGLPROGRAMPARAMETERIPROC)get_gl_function("glProgramParameteri")
    
    glInvalidateFramebuffer = (PFNGLINVALIDATEFRAMEBUFFERPROC)get_gl_function("glInvalidateFramebuffer")
    
    glInvalidateSubFramebuffer = (PFNGLINVALIDATESUBFRAMEBUFFERPROC)get_gl_function("glInvalidateSubFramebuffer")
    
    glTexStorage2D = (PFNGLTEXSTORAGE2DPROC)get_gl_function("glTexStorage2D")
    
    glTexStorage3D = (PFNGLTEXSTORAGE3DPROC)get_gl_function("glTexStorage3D")
    
    glGetInternalformativ = (PFNGLGETINTERNALFORMATIVPROC)get_gl_function("glGetInternalformativ")
    

    return true
}