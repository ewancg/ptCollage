project(pxtone-player)

set(PROJECT_RESOURCES
    script.rc
)

set(PROJECT_SOURCES_DIALOG
    dialog/dlg_About.cpp
    dialog/dlg_BuildOption.cpp
    dialog/dlg_BuildProgress.cpp
    dialog/dlg_Config.cpp
    dialog/dlg_Message.cpp
)

set(PROJECT_SOURCES_INTERFACE
    interface/if_Cursor.cpp
    interface/if_Cursor_Player.cpp
    interface/if_Player.cpp
    interface/Interface.cpp
)

set(PROJECT_SOURCES
    Call_ptCollage.cpp
    JapaneseTable.cpp
    Main.cpp
    Tune.cpp

    ${PROJECT_SOURCES_DIALOG}
    ${PROJECT_SOURCES_INTERFACE}
    ${PROJECT_RESOURCES}
)

set(PROJECT_HEADERS_DIALOG
    dialog/dlg_BuildProgress.h
    dialog/dlg_Message.h
)

set(PROJECT_HEADERS_INTERFACE
    interface/if_Cursor.h
    interface/if_Player.h
    interface/Interface.h
    interface/SurfaceNo.h
)

set(PROJECT_HEADERS
    Call_ptCollage.h
    JapaneseTable.h
    resource.h
    StdAfx/StdAfx.h
    Tune.h

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

