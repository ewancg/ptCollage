
#include "../../Generic/KeyControl.h"
#include "../../Generic/if_gen_Scroll.h"

#include "../Unit.h"

#include "Interface.h"
#include "if_Cursor.h"
#include "if_Menu_Unit.h"

extern HWND g_hWnd_Main;


// 音符編集カーソル
bool if_Cursor_Action_Menu_Unit( float cur_x, float cur_y )
{
	fRECT*  p_field_rect;
	int32_t top, bottom;
	int32_t u;

	p_field_rect = if_Menu_Unit_GetRect();
	if( if_Menu_Unit_IsTop() ){ top    =               0; bottom = UNITNAME_HEIGHT; }
	else                      { top    = UNITNAME_HEIGHT; bottom =               0; }

	if( cur_x <  p_field_rect->l         ||
		cur_x >= p_field_rect->r         ||
		cur_y <  p_field_rect->t - top   ||
		cur_y >= p_field_rect->b + bottom ){
		if_Menu_Unit_Close();
		return false;
	}

	g_cursor.focus        = ifCurFocus_Menu_Unit;
	g_cursor.p_field_rect = p_field_rect;
	g_cursor.tgt_id       = if_Menu_Unit_GetMenu( cur_x, cur_y );

	// 左クリック
	if( KeyControl_IsClickLeftTrigger()  ){
		u = if_Menu_Unit_GetUnitIndex();

		switch( if_Menu_Unit_GetMenu( cur_x, cur_y ) )
		{
		case enum_UnitMenu_Edit  : Unit_Dialog_Edit( u ); break;
		case enum_UnitMenu_Remove: Unit_Remove(      u ); break;
		}
		if_Menu_Unit_Close();
	}

	return true;
}
