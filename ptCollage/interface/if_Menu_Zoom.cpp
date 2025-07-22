

#include <pxwDx09Draw.h>
extern pxwDx09Draw *g_dxdraw;

#include "Interface.h"
#include "SurfaceNo.h"
#include "if_Panel_Scale.h"


#define _MENU_W   56
#define _MENU_H   84

#define _BUTTON_W 56
#define _BUTTON_H 16


typedef struct
{
	bool  b_active;
	float x, y;
	int   zoom_index;

}_MENUSTRUCT_ZOOM;

static fRECT            _rcMenu   ;
static _MENUSTRUCT_ZOOM _zoom_menu;

void if_Menu_Zoom_Initialize()
{
	_zoom_menu.b_active = false;
}

// 座標
void if_Menu_Zoom_Show()
{
	fRECT* p_rc = if_Panel_Scale_GetRect();

	_zoom_menu.b_active   = true;
	_zoom_menu.x          = p_rc->l + 40;
	_zoom_menu.y          = p_rc->t     ;
	_zoom_menu.zoom_index = -1;
}

void if_Menu_Zoom_Hide()
{
	_zoom_menu.b_active = false;
}

bool if_Menu_Zoom_IsPanel( float x, float y )
{
	if( !_zoom_menu.b_active ) return false;

	if( x >= _zoom_menu.x            &&
		x <  _zoom_menu.x + _MENU_W  &&
		y >= _zoom_menu.y            &&
		y <  _zoom_menu.y + _MENU_H ) return true;

	return false;
}

int32_t if_Menu_Zoom_GetIndex( float x, float y )
{
	if( !_zoom_menu.b_active ) return 0;

	_zoom_menu.zoom_index = -1;
	if( x <  _zoom_menu.x             ||
		x >= _zoom_menu.x + _MENU_W   ||
		y <  _zoom_menu.y + 20 ||
		y >= _zoom_menu.y + _MENU_H  ) return -1;


	_zoom_menu.zoom_index = ( y - _zoom_menu.y - 20 ) / _BUTTON_H;

	return _zoom_menu.zoom_index;
}

void if_Menu_Zoom_Put()
{
	fRECT rc_menu = {400, 72,456,156};
	fRECT rc      = {456,  0,512,  0};

	if( !_zoom_menu.b_active ) return;

	g_dxdraw->tex_Put_View( _zoom_menu.x, _zoom_menu.y, &rc_menu, SURF_TABLES );

	if( _zoom_menu.zoom_index != -1 )
	{
		rc.t = _zoom_menu.zoom_index * _BUTTON_H + 92;
		rc.b = rc.t +                  _BUTTON_H     ;
		g_dxdraw->tex_Put_View( _zoom_menu.x, _zoom_menu.y + 20 + _zoom_menu.zoom_index * _BUTTON_H, &rc, SURF_TABLES );
	}
}

