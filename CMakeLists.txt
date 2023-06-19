cmake_minimum_required(VERSION 3.18)
project(LS_GL_Loader C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED TRUE)



# -------------------------------------
# External Package Setup
# -------------------------------------
find_package(Python3 REQUIRED COMPONENTS Interpreter)
include(external_deps.cmake)
include(SDL2Config.cmake)



# -------------------------------------
# GL Folder Creation
# -------------------------------------
function(add_gl_directory glVer)
    add_custom_command(
        OUTPUT
            ${PROJECT_BINARY_DIR}/${glVer}
        COMMAND
            ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/${glVer}
    )

    add_custom_target(copy_${glVer}_headers
        ALL
        DEPENDS
            ${PROJECT_BINARY_DIR}/${glVer}
    )

    foreach(glSource ${ARGN})
        string(REGEX REPLACE "[\\/]" "." temp ${glSource})

        add_custom_command(
            OUTPUT
                ${PROJECT_BINARY_DIR}/${glSource}
            DEPENDS
                ${PROJECT_SOURCE_DIR}/${glSource}
            COMMAND
                ${CMAKE_COMMAND} -E copy_if_different ${PROJECT_SOURCE_DIR}/${glSource} ${PROJECT_BINARY_DIR}/${glSource}
        )

        add_custom_target(copy_${temp}
            ALL
            DEPENDS
                ${PROJECT_BINARY_DIR}/${glVer}
                ${PROJECT_BINARY_DIR}/${glSource}
        )

        add_dependencies(copy_${glVer}_headers copy_${temp})
        unset(temp)
    endforeach()
endfunction()

add_gl_directory(EGL   EGL/egl.h EGL/eglext.h EGL/eglplatform.h)
add_gl_directory(GL    GL/glcorearb.h GL/glext.h GL/glxext.h GL/wgl.h GL/wglext.h)
add_gl_directory(GLES  GLES/egl.h GLES/gl.h GLES/glext.h GLES/glplatform.h)
add_gl_directory(GLES2 GLES2/gl2.h GLES2/gl2ext.h GLES2/gl2platform.h)
add_gl_directory(GLES3 GLES3/gl3.h GLES3/gl31.h GLES3/gl32.h GLES3/gl3platform.h)
add_gl_directory(KHR   KHR/khrplatform.h)



# -------------------------------------
# Target Creation
# -------------------------------------
function(add_lsgl_sources glVer glHeader glExtHeader)
    add_custom_command(
        OUTPUT
            ${PROJECT_BINARY_DIR}/${glVer}/lsgl.h
            ${PROJECT_BINARY_DIR}/${glVer}/lsgl.c
        DEPENDS
            ${glHeader}
            ${glExtHeader}
            ${PROJECT_SOURCE_DIR}/lsgl/__init__.py
            ${PROJECT_SOURCE_DIR}/lsgl/__main__.py
            ${PROJECT_SOURCE_DIR}/lsgl/glloader.py
            ${PROJECT_SOURCE_DIR}/lsgl/templates/lsgl_template.h
            ${PROJECT_SOURCE_DIR}/lsgl/templates/lsgl_template.c
        COMMAND
            ${Python3_EXECUTABLE} -m lsgl -i ${glHeader} -o ${PROJECT_BINARY_DIR}/${glVer}
        COMMAND
            ${CMAKE_COMMAND} -E copy_if_different ${PROJECT_SOURCE_DIR}/lsgl_test.c ${PROJECT_BINARY_DIR}/${glVer}_test.c
        WORKING_DIRECTORY
            ${PROJECT_SOURCE_DIR}
    )

    add_custom_target(lsgl_${glVer}_sources
        ALL
        DEPENDS
            ${PROJECT_BINARY_DIR}/${glVer}/lsgl.h
            ${PROJECT_BINARY_DIR}/${glVer}/lsgl.c
        SOURCES
            ${glHeader}
            ${glExtHeader}
            ${PROJECT_SOURCE_DIR}/lsgl/__init__.py
            ${PROJECT_SOURCE_DIR}/lsgl/__main__.py
            ${PROJECT_SOURCE_DIR}/lsgl/glloader.py
            ${PROJECT_SOURCE_DIR}/lsgl/templates/lsgl_template.h
            ${PROJECT_SOURCE_DIR}/lsgl/templates/lsgl_template.c
    )

    # This should convert things like "GLES32" to "GLES3"
    string(REGEX REPLACE "(GL(ES[0-9]?)?)[0-9]?" "\\1" glBaseVer ${glVer})
    message("${glVer}: copy_${glBaseVer}_headers")

    add_executable(test_${glVer}
        lsgl_test.c
        ${glHeader}
        ${glExtHeader}
        ${PROJECT_BINARY_DIR}/${glVer}/lsgl.h
        ${PROJECT_BINARY_DIR}/${glVer}/lsgl.c
    )

    target_include_directories(test_${glVer} SYSTEM BEFORE PRIVATE ${PROJECT_BINARY_DIR} ${PROJECT_BINARY_DIR}/${glBaseVer} ${ARGN})
    target_link_libraries(test_${glVer} PRIVATE ${SDL2_LIBRARIES} EGL m)

    add_dependencies(test_${glVer} lsgl_${glVer}_sources copy_${glBaseVer}_headers)

    foreach(glTarget ${ARGN})
        add_dependencies(test_${glVer} copy_${glTarget}_headers)
    endforeach()
endfunction()



# -------------------------------------
# LSGL Sources
# -------------------------------------
add_lsgl_sources(GL     GL/glcorearb.h GL/glext.h     KHR)
add_lsgl_sources(GLES   GLES/gl.h      GLES/glext.h   KHR EGL)
add_lsgl_sources(GLES2  GLES2/gl2.h    GLES2/gl2ext.h KHR EGL)
add_lsgl_sources(GLES3  GLES3/gl3.h    GLES2/gl2ext.h KHR EGL GLES2)
add_lsgl_sources(GLES31 GLES3/gl31.h   GLES2/gl2ext.h KHR EGL GLES2)
add_lsgl_sources(GLES32 GLES3/gl32.h   GLES2/gl2ext.h KHR EGL GLES2)
