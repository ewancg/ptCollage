project(pxtone-tool)

set(PROJECT_RESOURCES
    Script.rc
)

set(PROJECT_SOURCES
    HearSelect.cpp
    Japanese.cpp
    Main.cpp

    ${PROJECT_RESOURCES}
)

set(PROJECT_HEADERS
    HearSelect.h
    Japanese.h
    pxtoneTool.h
    resource.h
)

add_pxtone_library(
    ${PROJECT_NAME}
    SHARED
    "${PROJECT_SOURCES};${PROJECT_HEADERS}"
    pxtone::windows
    pxtone::works
    pxtone::xa2
    pxtone::generic
    pxtone::pxtone
)

target_compile_definitions(${PROJECT_NAME} PRIVATE -DPXTONETOOL_EXPORTS)

# Export
# ---------------

add_library(pxtone::tool ALIAS ${PROJECT_NAME})
