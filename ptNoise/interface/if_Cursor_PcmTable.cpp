
#include "../../Generic/KeyControl.h"
#include "../../Generic/if_Generic.h"

#include "../PcmTable.h"

#include "Interface.h"
#include "if_Cursor.h"
#include "if_PcmTable.h"


extern HWND          g_hWnd_Main;
extern if_gen_Scroll g_ScrlPCM_H;

enum
{
	_DRAGMODE_NONE   = 0,
	_DRAGMODE_PLAY_PCM  ,
	_DRAGMODE_PLAY_SCOPED,
//	_DRAGMODE_PLAY_PTT  ,
	_DRAGMODE_SCOPE     ,
};

bool MainProc_IsLoop();


static bool _Action_Free( float cur_x, float cur_y )
{
	const fRECT *p_field_rect = if_PcmTable_GetRect();

	if( cur_x <  p_field_rect->l ||
		cur_x >= p_field_rect->r ||
		cur_y <  p_field_rect->t ||
		cur_y >= p_field_rect->b ) return false;

	g_cursor.p_field_rect = p_field_rect;

	// 左クリック
	if( KeyControl_IsClickLeftTrigger() )
	{
		if( if_PcmTable_Scope_IsHitPCM( cur_x, cur_y ) )
		{
			PcmTable_Scoped_Play();
			g_cursor.action = _DRAGMODE_PLAY_SCOPED;
		}
		else if( if_PcmTable_IsHitPCM( cur_x, cur_y ) )
		{
			PcmTable_Woice_Play( MainProc_IsLoop() );
			g_cursor.action = _DRAGMODE_PLAY_PCM;
		}
		g_cursor.focus  = CURSORFOCUS_PCMTABLE;
	}
	else if( KeyControl_IsClickRightTrigger() )
	{
		g_cursor.focus  = CURSORFOCUS_PCMTABLE;
		g_cursor.action = _DRAGMODE_SCOPE;
		if_PcmTable_Scope_SetStart( cur_x );
		if_PcmTable_Scope_SetEnd(   cur_x );
	}

	return true;
}

static bool _Action_Drag_Play_PCM( float cur_x, float cur_y )
{
	g_cursor.focus = CURSORFOCUS_PCMTABLE;
	if( !KeyControl_IsClickLeft() || KeyControl_IsClickRight() )
	{
		PcmTable_Woice_Stop( false );
		g_cursor.action = _DRAGMODE_NONE;
	}
	return true;
}

static bool _Action_Drag_Play_Scoped( float cur_x, float cur_y )
{
	g_cursor.focus = CURSORFOCUS_PCMTABLE;
	if( !KeyControl_IsClickLeft() || KeyControl_IsClickRight() )
	{
		PcmTable_Scoped_Stop( false );
		g_cursor.action = _DRAGMODE_NONE;
	}
	return true;
}

static bool _Action_Drag_Scope( float cur_x, float cur_y )
{
	const fRECT* p_rc_field = if_PcmTable_GetRect();

	g_cursor.focus = CURSORFOCUS_PCMTABLE;

	if_PcmTable_Scope_SetEnd( cur_x );
	if_Cursor_DragScroll( p_rc_field->l, p_rc_field->r, cur_x, &g_ScrlPCM_H );

	if( KeyControl_IsClickLeft() || !KeyControl_IsClickRight() )
	{
		g_cursor.action = _DRAGMODE_NONE;
		int32_t start, end;
		if_PcmTable_Scope_GetScope( &start, &end );
		PcmTable_Woice_SetScoped(   start,  end );
	}
	return true;
}


// 音符編集カーソル
bool if_Cursor_Action_PcmTable( float cur_x, float cur_y )
{
	bool b_ret = false;

	switch( g_cursor.action )
	{
	case _DRAGMODE_NONE       : b_ret = _Action_Free(             cur_x, cur_y ); break;
	case _DRAGMODE_PLAY_PCM   : b_ret = _Action_Drag_Play_PCM(    cur_x, cur_y ); break;
	case _DRAGMODE_PLAY_SCOPED: b_ret = _Action_Drag_Play_Scoped( cur_x, cur_y ); break;
	case _DRAGMODE_SCOPE      : b_ret = _Action_Drag_Scope(       cur_x, cur_y ); break;
	}

	return b_ret;
}
