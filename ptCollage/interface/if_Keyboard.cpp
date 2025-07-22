
#include <pxtnEvelist.h>


#include <pxwDx09Draw.h>
extern pxwDx09Draw *g_dxdraw;

#include "../../Generic/if_gen_Scroll.h"
#include "../../Generic/if_Generic.h"

#include "../UnitFocus.h"

#include "if_Keyboard.h"
#include "if_ToolPanel.h"
#include "if_VolumePanel.h"
#include "Interface.h"
#include "SurfaceNo.h"


extern if_gen_Scroll g_ScrlKeyV;

static fRECT _rcField;
static char  _push_flag[ KEYBOARD_KEYNUM / 8 ];


void if_Keyboard_Initialize()
{
	memset( _push_flag, 0, KEYBOARD_KEYNUM / 8 );
}

void if_Keyboard_SetRect( const fRECT *rc_view )
{
	switch( if_ToolPanel_GetMode() )
	{
	case enum_ToolMode_K:
		_rcField.l = rc_view->l;
		_rcField.r = rc_view->l + NAMETRAY_WIDTH;
		_rcField.t = rc_view->t + HEADER_H + TOOLPANEL_HEIGHT + UNIT_HEIGHT + KEY_SEPARATOR;
		if( if_VolumePanel_IsUse() ) _rcField.b = rc_view->b - SCROLL_HEIGHT - VOLUME_HEIGHT;
		else                         _rcField.b = rc_view->b - SCROLL_HEIGHT;
		break;

	default: _rcField.b = _rcField.t;
	}
}

fRECT*if_Keyboard_GetRect()
{
	return &_rcField;
}



// キーボードを表示
void if_Keyboard_Put()
{
	float offset_y = g_ScrlKeyV.GetOffset();
	float size     = g_ScrlKeyV.GetSize  ();

	fRECT rc  = {  0,  0,144,192};

	if_gen_tile_v( &_rcField, &rc, 1, (int32_t)offset_y, SURF_FIELDS );

	// キー番号を表示
	float   key_height;
	float   y;
	int32_t i;

	key_height = _rcField.b - _rcField.t;

	for( i = 0; i <= 8; i++ )
	{
		y = _rcField.t + (i * (KEY_HEIGHT*12) ) - offset_y + 4;
		if( y >= _rcField.t - 12 && y <=  _rcField.b + 4 )
		{
			if_gen_num6_clip( _rcField.l + 32, y, 7 - i, 2, &_rcField );
		}
	}

	// プッシュ
	int32_t key;
	fRECT   rcPush  = {144,  0,232, 16};

	for( i = 0; i < 88; i++ )
	{
		if( _push_flag[ i / 8 ] & ( 0x80 >> (i%8) ) )
		{
			rcPush.t = (float)( 0 + ( i % 12 ) * KEY_HEIGHT );
			rcPush.b = (float)( rcPush.t +       KEY_HEIGHT );
			g_dxdraw->tex_Put_Clip( _rcField.l +  56, i * KEY_HEIGHT - offset_y + _rcField.t, &rcPush,  SURF_FIELDS, &_rcField );
		}
	}

	// 基本キー
	int32_t u;
	fRECT   rcBasic = {368,272,384,288};

	if( ( u = UnitFocus_Get() ) >= 0 )
	{
		key = 88 - ( EVENTDEFAULT_BASICKEY / 0x100 - 0x14 );
		g_dxdraw->tex_Put_Clip( _rcField.l + 128, key * KEY_HEIGHT - offset_y + _rcField.t, &rcBasic, SURF_FIELDS, &_rcField );
	}
}

void if_Keyboard_SetPush( int32_t key, bool bOn )
{
	int32_t bit;
	bit = 87 - ( key );
	if( bOn ) _push_flag[ bit / 8 ] |=  ( 0x80 >> (bit%8) );
	else      _push_flag[ bit / 8 ] &= ~( 0x80 >> (bit%8) );
}

void if_Keyboard_ClearPush()
{
	memset( _push_flag, 0, KEYBOARD_KEYNUM / 8 );
}





