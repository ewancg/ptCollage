
#include "../../Generic/KeyControl.h"

#include "Interface.h"
#include "if_Cursor.h"
#include "if_Menu_Division.h"
#include "if_Panel_Scale.h"

bool if_Cursor_Action_Menu_Division( float cur_x, float cur_y )
{
	if( !if_Menu_Division_IsPanel( cur_x, cur_y ) )
	{
		if_Menu_Division_Hide();
		return false;
	}

	g_cursor.focus        = ifCurFocus_Menu_Division;
	g_cursor.p_field_rect = NULL;
	g_cursor.tgt_id       = 0;

	int divi_index = if_Menu_Division_GetIndex( cur_x, cur_y );

	// 左クリック
	if( KeyControl_IsClickLeftRtrigger()  )
	{
		if_Panel_Scale_SetDivision( divi_index );
		if_Menu_Division_Hide();
	}

	return true;
}
