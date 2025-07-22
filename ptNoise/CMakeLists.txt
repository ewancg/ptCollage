project(pxtone-noise)

set(PROJECT_RESOURCES
    script.rc
)

set(PROJECT_SOURCES_INTERFACE
    interface/if_Cursor.cpp
    interface/if_Cursor_Menu_Zoom.cpp
    interface/if_Cursor_Panel_Scale.cpp
    interface/if_Cursor_PcmTable.cpp
    interface/if_Free.cpp
    interface/if_Menu_Zoom.cpp
    interface/if_Panel_Logo.cpp
    interface/if_Panel_Scale.cpp
    interface/if_PcmTable.cpp
    interface/Interface.cpp
)

set(PROJECT_SOURCES_DIALOG
    dialog/dlg_About.cpp
    dialog/dlg_Config.cpp
    dialog/dlg_History.cpp
    dialog/dlg_Message.cpp
    dialog/dlg_Noise_Copy.cpp
    dialog/dlg_Noise_Design.cpp
    dialog/dlg_Noise_Quality.cpp
    dialog/dlg_PCM_Volume.cpp
    dialog/dlg_YesNo.cpp
)

set(PROJECT_SOURCES
    JapaneseTable.cpp
    Main.cpp
    MainProc.cpp
    NoiseTable.cpp
    PcmTable.cpp
    StdAfx/StdAfx.cpp
    ${PROJECT_SOURCES_DIALOG}
    ${PROJECT_SOURCES_INTERFACE}
    ${PROJECT_RESOURCES}
)

set(PROJECT_HEADERS_DIALOG
    dialog/dlg_History.h
    dialog/dlg_Message.h
)

set(PROJECT_HEADERS_INTERFACE
    interface/if_Cursor.h
    interface/if_Free.h
    interface/if_Menu_Zoom.h
    interface/if_Panel_Logo.h
    interface/if_Panel_Scale.h
    interface/if_PcmTable.h
    interface/Interface.h
    interface/SurfaceNo.h
)

set(PROJECT_HEADERS
    JapaneseTable.h
    NoiseTable.h
    PcmTable.h
    ptNoise.h
    resource.h

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

