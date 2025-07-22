
#include <pxStdDef.h>


#include <pxwDx09Draw.h>
extern pxwDx09Draw *g_dxdraw;

#include "../../Generic/KeyControl.h"

#include "Interface.h"
#include "SurfaceNo.h"
#include "if_Cursor.h"
#include "if_PcmTable.h"


// ドラッグスクロールウエイト
#define DRAGSCROLLWAIT 1

ACTIONCURSOR      g_cursor;
extern if_gen_Scroll g_ScrlPCM_H;

bool if_Cursor_Action_PcmTable(    float cur_x, float cur_y );
bool if_Cursor_Action_Panel_Scale( float cur_x, float cur_y );
bool if_Cursor_Action_Menu_Zoom(   float cur_x, float cur_y );


///////////////////////////////////////
// 以下はグローバル ///////////////////
///////////////////////////////////////

void if_Cursor_Initialize()
{
	g_cursor.tgt_id  = 0;
	g_cursor.action  = 0;
}

void if_Cursor_DragScroll( float frame1, float frame2, float cur, if_gen_Scroll* scrl )
{
	if( cur <  frame1 || cur >= frame2 )
	{
		if( !g_cursor.scroll_count )
		{
			if( cur <  frame1 ) scrl->Scroll( (int32_t)( frame2 - frame1 ), -1 );
			if( cur >= frame2 ) scrl->Scroll( (int32_t)( frame2 - frame1 ),  1 );
			g_cursor.scroll_count = DRAGSCROLLWAIT;
		}
		else
		{
			g_cursor.scroll_count--;
		}
	}
	else
	{
		g_cursor.scroll_count = 0;
	}
}


bool if_Cursor_Action( float cur_x, float cur_y )
{
	bool b_l_clk = KeyControl_IsClickLeft       ();
	bool b_l_trg = KeyControl_IsClickLeftTrigger();

	// フリー ========================================
	if( g_cursor.action == 0 )
	{
		g_cursor.focus = CURSORFOCUS_NONE;
		while( 1 )
		{
			if( g_ScrlPCM_H.Action( (int32_t)cur_x, (int32_t)cur_y, b_l_clk, b_l_trg ) )
			{
				g_cursor.focus  = CURSORFOCUS_PCM_SCROLL;
				g_cursor.action = 1;
				break;
			}
			if( if_Cursor_Action_Menu_Zoom(   cur_x, cur_y ) ) break;
			if( if_Cursor_Action_Panel_Scale( cur_x, cur_y ) ) break;
			if( if_Cursor_Action_PcmTable(    cur_x, cur_y ) ) break;

			break;
		}

	}
	// ビジー ========================================
	else
	{
		bool bDrag = false;

		switch( g_cursor.focus )
		{
		case CURSORFOCUS_PCM_SCROLL:

			if( g_ScrlPCM_H.Action( (int32_t)cur_x, (int32_t)cur_y, b_l_clk, b_l_trg ) ) bDrag = true;
			else g_cursor.action  = 0;
			break;

		case CURSORFOCUS_MENU_ZOOM  : bDrag = if_Cursor_Action_Menu_Zoom(   cur_x, cur_y ); break;
		case CURSORFOCUS_PANEL_SCALE: bDrag = if_Cursor_Action_Panel_Scale( cur_x, cur_y ); break;
		case CURSORFOCUS_PCMTABLE   : bDrag = if_Cursor_Action_PcmTable(    cur_x, cur_y ); break;
		}
		return true;
	}

	if( g_cursor.focus == CURSORFOCUS_NONE ) return false;
	return true;
}


void if_Cursor_Put()
{

}