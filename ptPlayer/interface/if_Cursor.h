
enum ifCurFocus
{
	ifCurFocus_None = 0,
	ifCurFocus_Player,
};

typedef struct
{
	fRECT*     p_field_rect;
	ifCurFocus focus;
	int32_t    action;
	float      drag_xpos[2];
	float      drag_ypos;

	float      start_x;
	float      start_y;
	DWORD      wait_count;

	bool       bON; // トレイを有効にする時に使用。
}
ACTIONCURSOR;

extern ACTIONCURSOR g_cursor;

void if_Cursor_Initialize();
bool if_Cursor_Action( float cur_x, float cur_y, PTP_SIGN *p_ptp_sign );


