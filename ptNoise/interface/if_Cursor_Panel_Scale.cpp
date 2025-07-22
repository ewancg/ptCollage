
#include "../../Generic/KeyControl.h"

#include "if_Cursor.h"
#include "if_Panel_Scale.h"
#include "if_Menu_Zoom.h"

bool if_Cursor_Action_Panel_Scale( float cur_x, float cur_y )
{
	if( !KeyControl_IsClickLeftTrigger() ) return false;

	if( if_Panel_Scale_IsZoomButton( cur_x, cur_y ) )
	{
		g_cursor.focus = CURSORFOCUS_PANEL_SCALE;
		if_Menu_Zoom_Show();
		return true;
	}
	return false;
}
