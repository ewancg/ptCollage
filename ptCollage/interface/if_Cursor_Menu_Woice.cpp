
#include "../../Generic/KeyControl.h"
#include "../../Generic/if_gen_Scroll.h"

#include "../Woice.h"

#include "Interface.h"
#include "if_Cursor.h"
#include "if_Menu_Woice.h"

extern HWND g_hWnd_Main;


// 音符編集カーソル
bool if_Cursor_Action_Menu_Woice( float cur_x, float cur_y )
{
	fRECT *p_field_rect;
	int32_t top, bottom;
	int32_t w;

	p_field_rect = if_Menu_Woice_GetRect();
	if( if_Menu_Woice_IsTop() ){ top    =                0; bottom = WOICENAME_HEIGHT; }
	else                       { top    = WOICENAME_HEIGHT; bottom =                0; }

	if( cur_x <  p_field_rect->l          ||
		cur_x >= p_field_rect->r          ||
		cur_y <  p_field_rect->t - top    ||
		cur_y >= p_field_rect->b + bottom ){
		if_Menu_Woice_SetActive( false );
		return false;
	}

	g_cursor.focus        = ifCurFocus_Menu_Woice;
	g_cursor.p_field_rect = p_field_rect;
	g_cursor.tgt_id       = if_Menu_Woice_GetMenu( cur_x, cur_y );

	// 左クリック
	if( KeyControl_IsClickLeftTrigger()  )
	{
		w = if_Menu_Woice_GetWoiceIndex();
		switch( if_Menu_Woice_GetMenu( cur_x, cur_y ) )
		{
		case enum_WoiceMenu_Change: Woice_Dialog_Change( w ); break;
		case enum_WoiceMenu_Edit  : Woice_Dialog_Edit(   w ); break;
		case enum_WoiceMenu_Remove: Woice_Dialog_Remove( w ); break;
		case enum_WoiceMenu_Export: Woice_Dialog_Export( w ); break;
		}
		if_Menu_Woice_SetActive( false );
	}

	return true;
}
