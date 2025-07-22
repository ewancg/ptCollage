
#include "../../Generic/KeyControl.h"

#include "if_Panel_Rack.h"
#include "if_Cursor.h"

// 音符編集カーソル
bool if_Cursor_Action_Panel_Rack( float cur_x, float cur_y )
{
	switch( g_cursor.action )
	{
	case 0:

		if( !KeyControl_IsClickLeftTrigger()         ) return false;
		if( !if_Panel_Rack_HitButton( cur_x, cur_y ) ) return false;
		g_cursor.focus  = ifCurFocus_Panel_Rack;
		g_cursor.action = 0;
		return true;

	case 1:

		if( !KeyControl_IsClickLeft() ) g_cursor.action = 0;
		return true;
	}
	return false;
}
