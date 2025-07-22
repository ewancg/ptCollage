
#include <pxwAlteration.h>
extern pxwAlteration* g_alte;

#include <pxtnService.h>
extern pxtnService *g_pxtn;

#include "../../Generic/KeyControl.h"
#include "../../Generic/if_gen_Scroll.h"

#include "Interface.h"
#include "if_Cursor.h"
#include "if_PlayField.h"
#include "if_Menu_Play.h"


// 音符編集カーソル
bool if_Cursor_Action_Menu_Play( float cur_x, float cur_y )
{
	fRECT *p_field_rect;

	p_field_rect = if_Menu_Play_GetRect();

	if( cur_x <  p_field_rect->l ||
		cur_x >= p_field_rect->r ||
		cur_y <  p_field_rect->t - SCOPE_HEIGHT  ||
		cur_y >= p_field_rect->b ){
		if_Menu_Play_SetActive( false );
		return false;
	}

	g_cursor.focus        = ifCurFocus_Menu_Play;
	g_cursor.p_field_rect = p_field_rect;
	g_cursor.tgt_id       = if_Menu_Play_GetMenu( cur_x, cur_y );

	// 左クリック
	if( KeyControl_IsClickLeftTrigger()  )
	{
		bool bCancel = false;

		switch( if_Menu_Play_GetMenu( cur_x, cur_y ) )
		{
		case enum_PlayMenu_SetRepeat: g_pxtn->master->set_repeat_meas( (int32_t)g_cursor.drag_xpos[0]     ); break;
		case enum_PlayMenu_SetLast  : g_pxtn->master->set_last_meas  ( (int32_t)g_cursor.drag_xpos[0] + 1 ); break;
		case enum_PlayMenu_CutRepeat: g_pxtn->master->set_repeat_meas(                       0            ); break;
		case enum_PlayMenu_CutLast  : g_pxtn->master->set_last_meas  (                       0            ); break;
		default: bCancel = true;
		}
		if( !bCancel ) g_alte->set();
		if_Menu_Play_SetActive( false );
	}

	return true;
}
