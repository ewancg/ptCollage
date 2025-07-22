project(pxtone-voice)

set(PROJECT_RESOURCES
    script.rc
)

set(PROJECT_SOURCES_DIALOG
    dialog/dlg_About.cpp
    dialog/dlg_Config.cpp
    dialog/dlg_Message.cpp
    dialog/dlg_YesNo.cpp
)

set(PROJECT_SOURCES_INTERFACE
    interface/Interface.cpp
    interface/ptui.cpp
    interface/ptuiCursor.cpp
    interface/ptuiEnveHead.cpp
    interface/ptuiEnvelope.cpp
    interface/ptuiEnve_mini.cpp
    interface/ptuiHeader.cpp
    interface/ptuiKnob.cpp
    interface/ptuiMap.cpp
    interface/ptuiOrganKey.cpp
    interface/ptuiRackFull.cpp
    interface/ptuiRackHalf.cpp
    interface/ptuiReleaseTime.cpp
    interface/ptuiSines.cpp
    interface/ptuiSwitch.cpp
    interface/ptuiVelocity.cpp
    interface/ptuiWave.cpp
    interface/ptuiWaveHead.cpp
    interface/ptuiWavePreset.cpp
    interface/ptuiWave_mini.cpp
    interface/ptuiWorkTemp.cpp
)

set(PROJECT_SOURCES
    CursorKeyCtrl.cpp
    Japanese.cpp
    JapaneseTable.cpp
    Main.cpp
    MainProc.cpp
    MidiInput.cpp
    ptVoice.cpp
    ptvVelocity.cpp
    VoiceFile.cpp
    WoiceUnit.cpp
    WoiceUnit_csv.cpp

    ${PROJECT_SOURCES_DIALOG}
    ${PROJECT_SOURCES_INTERFACE}
    ${PROJECT_RESOURCES}
)

set(PROJECT_HEADERS_DIALOG
    dialog/dlg_Message.h
)

set(PROJECT_HEADERS_INTERFACE
    interface/Interface.h
    interface/ptui.h
    interface/ptuiCursor.h
    interface/ptuiEnveHead.h
    interface/ptuiEnvelope.h
    interface/ptuiEnve_mini.h
    interface/ptuiHeader.h
    interface/ptuiKnob.h
    interface/ptuiLayout.h
    interface/ptuiMap.h
    interface/ptuiOrganKey.h
    interface/ptuiRackFull.h
    interface/ptuiRackHalf.h
    interface/ptuiReleaseTime.h
    interface/ptuiSines.h
    interface/ptuiSwitch.h
    interface/ptuiVelocity.h
    interface/ptuiWave.h
    interface/ptuiWaveHead.h
    interface/ptuiWavePreset.h
    interface/ptuiWave_mini.h
    interface/ptuiWorkTemp.h
)

set(PROJECT_HEADERS
    CursorKeyCtrl.h
    JapaneseTable.h
    MidiInput.h
    ptVoice.h
    ptvVelocity.h
    resource.h
    StdAfx/StdAfx.h
    VoiceFile.h
    WoiceUnit.h

    ${PROJECT_HEADERS_DIALOG}
    ${PROJECT_HEADERS_INTERFACE}
)

add_pxtone_executable(${PROJECT_NAME} "${PROJECT_SOURCES};${PROJECT_HEADERS}"
    pxtone::pxtone
    pxtone::generic
    pxtone::windows
    pxtone::works
    pxtone::xa2
    pxtone::config
    pxtone::tool
    ${PNG_LIBRARIES}
)
