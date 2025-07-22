#include "../../Generic/if_gen_Scroll.h"

#include <pxStdDef.h>

#include <pxPalette.h>

enum ifCurFocus
{
	ifCurFocus_None = 0     ,
	ifCurFocus_Menu_Play    ,
	ifCurFocus_Menu_Scope   ,
	ifCurFocus_Menu_Unit    ,
	ifCurFocus_Menu_Woice   ,
	ifCurFocus_Menu_Division,
	ifCurFocus_Menu_Zoom    ,
	ifCurFocus_Tenkey_Tuning,
	ifCurFocus_Player       ,
	ifCurFocus_Copier       ,
	ifCurFocus_Projector    ,
	ifCurFocus_Effector     ,
	ifCurFocus_EventHScroll ,
	ifCurFocus_WoiceHScroll ,
	ifCurFocus_KeyScroll    ,
	ifCurFocus_UnitScroll   ,
	ifCurFocus_WoiceScroll  ,
	ifCurFocus_WoiceTray    ,
	ifCurFocus_UnitField    ,
	ifCurFocus_VolumeField  ,
	ifCurFocus_UnitTray     ,
	ifCurFocus_KeyField     ,
	ifCurFocus_Keyboard     ,
	ifCurFocus_PlayField    ,
	ifCurFocus_ScopeField   ,
	ifCurFocus_ToolPanel    ,
	ifCurFocus_VolumePanel  ,

	ifCurFocus_Panel_Rack    ,
	ifCurFocus_Panel_Scale   ,
};

enum enum_ScopeMode
{
	enum_ScopeMode_Point = 0,
	enum_ScopeMode_Scope,
};

typedef struct
{
	fRECT            rect;
	fRECT*           p_field_rect;
	ifCurFocus       focus;
	int32_t          action; // 0: free
	enum_ScopeMode   scope;
	int32_t          tgt_id;
	float            drag_xpos[ 2 ];
	float            drag_ypos   ;
	int32_t          drag_idy    ;
	int32_t          scroll_count;
	float            start_x;
	float            start_y;

	bool             bON; // トレイを有効にする時に使用。
	int              active_tone_id;
	bool             active_tone_on;
}
ACTIONCURSOR;

extern ACTIONCURSOR g_cursor;

bool if_Cursor_init( const pxPalette* pal );

void if_Cursor_DragScroll( float frame1, float frame2, float cur, if_gen_Scroll* scrl );
bool if_Cursor_Action    ( float cur_x, float cur_y );
void if_Cursor_Put       ();

bool if_Cursor_DragAction( float cur_x, float cur_y, int32_t *p_clock1, int32_t *p_clock2 );

void if_Cursor_SetActiveTone_Unit( int32_t u, float cur_x, float freq_rate, int32_t pan_vol, int32_t velocity, int32_t pan_time );
void if_Cursor_SetActiveTone_Unit( int32_t u, float cur_x, float freq_rate );
void if_Cursor_SetActiveTone_Unit( int32_t u, float cur_x );

void if_Cursor_SetActiveTone_Woice( int32_t w );
void if_Cursor_ChangeActiveTone   ( float freq_rate );
void if_Cursor_StopActiveTone     ();
