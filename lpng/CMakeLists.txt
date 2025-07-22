# Ad-hoc CMake module exposing all png sources & headers from in-tree

project(pxtone-png LANGUAGES C)

set(LIBRARY_SOURCES
    example.c
    png.c
    pngerror.c
    pngget.c
    pngmem.c
    pngpread.c
    pngread.c
    pngrio.c
    pngrtran.c
    pngrutil.c
    pngset.c
    pngtrans.c
    pngwio.c
    pngwrite.c
    pngwtran.c
    pngwutil.c
)

add_bundled_library(${PROJECT_NAME} SHARED "${LIBRARY_SOURCES}" "${CMAKE_CURRENT_SOURCE_DIR}" pxtone::zlib)

# Export
# ---------------

add_library(pxtone::png ALIAS ${PROJECT_NAME})
