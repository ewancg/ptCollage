
#include <pxtnService.h>
extern pxtnService*  g_pxtn    ;

#include <pxtonewinXA2.h>
extern pxtonewinXA2* g_strm_xa2;

#include "../../Generic/KeyControl.h"
#include "../../Generic/if_gen_Scroll.h"

#include "../UnitFocus.h"
#include "../Unit.h"
#include "../ActiveTone.h"

#include "Interface.h"
#include "if_Cursor.h"
#include "if_UnitTray.h"
#include "if_Menu_Unit.h"
#include "if_KeyField.h"
#include "if_ToolPanel.h"

enum
{
	_MODE_FREE = 0,
	_MODE_REPLACE ,
	_MODE_OPERATED,
	_MODE_PLAYED  ,
	_MODE_DUMMY   ,
	_MODE_CALLMENU,
};

extern if_gen_Scroll g_ScrlEventH;
extern if_gen_Scroll g_ScrlUnitV;
extern HWND       g_hWnd_Main;

static bool _ActionFree( float cur_x, float cur_y )
{
	int32_t num;
	int32_t u;
	int32_t offset;
	fRECT*  p_field_rect;

	int32_t scroll_dir;

	switch( if_ToolPanel_GetMode() )
	{
	case enum_ToolMode_K:
		if(      KeyControl_IsKeyTrigger( VK_PRIOR ) ) scroll_dir = -1;
		else if( KeyControl_IsKeyTrigger( VK_NEXT  ) ) scroll_dir =  1;
		else                                           scroll_dir =  0;
		break;
	case enum_ToolMode_U:
		if(      KeyControl_IsKeyTrigger( VK_PRIOR ) || KeyControl_IsKeyTrigger( VK_UP   ) ) scroll_dir = -1;
		else if( KeyControl_IsKeyTrigger( VK_NEXT  ) || KeyControl_IsKeyTrigger( VK_DOWN ) ) scroll_dir =  1;
		else                                                                                 scroll_dir =  0;
		break;
	default: scroll_dir = 0;
	}

	// カーソルキー
	if( scroll_dir )
	{
		if( scroll_dir == -1 ) UnitFocus_Shift( false );
		else                   UnitFocus_Shift( true  );
		if_UnitTray_JustScroll();
		u               = UnitFocus_Get(); if( u < 0 ) return false;
		g_cursor.action = _MODE_DUMMY;
		g_cursor.focus  = ifCurFocus_UnitTray;
		g_cursor.tgt_id = u;
		if( !g_strm_xa2->tune_is_sampling() )
		{
			if_Cursor_SetActiveTone_Unit( u, cur_x );
		}
		return true;
	}

	p_field_rect     = if_UnitTray_GetRect();
	if( g_cursor.action == _MODE_FREE )
	{
		if( cur_x <  p_field_rect->l + 16 ||
			cur_x >= p_field_rect->r    ||
			cur_y <  p_field_rect->t    ||
			cur_y >= p_field_rect->b ) return false;
	}

	offset = g_ScrlUnitV.GetOffset();
	num    = g_pxtn->Unit_Num();

	pxtnUnit *p_unit;

	// どのユニットか
	for( u = 0; u < num; u++ )
	{
		if( (p_unit = g_pxtn->Unit_Get_variable( u ) )                          &&
			cur_y >= p_field_rect->t + u * UNIT_HEIGHT               - offset &&
			cur_y <  p_field_rect->t + u * UNIT_HEIGHT + UNIT_HEIGHT - offset ) break;
	}
	if( u == num ) return false;

	g_cursor.drag_idy  = (int32_t)( ( cur_y - p_field_rect->t + offset ) / UNIT_HEIGHT );
	g_cursor.rect.l = p_field_rect->l + 16;
	g_cursor.rect.t = p_field_rect->t + g_cursor.drag_idy * UNIT_HEIGHT - offset;

	if( KeyControl_IsClickLeftTrigger() )
	{
		// 再生有効
		if( cur_x < p_field_rect->l + 32 )
		{
			if( p_unit->get_played() ) g_cursor.bON = false;
			else                  g_cursor.bON = true;
			g_cursor.p_field_rect = p_field_rect;
			g_cursor.focus        = ifCurFocus_UnitTray;
			g_cursor.action       = _MODE_PLAYED;
			p_unit->set_played( g_cursor.bON );
		}
		// 編集有効(一括)
		else if( KeyControl_IsKey( VK_SHIFT ) )
		{
			int32_t start_u = UnitFocus_Get();
			int32_t end_u   = u;
			g_pxtn->Unit_SetOpratedAll( false );
			if_UnitTray_LumpSelect( start_u, end_u );
			UnitFocus_Set( u, true );

			g_cursor.p_field_rect = p_field_rect;
			g_cursor.focus        = ifCurFocus_UnitTray;
			g_cursor.action       = _MODE_DUMMY;
		}
		// 編集有効
		else if( KeyControl_IsKey( VK_CONTROL ) )
		{
			if( p_unit->get_operated() ) g_cursor.bON = false;
			else                         g_cursor.bON = true;
			g_cursor.p_field_rect = p_field_rect;
			g_cursor.focus        = ifCurFocus_UnitTray;
			g_cursor.action       = _MODE_OPERATED;
			p_unit->set_operated( g_cursor.bON );
		}
		// 位置入れ替え
		else
		{
			g_cursor.start_x      = cur_x;
			g_cursor.start_y      = cur_y;
			g_cursor.focus        = ifCurFocus_UnitTray;

			g_pxtn->Unit_SetOpratedAll( false );
			UnitFocus_Set( u, true );

			if( !g_strm_xa2->tune_is_sampling() )
			{
				if_Cursor_SetActiveTone_Unit( u, cur_x );
				g_cursor.tgt_id       = u;
				g_cursor.p_field_rect = p_field_rect;
				if( if_ToolPanel_GetMode() == enum_ToolMode_U ) g_cursor.action = _MODE_REPLACE;
				else                                            g_cursor.action = _MODE_DUMMY  ;
			}
		}
	}
	// ユニットメニュー
	else if( KeyControl_IsClickRightTrigger() )
	{
		// 点灯
		g_cursor.p_field_rect = p_field_rect;
		g_cursor.focus        = ifCurFocus_UnitTray;
		g_cursor.action       = _MODE_CALLMENU;
		g_cursor.tgt_id       = u;
		g_pxtn->Unit_SetOpratedAll( false );
		UnitFocus_Set( u, true );
	}
	else
	{
		return false;
	}

	return true;
}


static bool _ActionDrag_Replace( float cur_x, float cur_y )
{
	int32_t offset       = g_ScrlUnitV.GetOffset();
	fRECT*  p_field_rect = g_cursor.p_field_rect;

	//ドラッグキャンセル
	if( KeyControl_IsClickRight() && KeyControl_IsClickLeft() )
	{
		if_Cursor_StopActiveTone();
		g_cursor.action = _MODE_FREE;
		return true;
	}

	if( KeyControl_IsClickLeft() )
	{
		g_cursor.drag_idy = (int32_t)( ( cur_y - p_field_rect->t + offset ) / UNIT_HEIGHT );
		if( g_cursor.drag_idy <  0 ) g_cursor.drag_idy = 0;

		int32_t max_unit_idy = g_pxtn->Unit_Num() - 1;
		if( g_cursor.drag_idy > max_unit_idy ) g_cursor.drag_idy = max_unit_idy;
		g_cursor.rect.l = p_field_rect->l + 16;
		g_cursor.rect.t = p_field_rect->t + g_cursor.drag_idy * UNIT_HEIGHT - offset;

		if_Cursor_DragScroll( p_field_rect->t, p_field_rect->b, cur_y, &g_ScrlUnitV );
	}

	// ドラッグセット
	else
	{
		g_cursor.action = _MODE_FREE;
		if_Cursor_StopActiveTone();
		Unit_Replace( g_cursor.tgt_id, g_cursor.drag_idy );
	}

	return true;
}


//　編集有効
static bool _ActionDrag_Operated( float cur_x, float cur_y )
{
	int32_t num = g_pxtn->Unit_Num();
	int32_t u;
	int32_t offset       = g_ScrlUnitV.GetOffset();
	fRECT*  p_field_rect = g_cursor.p_field_rect;

	pxtnUnit *p_unit;
	for( u = 0; u < num; u++ )
	{
		if( ( p_unit = g_pxtn->Unit_Get_variable( u ) )                       &&
			cur_y >= p_field_rect->t + u * UNIT_HEIGHT               - offset &&
			cur_y <  p_field_rect->t + u * UNIT_HEIGHT + UNIT_HEIGHT - offset ) break;
	}
	if( u != num )
	{
		//ドラッグキャンセル
		if( KeyControl_IsClickLeft() && !KeyControl_IsClickRight() ) p_unit->set_operated( g_cursor.bON );
		else                                                         g_cursor.action   = _MODE_FREE;
	}
	return true;
}

static bool _ActionDrag_Played( float cur_x, float cur_y )
{
	int32_t u;
	int32_t num          = g_pxtn->Unit_Num();
	int32_t offset       = g_ScrlUnitV.GetOffset();
	fRECT*  p_field_rect = g_cursor.p_field_rect;

	// ドラッグ終了
	if( !KeyControl_IsClickLeft() || KeyControl_IsClickRight() ) g_cursor.action = _MODE_FREE;
	else
	{
		pxtnUnit *p_u;
		for( u = 0; u < num; u++ )
		{
			if( ( p_u = g_pxtn->Unit_Get_variable( u ) )                          &&
				cur_y >= p_field_rect->t + u * UNIT_HEIGHT               - offset &&
				cur_y <  p_field_rect->t + u * UNIT_HEIGHT + UNIT_HEIGHT - offset ) break;
		}
		if( u != num ) p_u->set_played( g_cursor.bON );
	}

	return true;
}

static bool _ActionDrag_Dummy()
{
	if( !KeyControl_IsKey( VK_UP ) && !KeyControl_IsKey( VK_DOWN ) )
	{
		if_Cursor_StopActiveTone();
		g_cursor.action = _MODE_FREE;
	}
	return true;
}

static bool _ActionDrag_CallMenu( float cur_x, float cur_y )
{
	float x, y;
	if( KeyControl_IsClickLeft() && KeyControl_IsClickRight() )
	{
		g_cursor.action = _MODE_FREE;
		return true;
	}
	if( !KeyControl_IsClickRight() )
	{
		if( if_UnitTray_GetNamePosition( g_cursor.tgt_id, &x, &y ) )
		{
			if_Menu_Unit_SetPosition( x, y, g_cursor.tgt_id );
		}
		g_cursor.action = _MODE_FREE;
	}

	return true;
}


// ユニット編集カーソル
bool if_Cursor_Action_UnitTray( float cur_x, float cur_y )
{
	bool b_ret = false;

	switch( g_cursor.action )
	{
	case _MODE_FREE    : b_ret = _ActionFree(          cur_x, cur_y ); break;
	case _MODE_REPLACE : b_ret = _ActionDrag_Replace(  cur_x, cur_y ); break;
	case _MODE_OPERATED: b_ret = _ActionDrag_Operated( cur_x, cur_y ); break;
	case _MODE_PLAYED  : b_ret = _ActionDrag_Played(   cur_x, cur_y ); break;
	case _MODE_DUMMY   : b_ret = _ActionDrag_Dummy(                 ); break;
	case _MODE_CALLMENU: b_ret = _ActionDrag_CallMenu( cur_x, cur_y ); break;
	}

	return b_ret;
}
