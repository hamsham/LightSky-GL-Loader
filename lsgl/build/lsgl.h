
/*
 * gcc --std=c99 -pedantic -pedantic-errors -Wall -Werror -Wextra -fPIC -O2 -I./ -g -c lsgl.c -o lsgl.o
 *
 * ar rcs lilsgl_d.a lsgl.o
 */

#ifndef __LS_GL_LOADER_H__
#define __LS_GL_LOADER_H__

#include <GLES3/gl3.h>
#include <GLES3/gl2ext.h>

/*-------------------------------------
 * LightSky OpenGL Function Initializaton
-------------------------------------*/
int lsgl_init();

/*-------------------------------------
 * OpenGL Function Declarations
-------------------------------------*/
extern PFNGLACTIVETEXTUREPROC glActiveTexture;

extern PFNGLATTACHSHADERPROC glAttachShader;

extern PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;

extern PFNGLBINDBUFFERPROC glBindBuffer;

extern PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;

extern PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer;

extern PFNGLBINDTEXTUREPROC glBindTexture;

extern PFNGLBLENDCOLORPROC glBlendColor;

extern PFNGLBLENDEQUATIONPROC glBlendEquation;

extern PFNGLBLENDEQUATIONSEPARATEPROC glBlendEquationSeparate;

extern PFNGLBLENDFUNCPROC glBlendFunc;

extern PFNGLBLENDFUNCSEPARATEPROC glBlendFuncSeparate;

extern PFNGLBUFFERDATAPROC glBufferData;

extern PFNGLBUFFERSUBDATAPROC glBufferSubData;

extern PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus;

extern PFNGLCLEARPROC glClear;

extern PFNGLCLEARCOLORPROC glClearColor;

extern PFNGLCLEARDEPTHFPROC glClearDepthf;

extern PFNGLCLEARSTENCILPROC glClearStencil;

extern PFNGLCOLORMASKPROC glColorMask;

extern PFNGLCOMPILESHADERPROC glCompileShader;

extern PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D;

extern PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glCompressedTexSubImage2D;

extern PFNGLCOPYTEXIMAGE2DPROC glCopyTexImage2D;

extern PFNGLCOPYTEXSUBIMAGE2DPROC glCopyTexSubImage2D;

extern PFNGLCREATEPROGRAMPROC glCreateProgram;

extern PFNGLCREATESHADERPROC glCreateShader;

extern PFNGLCULLFACEPROC glCullFace;

extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;

extern PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers;

extern PFNGLDELETEPROGRAMPROC glDeleteProgram;

extern PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffers;

extern PFNGLDELETESHADERPROC glDeleteShader;

extern PFNGLDELETETEXTURESPROC glDeleteTextures;

extern PFNGLDEPTHFUNCPROC glDepthFunc;

extern PFNGLDEPTHMASKPROC glDepthMask;

extern PFNGLDEPTHRANGEFPROC glDepthRangef;

extern PFNGLDETACHSHADERPROC glDetachShader;

extern PFNGLDISABLEPROC glDisable;

extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;

extern PFNGLDRAWARRAYSPROC glDrawArrays;

extern PFNGLDRAWELEMENTSPROC glDrawElements;

extern PFNGLENABLEPROC glEnable;

extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;

extern PFNGLFINISHPROC glFinish;

extern PFNGLFLUSHPROC glFlush;

extern PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer;

extern PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D;

extern PFNGLFRONTFACEPROC glFrontFace;

extern PFNGLGENBUFFERSPROC glGenBuffers;

extern PFNGLGENERATEMIPMAPPROC glGenerateMipmap;

extern PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;

extern PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers;

extern PFNGLGENTEXTURESPROC glGenTextures;

extern PFNGLGETACTIVEATTRIBPROC glGetActiveAttrib;

extern PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform;

extern PFNGLGETATTACHEDSHADERSPROC glGetAttachedShaders;

extern PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;

extern PFNGLGETBOOLEANVPROC glGetBooleanv;

extern PFNGLGETBUFFERPARAMETERIVPROC glGetBufferParameteriv;

extern PFNGLGETERRORPROC glGetError;

extern PFNGLGETFLOATVPROC glGetFloatv;

extern PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glGetFramebufferAttachmentParameteriv;

extern PFNGLGETINTEGERVPROC glGetIntegerv;

extern PFNGLGETPROGRAMIVPROC glGetProgramiv;

extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;

extern PFNGLGETRENDERBUFFERPARAMETERIVPROC glGetRenderbufferParameteriv;

extern PFNGLGETSHADERIVPROC glGetShaderiv;

extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;

extern PFNGLGETSHADERPRECISIONFORMATPROC glGetShaderPrecisionFormat;

extern PFNGLGETSHADERSOURCEPROC glGetShaderSource;

extern PFNGLGETSTRINGPROC glGetString;

extern PFNGLGETTEXPARAMETERFVPROC glGetTexParameterfv;

extern PFNGLGETTEXPARAMETERIVPROC glGetTexParameteriv;

extern PFNGLGETUNIFORMFVPROC glGetUniformfv;

extern PFNGLGETUNIFORMIVPROC glGetUniformiv;

extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;

extern PFNGLGETVERTEXATTRIBFVPROC glGetVertexAttribfv;

extern PFNGLGETVERTEXATTRIBIVPROC glGetVertexAttribiv;

extern PFNGLGETVERTEXATTRIBPOINTERVPROC glGetVertexAttribPointerv;

extern PFNGLHINTPROC glHint;

extern PFNGLISBUFFERPROC glIsBuffer;

extern PFNGLISENABLEDPROC glIsEnabled;

extern PFNGLISFRAMEBUFFERPROC glIsFramebuffer;

extern PFNGLISPROGRAMPROC glIsProgram;

extern PFNGLISRENDERBUFFERPROC glIsRenderbuffer;

extern PFNGLISSHADERPROC glIsShader;

extern PFNGLISTEXTUREPROC glIsTexture;

extern PFNGLLINEWIDTHPROC glLineWidth;

extern PFNGLLINKPROGRAMPROC glLinkProgram;

extern PFNGLPIXELSTOREIPROC glPixelStorei;

extern PFNGLPOLYGONOFFSETPROC glPolygonOffset;

extern PFNGLREADPIXELSPROC glReadPixels;

extern PFNGLRELEASESHADERCOMPILERPROC glReleaseShaderCompiler;

extern PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage;

extern PFNGLSAMPLECOVERAGEPROC glSampleCoverage;

extern PFNGLSCISSORPROC glScissor;

extern PFNGLSHADERBINARYPROC glShaderBinary;

extern PFNGLSHADERSOURCEPROC glShaderSource;

extern PFNGLSTENCILFUNCPROC glStencilFunc;

extern PFNGLSTENCILFUNCSEPARATEPROC glStencilFuncSeparate;

extern PFNGLSTENCILMASKPROC glStencilMask;

extern PFNGLSTENCILMASKSEPARATEPROC glStencilMaskSeparate;

extern PFNGLSTENCILOPPROC glStencilOp;

extern PFNGLSTENCILOPSEPARATEPROC glStencilOpSeparate;

extern PFNGLTEXIMAGE2DPROC glTexImage2D;

extern PFNGLTEXPARAMETERFPROC glTexParameterf;

extern PFNGLTEXPARAMETERFVPROC glTexParameterfv;

extern PFNGLTEXPARAMETERIPROC glTexParameteri;

extern PFNGLTEXPARAMETERIVPROC glTexParameteriv;

extern PFNGLTEXSUBIMAGE2DPROC glTexSubImage2D;

extern PFNGLUNIFORM1FPROC glUniform1f;

extern PFNGLUNIFORM1FVPROC glUniform1fv;

extern PFNGLUNIFORM1IPROC glUniform1i;

extern PFNGLUNIFORM1IVPROC glUniform1iv;

extern PFNGLUNIFORM2FPROC glUniform2f;

extern PFNGLUNIFORM2FVPROC glUniform2fv;

extern PFNGLUNIFORM2IPROC glUniform2i;

extern PFNGLUNIFORM2IVPROC glUniform2iv;

extern PFNGLUNIFORM3FPROC glUniform3f;

extern PFNGLUNIFORM3FVPROC glUniform3fv;

extern PFNGLUNIFORM3IPROC glUniform3i;

extern PFNGLUNIFORM3IVPROC glUniform3iv;

extern PFNGLUNIFORM4FPROC glUniform4f;

extern PFNGLUNIFORM4FVPROC glUniform4fv;

extern PFNGLUNIFORM4IPROC glUniform4i;

extern PFNGLUNIFORM4IVPROC glUniform4iv;

extern PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv;

extern PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv;

extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;

extern PFNGLUSEPROGRAMPROC glUseProgram;

extern PFNGLVALIDATEPROGRAMPROC glValidateProgram;

extern PFNGLVERTEXATTRIB1FPROC glVertexAttrib1f;

extern PFNGLVERTEXATTRIB1FVPROC glVertexAttrib1fv;

extern PFNGLVERTEXATTRIB2FPROC glVertexAttrib2f;

extern PFNGLVERTEXATTRIB2FVPROC glVertexAttrib2fv;

extern PFNGLVERTEXATTRIB3FPROC glVertexAttrib3f;

extern PFNGLVERTEXATTRIB3FVPROC glVertexAttrib3fv;

extern PFNGLVERTEXATTRIB4FPROC glVertexAttrib4f;

extern PFNGLVERTEXATTRIB4FVPROC glVertexAttrib4fv;

extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;

extern PFNGLVIEWPORTPROC glViewport;

extern PFNGLREADBUFFERPROC glReadBuffer;

extern PFNGLDRAWRANGEELEMENTSPROC glDrawRangeElements;

extern PFNGLTEXIMAGE3DPROC glTexImage3D;

extern PFNGLTEXSUBIMAGE3DPROC glTexSubImage3D;

extern PFNGLCOPYTEXSUBIMAGE3DPROC glCopyTexSubImage3D;

extern PFNGLCOMPRESSEDTEXIMAGE3DPROC glCompressedTexImage3D;

extern PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC glCompressedTexSubImage3D;

extern PFNGLGENQUERIESPROC glGenQueries;

extern PFNGLDELETEQUERIESPROC glDeleteQueries;

extern PFNGLISQUERYPROC glIsQuery;

extern PFNGLBEGINQUERYPROC glBeginQuery;

extern PFNGLENDQUERYPROC glEndQuery;

extern PFNGLGETQUERYIVPROC glGetQueryiv;

extern PFNGLGETQUERYOBJECTUIVPROC glGetQueryObjectuiv;

extern PFNGLUNMAPBUFFERPROC glUnmapBuffer;

extern PFNGLGETBUFFERPOINTERVPROC glGetBufferPointerv;

extern PFNGLDRAWBUFFERSPROC glDrawBuffers;

extern PFNGLUNIFORMMATRIX2X3FVPROC glUniformMatrix2x3fv;

extern PFNGLUNIFORMMATRIX3X2FVPROC glUniformMatrix3x2fv;

extern PFNGLUNIFORMMATRIX2X4FVPROC glUniformMatrix2x4fv;

extern PFNGLUNIFORMMATRIX4X2FVPROC glUniformMatrix4x2fv;

extern PFNGLUNIFORMMATRIX3X4FVPROC glUniformMatrix3x4fv;

extern PFNGLUNIFORMMATRIX4X3FVPROC glUniformMatrix4x3fv;

extern PFNGLBLITFRAMEBUFFERPROC glBlitFramebuffer;

extern PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC glRenderbufferStorageMultisample;

extern PFNGLFRAMEBUFFERTEXTURELAYERPROC glFramebufferTextureLayer;

extern PFNGLMAPBUFFERRANGEPROC glMapBufferRange;

extern PFNGLFLUSHMAPPEDBUFFERRANGEPROC glFlushMappedBufferRange;

extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;

extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;

extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;

extern PFNGLISVERTEXARRAYPROC glIsVertexArray;

extern PFNGLGETINTEGERI_VPROC glGetIntegeri_v;

extern PFNGLBEGINTRANSFORMFEEDBACKPROC glBeginTransformFeedback;

extern PFNGLENDTRANSFORMFEEDBACKPROC glEndTransformFeedback;

extern PFNGLBINDBUFFERRANGEPROC glBindBufferRange;

extern PFNGLBINDBUFFERBASEPROC glBindBufferBase;

extern PFNGLTRANSFORMFEEDBACKVARYINGSPROC glTransformFeedbackVaryings;

extern PFNGLGETTRANSFORMFEEDBACKVARYINGPROC glGetTransformFeedbackVarying;

extern PFNGLVERTEXATTRIBIPOINTERPROC glVertexAttribIPointer;

extern PFNGLGETVERTEXATTRIBIIVPROC glGetVertexAttribIiv;

extern PFNGLGETVERTEXATTRIBIUIVPROC glGetVertexAttribIuiv;

extern PFNGLVERTEXATTRIBI4IPROC glVertexAttribI4i;

extern PFNGLVERTEXATTRIBI4UIPROC glVertexAttribI4ui;

extern PFNGLVERTEXATTRIBI4IVPROC glVertexAttribI4iv;

extern PFNGLVERTEXATTRIBI4UIVPROC glVertexAttribI4uiv;

extern PFNGLGETUNIFORMUIVPROC glGetUniformuiv;

extern PFNGLGETFRAGDATALOCATIONPROC glGetFragDataLocation;

extern PFNGLUNIFORM1UIPROC glUniform1ui;

extern PFNGLUNIFORM2UIPROC glUniform2ui;

extern PFNGLUNIFORM3UIPROC glUniform3ui;

extern PFNGLUNIFORM4UIPROC glUniform4ui;

extern PFNGLUNIFORM1UIVPROC glUniform1uiv;

extern PFNGLUNIFORM2UIVPROC glUniform2uiv;

extern PFNGLUNIFORM3UIVPROC glUniform3uiv;

extern PFNGLUNIFORM4UIVPROC glUniform4uiv;

extern PFNGLCLEARBUFFERIVPROC glClearBufferiv;

extern PFNGLCLEARBUFFERUIVPROC glClearBufferuiv;

extern PFNGLCLEARBUFFERFVPROC glClearBufferfv;

extern PFNGLCLEARBUFFERFIPROC glClearBufferfi;

extern PFNGLGETSTRINGIPROC glGetStringi;

extern PFNGLCOPYBUFFERSUBDATAPROC glCopyBufferSubData;

extern PFNGLGETUNIFORMINDICESPROC glGetUniformIndices;

extern PFNGLGETACTIVEUNIFORMSIVPROC glGetActiveUniformsiv;

extern PFNGLGETUNIFORMBLOCKINDEXPROC glGetUniformBlockIndex;

extern PFNGLGETACTIVEUNIFORMBLOCKIVPROC glGetActiveUniformBlockiv;

extern PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC glGetActiveUniformBlockName;

extern PFNGLUNIFORMBLOCKBINDINGPROC glUniformBlockBinding;

extern PFNGLDRAWARRAYSINSTANCEDPROC glDrawArraysInstanced;

extern PFNGLDRAWELEMENTSINSTANCEDPROC glDrawElementsInstanced;

extern PFNGLFENCESYNCPROC glFenceSync;

extern PFNGLISSYNCPROC glIsSync;

extern PFNGLDELETESYNCPROC glDeleteSync;

extern PFNGLCLIENTWAITSYNCPROC glClientWaitSync;

extern PFNGLWAITSYNCPROC glWaitSync;

extern PFNGLGETINTEGER64VPROC glGetInteger64v;

extern PFNGLGETSYNCIVPROC glGetSynciv;

extern PFNGLGETINTEGER64I_VPROC glGetInteger64i_v;

extern PFNGLGETBUFFERPARAMETERI64VPROC glGetBufferParameteri64v;

extern PFNGLGENSAMPLERSPROC glGenSamplers;

extern PFNGLDELETESAMPLERSPROC glDeleteSamplers;

extern PFNGLISSAMPLERPROC glIsSampler;

extern PFNGLBINDSAMPLERPROC glBindSampler;

extern PFNGLSAMPLERPARAMETERIPROC glSamplerParameteri;

extern PFNGLSAMPLERPARAMETERIVPROC glSamplerParameteriv;

extern PFNGLSAMPLERPARAMETERFPROC glSamplerParameterf;

extern PFNGLSAMPLERPARAMETERFVPROC glSamplerParameterfv;

extern PFNGLGETSAMPLERPARAMETERIVPROC glGetSamplerParameteriv;

extern PFNGLGETSAMPLERPARAMETERFVPROC glGetSamplerParameterfv;

extern PFNGLVERTEXATTRIBDIVISORPROC glVertexAttribDivisor;

extern PFNGLBINDTRANSFORMFEEDBACKPROC glBindTransformFeedback;

extern PFNGLDELETETRANSFORMFEEDBACKSPROC glDeleteTransformFeedbacks;

extern PFNGLGENTRANSFORMFEEDBACKSPROC glGenTransformFeedbacks;

extern PFNGLISTRANSFORMFEEDBACKPROC glIsTransformFeedback;

extern PFNGLPAUSETRANSFORMFEEDBACKPROC glPauseTransformFeedback;

extern PFNGLRESUMETRANSFORMFEEDBACKPROC glResumeTransformFeedback;

extern PFNGLGETPROGRAMBINARYPROC glGetProgramBinary;

extern PFNGLPROGRAMBINARYPROC glProgramBinary;

extern PFNGLPROGRAMPARAMETERIPROC glProgramParameteri;

extern PFNGLINVALIDATEFRAMEBUFFERPROC glInvalidateFramebuffer;

extern PFNGLINVALIDATESUBFRAMEBUFFERPROC glInvalidateSubFramebuffer;

extern PFNGLTEXSTORAGE2DPROC glTexStorage2D;

extern PFNGLTEXSTORAGE3DPROC glTexStorage3D;

extern PFNGLGETINTERNALFORMATIVPROC glGetInternalformativ;


#endif /* __LS_GL_LOADER_H__ */
