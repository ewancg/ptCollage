
#include "../../Generic/KeyControl.h"

#include "Interface.h"
#include "if_Cursor.h"
#include "if_ToolPanel.h"


enum{
	_DRAGMODE_NONE =    0,
	_DRAGMODE_BUTTON     ,
	_DRAGMODE_SHORTCUTKEY,
};


static bool _Action_Free( float cur_x, float cur_y )
{
	enum_ToolButton button;

	if( !KeyControl_IsClickLeftTrigger()     ) return false;

	button = if_ToolPanel_GetHitButton( cur_x, cur_y );

	if( !if_ToolPanel_SetHitButton( button ) ) return false;

	if( button == enum_ToolButton_U_add      ) return true ;

	g_cursor.action = _DRAGMODE_BUTTON;
	g_cursor.focus  = ifCurFocus_ToolPanel;

	return true;
}

static bool _Action_Drag_Button( float cur_x, float cur_y )
{
	if( KeyControl_IsClickRight() ||
		!KeyControl_IsClickLeft() ) g_cursor.action = _DRAGMODE_NONE;
	return true;
}

static bool _Action_Drag_ShortcutKey( float cur_x, float cur_y )
{
	if( !KeyControl_IsKey( VK_F1 ) &&
		!KeyControl_IsKey( VK_F2 ) &&
		!KeyControl_IsKey( VK_F3 ) ) g_cursor.action = _DRAGMODE_NONE;
	return true;
}


// 音符編集カーソル
bool if_Cursor_Action_ToolPanel( float cur_x, float cur_y )
{
	bool b_ret = false;

	switch( g_cursor.action )
	{
	case _DRAGMODE_NONE       : b_ret = _Action_Free(             cur_x, cur_y ); break;
	case _DRAGMODE_BUTTON     : b_ret = _Action_Drag_Button(      cur_x, cur_y ); break;
	case _DRAGMODE_SHORTCUTKEY: b_ret = _Action_Drag_ShortcutKey( cur_x, cur_y ); break;
	}

	return b_ret;
}
