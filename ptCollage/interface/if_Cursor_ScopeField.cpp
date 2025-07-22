
#include "../../Generic/KeyControl.h"
#include "../../Generic/if_gen_Scroll.h"

#include "../UndoEvent.h"

#include "Interface.h"
#include "if_Cursor.h"
#include "if_BaseField.h"
#include "if_ScopeField.h"
#include "if_Menu_Scope.h"

extern if_gen_Scroll    g_ScrlEventH;

static bool _Action_Free( float cur_x, float cur_y )
{
	int32_t divi_w;
	int32_t beat_w;
	int32_t offset_x;

	fRECT* p_field_rect;

	p_field_rect = if_ScopeField_GetRect();

	if( cur_x <  p_field_rect->l ||
		cur_x >= p_field_rect->r ||
		cur_y <  p_field_rect->t ||
		cur_y >= p_field_rect->b ) return false;


	g_cursor.focus        = ifCurFocus_ScopeField;
	g_cursor.p_field_rect = p_field_rect;
	g_cursor.tgt_id       = 0;
	g_cursor.drag_ypos    = 0;
	g_cursor.rect.t       = ( p_field_rect->b + p_field_rect->t ) / 2;
	g_cursor.rect.b       = g_cursor.rect.t;

	offset_x              = g_ScrlEventH.GetOffset();
	divi_w                = if_BaseField_GetDivideWidth();
	beat_w                = if_BaseField_GetBeatWidth();

	g_cursor.drag_xpos[0] = ( (int32_t)( cur_x - p_field_rect->l + offset_x ) / divi_w ) * divi_w;
	g_cursor.drag_xpos[1] = g_cursor.drag_xpos[0] + divi_w;
	g_cursor.rect.l       = g_cursor.drag_xpos[0] + p_field_rect->l - offset_x;
	g_cursor.rect.r       = g_cursor.drag_xpos[1] + p_field_rect->l - offset_x;

	if(       KeyControl_IsClickLeftTrigger()  )
	{
		g_cursor.action  = 1;
		g_cursor.scope   = enum_ScopeMode_Point;
		g_cursor.start_x = cur_x;
		g_cursor.start_y = cur_y;
	}
	else if( KeyControl_IsClickRightTrigger() )
	{
		g_cursor.action = 2;
	}
	return true;
}


static bool _Action_Drag( float cur_x, float cur_y, bool bDelete )
{
	int32_t clock1, clock2;

	if( if_Cursor_DragAction( cur_x, cur_y, &clock1, &clock2 ) )
	{
		if( !bDelete )
		{
			if( clock1 == clock2 )
			{
				if_ScopeField_SetScope( clock1, clock1 );
				if_Menu_Scope_SetPosition( cur_x, g_cursor.p_field_rect->b, true );
			}
			else
			{
				if_ScopeField_SetScope( clock1, clock2 );
			}
		}
		else
		{
			if_Menu_Scope_SetActive( true );
			if( clock1 == clock2 ) if_Menu_Scope_SetPosition( cur_x, g_cursor.p_field_rect->b, true );
			else                   if_Menu_Scope_SetPosition( cur_x, g_cursor.p_field_rect->b, true );
		}
	}

	return true;
}


bool if_Cursor_Action_ScopeField( float cur_x, float cur_y )
{
	bool b_ret = false;

	switch( g_cursor.action )
	{
	// フリー --------
	case 0: b_ret = _Action_Free( cur_x, cur_y              ); break;
	case 1: b_ret = _Action_Drag( cur_x, cur_y, false       ); break;
	case 2: b_ret = _Action_Drag( cur_x, cur_y, true        ); break;
	}

	fRECT* p_field_rect;
	p_field_rect = if_ScopeField_GetRect();
	if( g_cursor.rect.l < p_field_rect->l ) g_cursor.rect.l = p_field_rect->l;
	if( g_cursor.rect.r > p_field_rect->r ) g_cursor.rect.r = p_field_rect->r;

	return b_ret;
}
