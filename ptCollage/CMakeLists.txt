project(pxtone-collage)

set(PROJECT_RESOURCES
    Script.rc
)

set(PROJECT_SOURCES_DIALOG
    dialog/dlg_About.cpp
    dialog/dlg_AddUnit.cpp
    dialog/dlg_BuildOption.cpp
    dialog/dlg_BuildProgress.cpp
    dialog/dlg_Comment.cpp
    dialog/dlg_Config.cpp
    dialog/dlg_CopyMeas.cpp
    dialog/dlg_Delay.cpp
    dialog/dlg_EventVolume.cpp
    dialog/dlg_OverDrive.cpp
    dialog/dlg_Project.cpp
    dialog/dlg_Property.cpp
    dialog/dlg_Scope.cpp
    dialog/dlg_Unit.cpp
    dialog/dlg_Woice.cpp
    dialog/dlg_YesNo.cpp
)

set(PROJECT_SOURCES_INTERFACE
    interface/if_BaseField.cpp
    interface/if_Copier.cpp
    interface/if_Cursor.cpp
    interface/if_Cursor_Copier.cpp
    interface/if_Cursor_Effector.cpp
    interface/if_Cursor_Keyboard.cpp
    interface/if_Cursor_KeyField.cpp
    interface/if_Cursor_Menu_Division.cpp
    interface/if_Cursor_Menu_Play.cpp
    interface/if_Cursor_Menu_Scope.cpp
    interface/if_Cursor_Menu_Unit.cpp
    interface/if_Cursor_Menu_Woice.cpp
    interface/if_Cursor_Menu_Zoom.cpp
    interface/if_Cursor_Panel_Comment.cpp
    interface/if_Cursor_Panel_Rack.cpp
    interface/if_Cursor_Panel_Scale.cpp
    interface/if_Cursor_Player.cpp
    interface/if_Cursor_PlayField.cpp
    interface/if_Cursor_Projector.cpp
    interface/if_Cursor_ScopeField.cpp
    interface/if_Cursor_Tenkey_Correct.cpp
    interface/if_Cursor_ToolPanel.cpp
    interface/if_Cursor_UnitField.cpp
    interface/if_Cursor_UnitTray.cpp
    interface/if_Cursor_VolumeField.cpp
    interface/if_Cursor_VolumePanel.cpp
    interface/if_Cursor_WoiceTray.cpp
    interface/if_Effector.cpp
    interface/if_Free.cpp
    interface/if_Keyboard.cpp
    interface/if_KeyField.cpp
    interface/if_Menu_Division.cpp
    interface/if_Menu_Play.cpp
    interface/if_Menu_Scope.cpp
    interface/if_Menu_Unit.cpp
    interface/if_Menu_Woice.cpp
    interface/if_Menu_Zoom.cpp
    interface/if_Panel_Comment.cpp
    interface/if_Panel_Logo.cpp
    interface/if_Panel_Rack.cpp
    interface/if_Panel_Scale.cpp
    interface/if_Player.cpp
    interface/if_PlayField.cpp
    interface/if_Projector.cpp
    interface/if_ScopeField.cpp
    interface/if_SelectNo_Group.cpp
    interface/if_SelectNo_Woice.cpp
    interface/if_ShortcutKey.cpp
    interface/if_SubWindows.cpp
    interface/if_Tenkey_Tuning.cpp
    interface/if_ToolPanel.cpp
    interface/if_UnitField.cpp
    interface/if_UnitTray.cpp
    interface/if_VolumeField.cpp
    interface/if_VolumePanel.cpp
    interface/if_WoiceDummy.cpp
    interface/if_WoiceField.cpp
    interface/if_WoiceTray.cpp
    interface/Interface.cpp
)

set(PROJECT_SOURCES
    ActiveTone.cpp
    Generic.cpp
    JapaneseTable.cpp
    Main.cpp
    MainProc.cpp
    MidiInput.cpp
    Project.cpp
    ProjectFile.cpp
    pxtoneProject.cpp
    ScopeEvent.cpp
    UndoEvent.cpp
    Unit.cpp
    UnitFocus.cpp
    Woice.cpp
    WoiceFocus.cpp
    ${PROJECT_SOURCES_DIALOG}
    ${PROJECT_SOURCES_INTERFACE}
    ${PROJECT_RESOURCES}
)

set(PROJECT_HEADERS_DIALOG
    dialog/dlg_AddUnit.h
    dialog/dlg_BuildProgress.h
    dialog/dlg_Delay.h
    dialog/dlg_EventVolume.h
    dialog/dlg_OverDrive.h
)

set(PROJECT_HEADERS_INTERFACE
    interface/if_BaseField.h
    interface/if_Copier.h
    interface/if_Cursor.h
    interface/if_Effector.h
    interface/if_Free.h
    interface/if_Keyboard.h
    interface/if_KeyField.h
    interface/if_Menu_Division.h
    interface/if_Menu_Play.h
    interface/if_Menu_Scope.h
    interface/if_Menu_Unit.h
    interface/if_Menu_Woice.h
    interface/if_Menu_Zoom.h
    interface/if_Panel_Comment.h
    interface/if_Panel_Logo.h
    interface/if_Panel_Rack.h
    interface/if_Panel_Scale.h
    interface/if_Player.h
    interface/if_PlayField.h
    interface/if_Projector.h
    interface/if_ScopeField.h
    interface/if_SelectNo_Group.h
    interface/if_SelectNo_Woice.h
    interface/if_ShortcutKey.h
    interface/if_SubWindows.h
    interface/if_Tenkey_Tuning.h
    interface/if_ToolPanel.h
    interface/if_UnitField.h
    interface/if_UnitTray.h
    interface/if_VolumeField.h
    interface/if_VolumePanel.h
    interface/if_WoiceDummy.h
    interface/if_WoiceField.h
    interface/if_WoiceTray.h
    interface/Interface.h
    interface/SurfaceNo.h
)

set(PROJECT_HEADERS
    ActiveTone.h
    JapaneseTable.h
    MidiInput.h
    Project.h
    ptCollage.h
    resource.h
    ScopeEvent.h
    StdAfx/StdAfx.h
    UndoEvent.h
    Unit.h
    UnitFocus.h
    Woice.h
    WoiceFocus.h

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

