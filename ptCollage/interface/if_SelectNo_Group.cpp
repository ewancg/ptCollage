
#include <pxtnService.h>
extern pxtnService *g_pxtn;


#include <pxwDx09Draw.h>
extern pxwDx09Draw *g_dxdraw;

#include "../../Generic/if_Generic.h"

#include "Interface.h"
#include "SurfaceNo.h"
#include "if_Cursor.h"

typedef struct
{
	bool    bActive;
	float   l, b;
	int32_t no;
}
_SELECTNOSTRUCT;

static _SELECTNOSTRUCT _select = {0};

void if_SelectNo_Group_Initialize()
{
	_select.bActive = false;
}

// 座標
void if_SelectNo_Group_Start( float left, float bottom )
{
	_select.bActive = true;
	_select.l       = left;
	_select.b       = bottom;
	_select.no      = 0;
}

unsigned short if_SelectNo_Group_End( float cur_y )
{
	if( !_select.bActive ) return 0;

	_select.bActive = false;

	return (unsigned short)_select.no;
}

void if_SelectNo_Group_Update( float cur_y )
{
	if( !_select.bActive ) return;

	int32_t enable_num = g_pxtn->Group_Num();

	_select.no = (int32_t)( _select.b - cur_y ) / WOICENAME_HEIGHT;
	if( _select.no <           0 ) _select.no = 0;
	if( _select.no >= enable_num ) _select.no = enable_num - 1;
}

void if_SelectNo_Group_Put()
{
	int32_t i;
	float   ypos;
	int32_t enable_num = g_pxtn->Group_Num();

	fRECT rcFocus = {408,272,432,288};
	fRECT rcNoBox = {384,272,408,288};

	if( !_select.bActive ) return;

	for( i = 0; i < enable_num; i++ )
	{
		ypos = _select.b - i * NOBOX_HEIGHT - NOBOX_HEIGHT;

		g_dxdraw->tex_Put_View( _select.l, ypos, &rcNoBox, SURF_FIELDS );

		// 有効チェック
		if( _select.no == i ) g_dxdraw->tex_Put_View( _select.l, ypos, &rcFocus,  SURF_FIELDS );

		if_gen_num6( _select.l + 4 , ypos + 4, i, 2 );
	}
}
