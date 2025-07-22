project(pxtone-wrapper)

set(PROJECT_SOURCES
    pxwrAppEtc.cpp
    pxwrDirectory.cpp
    pxwrMouse.cpp
    pxwrMutex.cpp
)

set(PROJECT_HEADERS
    pxwrAppEtc.h
    pxwrDirectory.h
    pxwrMouse.h
    pxwrMutex.h
)

add_pxtone_library(
    ${PROJECT_NAME}
    STATIC
    "${PROJECT_SOURCES};${PROJECT_HEADERS}"
    pxtone::windows
    pxtone::works
)

# Export
# ---------------

add_library(pxtone::wrapper ALIAS ${PROJECT_NAME})
