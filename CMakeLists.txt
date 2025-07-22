# Meta
cmake_minimum_required(VERSION 3.29)
include(CMakeDependentOption)

set(CMAKE_CXX_STANDARD 11)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Configuration options
# ---------------

option(SHARED_PXTONE "Compile pxtone as a shared library" true)

option(ENABLE_PTCOLLAGE "Build ptCollage" true)
option(ENABLE_PTVOICE "Build ptVoice" true)
option(ENABLE_PTNOISE "Build ptNoise" true)
option(ENABLE_PTPLAYER "Build ptPlayer" true)

cmake_dependent_option(ENABLE_PXWINDOWS "Include pxWindows in source tree" true "ENABLE_PTCOLLAGE OR ENABLE_PTVOICE OR ENABLE_PTNOISE OR ENABLE_PTPLAYER" false)

option(USE_UNICODE "Force Unicode" true)
option(FORCE_64_BIT "Force 64-bit" false)
# Low quality option
# option(FORCE_LLVM_RC "Try to force use of LLVM-RC for compiling resources. Requires llvm-rc and LLVM lld in the PATH and manual specification of CMAKE_RC_IMPLICIT_INCLUDE_DIRECTORIES (/[sysroot]/include on MinGW)" false)

option(BUNDLED_VORBIS "Use the included libvorbis" false)
option(BUNDLED_PNG "Use the included libpng (and zlib)" false)

# option() defaults this to "off" which is problematic; this is ignored on multi-config generators, the output paths will be respected because they can't be observed
set(BUNDLE_BUILD_DIR "" CACHE STRING "Copy build into a pxtone-compatible structure at this path, relative to CMAKE_SOURCE_DIR (-S). If not provided, all binaries will stay in the build directory & any folders within as dictated by the generator, and will have to be moved manually.")

# Base configuration
# ---------------

# This must be specified before the project is initialized
# For testing whether LLVM-RC continues to work with the project's resources, this option is more convenient for me than using Clang
# if(FORCE_LLVM_RC)
#     find_program (LLVM_RC llvm-rc REQUIRED)
#     set(CMAKE_RC_COMPILER "${LLVM_RC}")
#     # code page (-C) 932 is shift JIS, override with UTF-8 (65001)
#     set(CMAKE_RC_COMPILE_OBJECT "<CMAKE_RC_COMPILER> <DEFINES> -I \"${CMAKE_RC_IMPLICIT_INCLUDE_DIRECTORIES}\" -C 65001 ${rc_flags} -FO \"<OBJECT>\" \"<SOURCE>\"")
#     set(CMAKE_LINKER_TYPE LLD)
# endif()

project(pxtone LANGUAGES CXX)

if(${WIN32})
    add_compile_definitions(WIN_32_LEAN_AND_MEAN pxPLATFORM_windows)
    add_compile_options("-Wl,-subsystem,windows")
    if(USE_UNICODE)
        # win32 library defs
        add_compile_definitions(UNICODE _UNICODE)
        if(${MINGW})
            # compiler defs
            add_compile_options("-municode")
        endif()

        # runtime defs via. manifest
        # we need to create a .rc which wraps the .manifest in order for all compilers to understand
        # executables will automatically source this via. macro
        set(MANIFEST_RC "${CMAKE_BINARY_DIR}/manifest.rc")
        file(WRITE "${MANIFEST_RC}" "1 24 \"${CMAKE_SOURCE_DIR}/pxCommon/utf8.manifest\"\n")
    endif()
endif()

if(FORCE_64_BIT OR ("${CMAKE_HOST_SYSTEM_PROCESSOR}" MATCHES "64"))
    add_compile_definitions(px64BIT)
endif()

# shared functionality library providing pxStdAfx.h and macros
add_subdirectory(pxCommon)

# External dependencies
# ---------------

if(BUNDLED_VORBIS)
    add_subdirectory(vorbis)
    set(VORBISFILE_LIBRARY pxtone::vorbis)
else()
    find_package(Vorbis)
    if(Vorbis_FOUND)
        set(VORBISFILE_LIBRARY Vorbis::vorbisfile)
    else()
        message(FATAL_ERROR "Could not find system libvorbis. Please specify BUNDLED_VORBIS")
    endif()
endif()

if(BUNDLED_PNG AND ENABLE_PXWINDOWS)
    add_subdirectory(zlib)
    add_subdirectory(lpng)
    set(PNG_LIBRARIES pxtone::png)
else()
    find_package(PNG)
    if(PNG_FOUND)
        set(PNG_LIBRARIES PNG)
    else()
        message(FATAL_ERROR "Could not find system libpng. Please specify BUNDLED_PNG")
    endif()
endif()

# Internal libraries & includes ("producing" targets)
# ---------------

# pxtone library (sound engine)
add_subdirectory(pxtone)

add_subdirectory(Generic)

if (ENABLE_PXWINDOWS)
    add_subdirectory(ptConfig)
    add_subdirectory(pxtoneTool)
    add_subdirectory(pxtonewin)
    add_subdirectory(pxWindows)
    add_subdirectory(pxWorks)
    add_subdirectory(pxWrapper)
endif()

# Subproject configurations ("consuming" targets)
# ---------------

if (ENABLE_PTCOLLAGE)
    add_subdirectory(ptCollage)
endif()

if (ENABLE_PTVOICE)
    add_subdirectory(ptVoice)
endif()

if (ENABLE_PTNOISE)
    add_subdirectory(ptNoise)
endif()

if (ENABLE_PTPLAYER)
    add_subdirectory(ptPlayer)
endif()
