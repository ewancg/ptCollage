
#include "../../Generic/KeyControl.h"

#include "Interface.h"
#include "if_Cursor.h"
#include "if_Menu_Zoom.h"
#include "if_Panel_Scale.h"

bool if_Cursor_Action_Menu_Zoom( float cur_x, float cur_y )
{
	if( !if_Menu_Zoom_IsPanel( cur_x, cur_y ) )
	{
		if_Menu_Zoom_Hide();
		return false;
	}

	g_cursor.focus        = ifCurFocus_Menu_Zoom;
	g_cursor.p_field_rect = NULL;
	g_cursor.tgt_id       = 0;

	int32_t zoom_index = if_Menu_Zoom_GetIndex( cur_x, cur_y );

	// 左クリック
	if( KeyControl_IsClickLeftRtrigger()  )
	{
		if_Panel_Scale_SetZoom( zoom_index );
		if_Menu_Zoom_Hide();
	}

	return true;
}
