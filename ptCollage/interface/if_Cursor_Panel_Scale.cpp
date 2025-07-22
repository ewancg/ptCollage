
#include "../../Generic/KeyControl.h"

#include "if_Panel_Scale.h"
#include "if_Menu_Division.h"
#include "if_Menu_Zoom.h"
#include "if_Cursor.h"


bool if_Cursor_Action_Panel_Scale( float cur_x, float cur_y )
{
	if( !KeyControl_IsClickLeftTrigger() ) return false;

	if( if_Panel_Scale_IsDiviButton( cur_x, cur_y ) )
	{
		g_cursor.focus = ifCurFocus_Panel_Scale;
		if_Menu_Division_Show();
		return true;
	}

	if( if_Panel_Scale_IsZoomButton( cur_x, cur_y ) )
	{
		g_cursor.focus = ifCurFocus_Panel_Scale;
		if_Menu_Zoom_Show();
		return true;
	}
	return false;
}
