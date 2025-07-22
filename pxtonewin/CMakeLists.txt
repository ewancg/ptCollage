project(pxtone-xaudio2)

set(PROJECT_SOURCES
    pxtonewinWoice.cpp
    pxtonewinXA2.cpp
    pxtonewinXA2_tune.cpp
    pxtonewinXA2_voice.cpp
)

set(PROJECT_HEADERS
    pxtonewinWoice.h
    pxtonewinXA2.h
)

add_pxtone_library(
    ${PROJECT_NAME}
    STATIC
    "${PROJECT_SOURCES};${PROJECT_HEADERS}"
    pxtone::windows

    pxtone::pxtone
    pxtone::works
)

# Export
# ---------------

add_library(pxtone::xa2 ALIAS ${PROJECT_NAME})
