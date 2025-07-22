
#include <pxtnPulse_Frequency.h>
extern pxtnPulse_Frequency *g_freq;

#include <pxtnService.h>
extern pxtnService *g_pxtn;

#include "../../Generic/KeyControl.h"
#include "../../Generic/if_gen_Scroll.h"

#include "../UnitFocus.h"
#include "../ActiveTone.h"

#include "Interface.h"
#include "if_Cursor.h"
#include "if_Keyboard.h"
#include "if_KeyField.h"
#include "if_BaseField.h"

extern if_gen_Scroll    g_ScrlKeyV;


static bool _Action_Free( float cur_x, float cur_y )
{
	int32_t offset_y;
	int32_t target = UnitFocus_Get(); if( target < 0 ) return false;
	fRECT*  p_field_rect = if_Keyboard_GetRect();

	if( cur_x <  p_field_rect->l ||
		cur_x >= p_field_rect->r ||
		cur_y <  p_field_rect->t ||
		cur_y >= p_field_rect->b ) return false;

	offset_y              = g_ScrlKeyV.GetOffset();

	g_cursor.focus        = ifCurFocus_Keyboard;
	g_cursor.p_field_rect = p_field_rect;
	g_cursor.drag_ypos    = cur_y - p_field_rect->t + offset_y;
	g_cursor.tgt_id       = target;

	// 左クリック
	if(       KeyControl_IsClickLeftTrigger()  )
	{
		int32_t key_index;
		float   freq_rate;

		if( !g_pxtn->Unit_Get( g_cursor.tgt_id ) ) return true;
		key_index       = 87 - ( (int32_t)g_cursor.drag_ypos / KEY_HEIGHT );
		freq_rate       = g_freq->Get( ( key_index + 0x15 ) * 0x100 - EVENTDEFAULT_BASICKEY );
		g_cursor.action = 1;

		if_Cursor_SetActiveTone_Unit( target, cur_x, freq_rate );
		if_Keyboard_ClearPush();
		if_Keyboard_SetPush( key_index, true );
	}

	return true;
}

static bool _Action_Drag( float cur_x, float cur_y )
{
	int32_t offset_y     = g_ScrlKeyV.GetOffset();
	fRECT*  p_field_rect = if_Keyboard_GetRect ();

	g_cursor.focus        = ifCurFocus_Keyboard;
	g_cursor.p_field_rect = p_field_rect;

	// 周波数変更
	{
		int32_t key_index;
		float   freq_rate;

		g_cursor.drag_ypos = cur_y - p_field_rect->t + offset_y;
		if( g_cursor.drag_ypos < 0                                      ) g_cursor.drag_ypos = 0;
		if( g_cursor.drag_ypos >= KEYBOARD_KEYHEIGHT * KEYBOARD_KEYNUM  ) g_cursor.drag_ypos = KEYBOARD_KEYHEIGHT * KEYBOARD_KEYNUM -1;
		key_index          = 87 - ( (int32_t)g_cursor.drag_ypos / KEY_HEIGHT );
		freq_rate          = g_freq->Get( ( key_index + 0x15 ) * 0x100 - EVENTDEFAULT_BASICKEY );
		if_Cursor_ChangeActiveTone( freq_rate );
		if_Keyboard_ClearPush();
		if_Keyboard_SetPush( key_index, true );
	}

	if( !KeyControl_IsClickLeft() )
	{
		if_Cursor_StopActiveTone();
		g_cursor.action = 0;
		if_Keyboard_ClearPush();
	}

	return true;
}

// 音符編集カーソル
bool if_Cursor_Action_Keyboard( float cur_x, float cur_y )
{
	bool b_ret = false;

	switch( g_cursor.action ){
	case 0: b_ret = _Action_Free( cur_x, cur_y ); break;
	case 1: b_ret = _Action_Drag( cur_x, cur_y ); break;
	}

	return b_ret;
}
