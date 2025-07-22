project(pxtone-windows)

set(PROJECT_SOURCES
    pxwAlteration.cpp
    pxwAppEtc.cpp
    pxwDirectory.cpp
    pxwDlg_SelFile.cpp
    pxwDx09Draw.cpp
    pxwFile.cpp
    pxwFilePath.cpp
    pxwGlyph1.cpp
    pxwMutex.cpp
    pxwPathDialog.cpp
    pxwTextOverride.cpp
    pxwThread.cpp
    pxwUTF8.cpp
    pxwWindowRect.cpp
    pxwXA2stream.cpp
    pxwXA2unit.cpp
    pxwXAudio2.cpp
    pxwXAudio2Keep.cpp
)

set(PROJECT_HEADERS
    pxwAlteration.h
    pxwAppEtc.h
    pxwDirectory.h
    pxwDlg_SelFile.h
    pxwDx09Draw.h
    pxwFile.h
    pxwFilePath.h
    pxwGlyph1.h
    pxwMutex.h
    pxwPathDialog.h
    pxwTextOverride.h
    pxwThread.h
    pxwUTF8.h
    pxwWindowRect.h
    pxwXA2stream.h
    pxwXA2unit.h
    pxwXAudio2.h
    pxwXAudio2Keep.h
)

add_pxtone_library(
    ${PROJECT_NAME}
    STATIC
    "${PROJECT_SOURCES};${PROJECT_HEADERS}"
    pxtone::works

    version.lib
    comctl32.lib
    ksguid.lib
    dxguid.lib
    shlwapi.lib
    winmm.lib
    imm32.lib
    d3dx9.lib
    d3d9.lib
)

# Export
# ---------------

add_library(pxtone::windows ALIAS ${PROJECT_NAME})
