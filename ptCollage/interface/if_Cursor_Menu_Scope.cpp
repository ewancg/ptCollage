
#include "../../Generic/KeyControl.h"
#include "../../Generic/if_gen_Scroll.h"

#include "../UnitFocus.h"
#include "../ScopeEvent.h"

#include "Interface.h"

#include "if_Cursor.h"
#include "if_ToolPanel.h"
#include "if_ScopeField.h"
#include "if_Menu_Scope.h"
#include "if_Copier.h"

extern HWND g_hWnd_Main;

bool Function_IDM_TRANSPOSE( HWND hWnd );
bool Function_IDM_SCOPE(     HWND hWnd );

// 音符編集カーソル
bool if_Cursor_Action_Menu_Scope( float cur_x, float cur_y )
{
	fRECT*  p_rc;
	int32_t clock1, clock2;

	p_rc = if_Menu_Scope_GetRect();

	if( cur_x <  p_rc->l                ||
		cur_x >= p_rc->r                ||
		cur_y <  p_rc->t - SCOPE_HEIGHT ||
		cur_y >= p_rc->b ){
		if_Menu_Scope_SetActive( false );
		return false;
	}

	g_cursor.focus        = ifCurFocus_Menu_Scope;
	g_cursor.p_field_rect = p_rc;
	g_cursor.tgt_id       = if_Menu_Scope_GetMenu( cur_x, cur_y );

	// 左クリック
	if( KeyControl_IsClickLeftTrigger()  )
	{
		if_ScopeField_GetSelected( &clock1, &clock2 );
		switch( if_Menu_Scope_GetMenu( cur_x, cur_y ) )
		{
		case enum_ScopeMenu_Copy     : ScopeEvent_Copy(   clock1, clock2,   if_Copier_GetEventKinds() ); break;
		case enum_ScopeMenu_Cut      : ScopeEvent_Cut(    clock1, clock2 ); if_Copier_AllCheck();        break;
		case enum_ScopeMenu_Clear    : ScopeEvent_Clear(  clock1, clock2 ); break;
		case enum_ScopeMenu_Delete   : ScopeEvent_Delete( clock1, clock2 ); break;
		case enum_ScopeMenu_Paste    : ScopeEvent_Paste(  clock1,      1,   if_Copier_GetEventKinds() ); break;
		case enum_ScopeMenu_Insert   : ScopeEvent_Insert( clock1,      1 ); break;
		case enum_ScopeMenu_Transpose: Function_IDM_TRANSPOSE( g_hWnd_Main ); KeyControl_Clear(); break;
		case enum_ScopeMenu_Scope    : Function_IDM_SCOPE(     g_hWnd_Main ); KeyControl_Clear(); break;
		}
		if_Menu_Scope_SetActive( false );
	}

	return true;
}
