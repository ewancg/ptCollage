
#include "../../Generic/KeyControl.h"

#include "Interface.h"
#include "if_Cursor.h"
#include "if_VolumePanel.h"

static bool _Action_Free( float cur_x, float cur_y )
{
	if( !KeyControl_IsClickLeftTrigger() ) return false;
	if( !if_VolumePanel_SetHitButton( if_VolumePanel_GetHitButton( cur_x, cur_y ) ) ) return false;
	g_cursor.action = 1;
	g_cursor.focus  = ifCurFocus_VolumePanel;
	return true;
}

static bool _Action_Drag( float cur_x, float cur_y )
{

	if( KeyControl_IsClickRight() || !KeyControl_IsClickLeft() ) g_cursor.action = 0;
	return true;
}

// 音符編集カーソル
bool if_Cursor_Action_VolumePanel( float cur_x, float cur_y )
{
	bool b_ret = false;

	switch( g_cursor.action ){
	case 0: b_ret = _Action_Free( cur_x, cur_y ); break;
	case 1: b_ret = _Action_Drag( cur_x, cur_y ); break;
	}

	return b_ret;
}
