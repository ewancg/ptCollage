﻿
#include "../../Generic/KeyControl.h"

#include "Interface.h"
#include "if_Cursor.h"
#include "if_Copier.h"


extern HWND g_hWnd_Main;

enum enum_DragMode
{
	enum_DragMode_Frame = 0,
	enum_DragMode_Check,
	enum_DragMode_Shut ,
};

static enum_DragMode _drag_mode;

static bool _Action_Free( float cur_x, float cur_y )
{
	if( !if_Copier_IsOpen() ) return false;

	fRECT* p_field_rect = if_Copier_GetRect();

	if( cur_x <  p_field_rect->l ||
		cur_x >= p_field_rect->r ||
		cur_y <  p_field_rect->t ||
		cur_y >= p_field_rect->b ) return false;

	g_cursor.p_field_rect = p_field_rect;
	g_cursor.drag_xpos[0] = cur_x;
	g_cursor.drag_ypos    = cur_y;
	

	// 左クリック
	if(       KeyControl_IsClickLeftTrigger()  )
	{
		if_Copier_SetFocus();

		g_cursor.action = 1;
		g_cursor.focus  = ifCurFocus_Copier;

		if(      if_Copier_CheckButton( cur_x, cur_y, &g_cursor.bON ) ){ _drag_mode = enum_DragMode_Check; }
		else if( if_Copier_ShutButton(  cur_x, cur_y                ) ){ _drag_mode = enum_DragMode_Shut ; }
		else
		{
			if_Copier_GetPosition( &g_cursor.start_x, &g_cursor.start_y );
			_drag_mode = enum_DragMode_Frame;
		}
	}

	return true;
}

static bool _Action_Drag( float cur_x, float cur_y )
{
		
	fRECT* p_field_rect;
	bool   bDrag = false;

	p_field_rect          = if_Copier_GetRect();
	g_cursor.focus        = ifCurFocus_Copier;
	g_cursor.p_field_rect = p_field_rect;

	//ドラッグキャンセル
	if( KeyControl_IsClickLeft() && KeyControl_IsClickRight() )
	{
		g_cursor.action = 0;

		switch( _drag_mode )
		{
		case enum_DragMode_Check:
			break;
		case enum_DragMode_Shut :
			break;
		case enum_DragMode_Frame:
			if_Copier_SetPosition( g_cursor.start_x, g_cursor.start_y );
			break;
		}
		return true;
	}

	switch( _drag_mode )
	{
	case enum_DragMode_Check:

		if_Copier_CheckButton( cur_x, cur_y, g_cursor.bON );
		break;

	case enum_DragMode_Shut :

		break;

	case enum_DragMode_Frame:

		if_Copier_SetPosition(
			g_cursor.start_x + cur_x - g_cursor.drag_xpos[0],
			g_cursor.start_y + cur_y - g_cursor.drag_ypos );
		break;
	}

	// ドラッグ終了
	if( !KeyControl_IsClickLeft() ) g_cursor.action = 0;

	return true;
}

// 音符編集カーソル
bool if_Cursor_Action_Copier( float cur_x, float cur_y )
{
	bool b_ret = false;

	switch( g_cursor.action )
	{
	case 0: b_ret = _Action_Free( cur_x, cur_y ); break;
	case 1: b_ret = _Action_Drag( cur_x, cur_y ); break;
	}

	return b_ret;
}

