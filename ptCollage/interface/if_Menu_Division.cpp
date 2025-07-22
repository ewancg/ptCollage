

#include <pxwDx09Draw.h>
extern pxwDx09Draw *g_dxdraw;

#include "Interface.h"
#include "SurfaceNo.h"
#include "if_Panel_Scale.h"


#define _MENU_W   56
#define _MENU_H  180

#define _BUTTON_W 56
#define _BUTTON_H 16


typedef struct
{
	bool    b_active;
	float   x, y;
	int32_t divi_index;

}_MENUSTRUCT_DIVI;

static fRECT            _rcMenu    = {0};
static _MENUSTRUCT_DIVI _divi_menu = {0};

void if_Menu_Division_Initialize()
{
	_divi_menu.b_active = false;
}

// 座標
void if_Menu_Division_Show()
{
	fRECT* p_rc = if_Panel_Scale_GetRect();

	_divi_menu.b_active   = true;
	_divi_menu.x          = p_rc->l + 152;
	_divi_menu.y          = p_rc->t      ;
	_divi_menu.divi_index = -1;
}

void if_Menu_Division_Hide()
{
	_divi_menu.b_active = false;
}

bool if_Menu_Division_IsPanel( int32_t x, int32_t y )
{
	if( !_divi_menu.b_active ) return false;

	if( x >= _divi_menu.x            &&
		x <  _divi_menu.x + _MENU_W  &&
		y >= _divi_menu.y            &&
		y <  _divi_menu.y + _MENU_H ) return true;

	return false;
}

int if_Menu_Division_GetIndex( int32_t x, int32_t y )
{
	if( !_divi_menu.b_active ) return 0;

	_divi_menu.divi_index = -1;
	if( x <  _divi_menu.x             ||
		x >= _divi_menu.x + _MENU_W   ||
		y <  _divi_menu.y + 20 ||
		y >= _divi_menu.y + _MENU_H  ) return -1;


	_divi_menu.divi_index = ( y - _divi_menu.y - 20 ) / _BUTTON_H;

	return _divi_menu.divi_index;
}

void if_Menu_Division_Put()
{
	fRECT rc_menu = {288, 72,344,252};
	fRECT rc      = {344,  0,400,  0};

	if( !_divi_menu.b_active ) return;

	g_dxdraw->tex_Put_View( _divi_menu.x, _divi_menu.y, &rc_menu, SURF_TABLES );

	if( _divi_menu.divi_index != -1 )
	{
		rc.t = _divi_menu.divi_index * _BUTTON_H + 92;
		rc.b = rc.t +                  _BUTTON_H     ;
		g_dxdraw->tex_Put_View( _divi_menu.x, _divi_menu.y + 20 + _divi_menu.divi_index * _BUTTON_H, &rc, SURF_TABLES );
	}
}
