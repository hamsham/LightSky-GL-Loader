
cmake_minimum_required(VERSION 3.12)


# #####################################
# External Project Setup
# #####################################
# Include the CMake module to support the builds of 3rd-party dependencies
include(ExternalProject)

# Sub-directories within the build folder (not installation folder).
set(EXTERNAL_PROJECT_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/external" CACHE STRING "Build prefix for 3rd-party libraries.")
mark_as_advanced(EXTERNAL_PROJECT_PREFIX)

# Include directory for 3rd-party libraries
include_directories(BEFORE SYSTEM ${EXTERNAL_PROJECT_PREFIX}/include)

# Ensure proper linkage
link_directories(${EXTERNAL_PROJECT_PREFIX}/lib)



# #####################################
# Folders for the external data
# #####################################
file(MAKE_DIRECTORY ${EXTERNAL_PROJECT_PREFIX})
file(MAKE_DIRECTORY ${EXTERNAL_PROJECT_PREFIX}/include)
file(MAKE_DIRECTORY ${EXTERNAL_PROJECT_PREFIX}/lib)
file(MAKE_DIRECTORY ${EXTERNAL_PROJECT_PREFIX}/bin)



# #####################################
# Version Control Tools
# #####################################
find_package(Hg REQUIRED)



# #####################################
# External build for SDL2
# #####################################
set(CMAKE_THREAD_PREFER_PTHREAD)
find_package(Threads)



# #####################################
# SDL2 VCS Setup
# #####################################
set(SDL2_GIT_BRANCH master)
set(SDL2_INSTALL_PREFIX    ${EXTERNAL_PROJECT_PREFIX})
set(SDL2_BINARY_DIRECTORY  ${SDL2_INSTALL_PREFIX}/src/Sdl2-build)
set(SDL2_SOURCE_DIRECTORY  ${SDL2_INSTALL_PREFIX}/src/Sdl2)
set(SDL2_INCLUDE_DIRECTORY ${SDL2_INSTALL_PREFIX}/include)
set(SDL2_LIBRARY_DIRECTORY ${SDL2_INSTALL_PREFIX}/lib)

set(SDL2_BRANCH "release-2.0.12" CACHE STRING "Git branch or tag for checking out SDL2.")
mark_as_advanced(SDL2_BRANCH)

set(SDL2_BUILD_SHARED OFF)

if (NOT CMAKE_BUILD_TYPE)
    set(SDL2_BUILD_TYPE relwithdebinfo)
else()
    string(TOLOWER ${CMAKE_BUILD_TYPE} SDL2_BUILD_TYPE)
endif()

if (NOT SDL2_BUILD_TYPE OR SDL2_BUILD_TYPE MATCHES "debug")
    set(SDL2_LIB_SUFFIX d)
else()
    set(SDL2_LIB_SUFFIX "")
endif()

if (SDL2_BUILD_TYPE MATCHES "release" OR SDL2_BUILD_TYPE MATCHES "minsizerel")
    set(SDL2_LIB_TYPE Release)
else()
    set(SDL2_LIB_TYPE Debug)
endif()

# #####################################
# Configure build options
# #####################################
set(SDL2_BUILD_FLAGS
    -DCMAKE_CXX_COMPILER:STRING=${CMAKE_CXX_COMPILER}
    -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS}
    -DCMAKE_C_COMPILER:STRING=${CMAKE_C_COMPILER}
    -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS}
    -DCMAKE_RC_COMPILER:FILEPATH=${CMAKE_RC_COMPILER}
    -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
    -DCMAKE_INSTALL_PREFIX:FILEPATH=${SDL2_INSTALL_PREFIX}
    -DCMAKE_SYSTEM_NAME:STRING=${CMAKE_SYSTEM_NAME}
    -DCMAKE_LIBRARY_OUTPUT_DIRECTORY:FILEPATH=${SDL2_LIBRARY_DIRECTORY}
    -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY:FILEPATH=${SDL2_LIBRARY_DIRECTORY}
    -DBUILD_SHARED_LIBS:BOOL=${SDL2_BUILD_SHARED}
    -DSNDIO:BOOL=OFF)
mark_as_advanced(SDL2_BUILD_FLAGS)

# #####################################
# Build SDL2
# #####################################
ExternalProject_Add(
    Sdl2
    PREFIX
        ${SDL2_INSTALL_PREFIX}
    HG_REPOSITORY
        "https://hg.libsdl.org/SDL"
    HG_TAG
        "${SDL2_BRANCH}"
    CMAKE_COMMAND
        ${CMAKE_COMMAND}
    CMAKE_CACHE_ARGS
        ${SDL2_BUILD_FLAGS}
    BUILD_COMMAND
        ${CMAKE_COMMAND} -E make_directory ${SDL2_LIBRARY_DIRECTORY} &&
        ${CMAKE_COMMAND} -E make_directory ${SDL2_INCLUDE_DIRECTORY} &&
        ${CMAKE_COMMAND} -E chdir ${SDL2_BINARY_DIRECTORY} ${CMAKE_COMMAND} --build . --config ${CMAKE_CFG_INTDIR} --parallel
    INSTALL_DIR
        ${SDL2_INSTALL_PREFIX}
    INSTALL_COMMAND
        ${CMAKE_COMMAND} -E chdir ${SDL2_BINARY_DIRECTORY} ${CMAKE_COMMAND} --build . --config ${CMAKE_CFG_INTDIR} --target install
)



# Add the imported library target
add_library(SDL2 STATIC IMPORTED)
set_target_properties(SDL2 PROPERTIES IMPORTED_LOCATION ${EXTERNAL_PROJECT_PREFIX}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2${SDL2_LIB_SUFFIX}${CMAKE_STATIC_LIBRARY_SUFFIX})
add_dependencies(SDL2 Sdl2)

add_library(SDL2_MAIN STATIC IMPORTED)
set_target_properties(SDL2_MAIN PROPERTIES IMPORTED_LOCATION ${EXTERNAL_PROJECT_PREFIX}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2main${SDL2_LIB_SUFFIX}${CMAKE_STATIC_LIBRARY_SUFFIX})
add_dependencies(SDL2_MAIN Sdl2)

add_dependencies(SDL2 Sdl2)



# #####################################
# Final Library Output
# #####################################
function(sdl2_locate_apple_framework outVariable framework)
    find_library(temp ${framework} REQUIRED)

    if (temp MATCHES temp-NOTFOUND)
        message(FATAL_ERROR "-- Unable to find ${framework} for linking with SDL2.")
    else()
        message("-- Found ${framework}: ${temp}")
        set(${outVariable} "-framework ${framework}" PARENT_SCOPE)
    endif()
endfunction()

function(sdl2_locate_library outVariable libName)
    find_library(temp ${libName} REQUIRED)

    if (temp MATCHES temp-NOTFOUND)
        message(FATAL_ERROR "-- Unable to find ${libName} for linking with SDL2.")
    else()
        message("-- Found ${libName}: ${temp}")
        set(${outVariable} "${libName}" PARENT_SCOPE)
    endif()
endfunction()

if (WIN32)
    find_package(OpenGL REQUIRED)

    set(SDL2_LIBRARIES SDL2 ${OPENGL_LIBRARIES} Threads::Threads)
elseif(NOT APPLE)
    find_package(OpenGL REQUIRED)
    find_library(DYNAMIC_LIBRARY dl REQUIRED)

    if (DYNAMIC_LIBRARY-NOTFOUND)
        message(FATAL_ERROR "-- Unable to find libdl for linking with SDL2.")
    endif()

    set(SDL2_LIBRARIES SDL2 SDL2_MAIN ${OPENGL_LIBRARIES} Threads::Threads ${DYNAMIC_LIBRARY})
elseif(APPLE)
    set(CMAKE_FIND_FRAMEWORK LAST)

    sdl2_locate_apple_framework(CARBON_LIBRARY Carbon)
    sdl2_locate_apple_framework(COCOA_LIBRARY Cocoa)
    sdl2_locate_apple_framework(OPENGL_LIBRARY OpenGL)
    sdl2_locate_apple_framework(METAL_LIBRARY Metal)
    sdl2_locate_apple_framework(FORCEFEEDBACK_LIBRARY ForceFeedback)
    sdl2_locate_apple_framework(CORE_BT_LIBRARY CoreBluetooth)
    sdl2_locate_apple_framework(AV_FOUNDATION_LIBRARY AVFoundation)
    sdl2_locate_apple_framework(AUDIO_TOOLBOX_LIBRARY AudioToolbox)
    sdl2_locate_apple_framework(CORE_GRAPHICS_LIBRARY CoreGraphics)
    sdl2_locate_apple_framework(CORE_AUDIO_LIBRARY CoreAudio)
    sdl2_locate_apple_framework(IO_KIT_LIBRARY IOKit)
    sdl2_locate_apple_framework(QUARTZ_CORE_LIBRARY QuartzCore)
    sdl2_locate_apple_framework(GAME_CONTROOLER_LIBRARY GameController)
    sdl2_locate_library(ICONV_LIBRARY iconv)

    set(SDL2_LIBRARIES SDL2 "${COCOA_LIBRARY}" "${CARBON_LIBRARY}" "${OPENGL_LIBRARY}" "${METAL_LIBRARY}" "${FORCEFEEDBACK_LIBRARY}" "${CORE_BT_LIBRARY}" "${AV_FOUNDATION_LIBRARY}" "${AUDIO_TOOLBOX_LIBRARY}" "${CORE_GRAPHICS_LIBRARY}" "${CORE_AUDIO_LIBRARY}" "${IO_KIT_LIBRARY}" "${QUARTZ_CORE_LIBRARY}" "${GAME_CONTROOLER_LIBRARY}" ${ICONV_LIBRARY} Threads::Threads)
endif()
