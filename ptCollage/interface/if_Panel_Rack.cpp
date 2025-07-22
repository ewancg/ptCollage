

#include <pxwDx09Draw.h>
extern pxwDx09Draw *g_dxdraw;

#include "../../Generic/KeyControl.h"
#include "../../Generic/if_Generic.h"

#include "SurfaceNo.h"
#include "Interface.h"
#include "if_Panel_Rack.h"
#include "if_Player.h"
#include "if_Copier.h"
#include "if_Projector.h"
#include "if_Effector.h"


#define _BUTTON_PLAYER_X  16
#define _BUTTON_PLAYER_Y   4
#define _BUTTON_PLAYER_W  88
#define _BUTTON_PLAYER_H  16

#define _BUTTON_PROJECTOR_X 112
#define _BUTTON_PROJECTOR_Y   4
#define _BUTTON_PROJECTOR_W  96
#define _BUTTON_PROJECTOR_H  16

#define _BUTTON_EFFECTOR_X 216
#define _BUTTON_EFFECTOR_Y   4
#define _BUTTON_EFFECTOR_W 104
#define _BUTTON_EFFECTOR_H  16

#define _BUTTON_COPIER_X 328
#define _BUTTON_COPIER_Y   4
#define _BUTTON_COPIER_W 120
#define _BUTTON_COPIER_H  16


static fRECT _rcPanel = {0};

void if_Panel_Rack_SetRect( const fRECT *rc_view )
{
	float x;

	x = rc_view->r - PANEL_RACK_W;
	if( x < 0 ) x = 0;

	_rcPanel   = *rc_view;
	_rcPanel.b = rc_view->t + PANEL_RACK_H;
	_rcPanel.l = x;

}

fRECT* if_Panel_Rack_GetRect()
{
	return &_rcPanel;
}

void if_Panel_Rack_Put()
{
	fRECT rc_rack = {  0, 0, 472, 24};

	fRECT rc_player    = { 16, 24, 104, 48};
	fRECT rc_projector = {112, 24, 208, 48};
	fRECT rc_effector  = {216, 24, 320, 48};
	fRECT rc_copier    = {328, 24, 448, 48};

	g_dxdraw->tex_Put_View( _rcPanel.l, _rcPanel.t, &rc_rack, SURF_TABLES );
	if( !if_Player_IsOpen(   ) ) g_dxdraw->tex_Put_View( _rcPanel.l + _BUTTON_PLAYER_X   , _rcPanel.t, &rc_player   , SURF_TABLES );
	if( !if_Projector_IsOpen() ) g_dxdraw->tex_Put_View( _rcPanel.l + _BUTTON_PROJECTOR_X, _rcPanel.t, &rc_projector, SURF_TABLES );
	if( !if_Effector_IsOpen( ) ) g_dxdraw->tex_Put_View( _rcPanel.l + _BUTTON_EFFECTOR_X , _rcPanel.t, &rc_effector , SURF_TABLES );
	if( !if_Copier_IsOpen(   ) ) g_dxdraw->tex_Put_View( _rcPanel.l + _BUTTON_COPIER_X   , _rcPanel.t, &rc_copier   , SURF_TABLES );
}

bool if_Panel_Rack_HitButton( float cur_x, float cur_y )
{
	if( cur_x > _rcPanel.l + _BUTTON_PLAYER_X                    &&
		cur_x < _rcPanel.l + _BUTTON_PLAYER_X + _BUTTON_PLAYER_W &&
		cur_y > _rcPanel.t + _BUTTON_PLAYER_Y                    &&
		cur_y < _rcPanel.t + _BUTTON_PLAYER_Y + _BUTTON_PLAYER_H )
	{
		if_Player_SetOpen();
		return true;
	}

	if( cur_x > _rcPanel.l + _BUTTON_PROJECTOR_X                    &&
		cur_x < _rcPanel.l + _BUTTON_PROJECTOR_X + _BUTTON_PROJECTOR_W &&
		cur_y > _rcPanel.t + _BUTTON_PROJECTOR_Y                    &&
		cur_y < _rcPanel.t + _BUTTON_PROJECTOR_Y + _BUTTON_PROJECTOR_H )
	{
		if_Projector_SetOpen();
		return true;
	}

	if( cur_x > _rcPanel.l + _BUTTON_EFFECTOR_X                    &&
		cur_x < _rcPanel.l + _BUTTON_EFFECTOR_X + _BUTTON_EFFECTOR_W &&
		cur_y > _rcPanel.t + _BUTTON_EFFECTOR_Y                    &&
		cur_y < _rcPanel.t + _BUTTON_EFFECTOR_Y + _BUTTON_EFFECTOR_H )
	{
		if_Effector_SetOpen();
		return true;
	}

	if( cur_x > _rcPanel.l + _BUTTON_COPIER_X                    &&
		cur_x < _rcPanel.l + _BUTTON_COPIER_X + _BUTTON_COPIER_W &&
		cur_y > _rcPanel.t + _BUTTON_COPIER_Y                    &&
		cur_y < _rcPanel.t + _BUTTON_COPIER_Y + _BUTTON_COPIER_H )
	{
		if_Copier_SetOpen();
		return true;
	}

	return false;
}
