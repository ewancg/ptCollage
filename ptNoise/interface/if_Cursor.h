
#include "../../Generic/if_gen_Scroll.h"

enum CURSORFOCUS
{
	CURSORFOCUS_NONE   = 0 ,
	CURSORFOCUS_MENU_ZOOM  ,
	CURSORFOCUS_PANEL_SCALE,
	CURSORFOCUS_PCMTABLE   ,
	CURSORFOCUS_PCM_SCROLL ,
};


typedef struct
{
	fRECT        rect;
	const fRECT* p_field_rect;
	CURSORFOCUS  focus;
	int32_t      action;
	int32_t      tgt_id;
	float        drag_ypos;
	int32_t      scroll_count;
	int32_t      active_tone_id;

	float        start_x;
	float        start_y;
	int32_t      start_volume_x;
	int32_t      start_volume_y;
	DWORD        wait_count;

}ACTIONCURSOR;

extern ACTIONCURSOR g_cursor;

void if_Cursor_DragScroll( float frame1, float frame2, float cur, if_gen_Scroll* scrl );
void if_Cursor_Initialize();
bool if_Cursor_Action    ( float cur_x, float cur_y );
void if_Cursor_Put       ();


