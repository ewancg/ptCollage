

#include <pxwDx09Draw.h>
extern pxwDx09Draw *g_dxdraw;

#include "../../Generic/if_Generic.h"

#include "SurfaceNo.h"
#include "Interface.h"

static fRECT _rcPanel;

void if_Panel_Logo_SetRect( const fRECT *rc_view )
{
	float x = rc_view->r - PANEL_RACK_W; if( x < 0 ) x = 0;
	_rcPanel.l = x          + PANEL_COMMENT_W + PANEL_SCALE_W;
	_rcPanel.t = rc_view->t + PANEL_RACK_H   ;
	_rcPanel.r = _rcPanel.l + PANEL_LOGO_W  ;
	_rcPanel.b = _rcPanel.t + PANEL_LOGO_H  ;
}

void if_Panel_Logo_Put()
{
	fRECT rcPanel = {  0, 48,112, 72};
	g_dxdraw->tex_Put_View( _rcPanel.l, _rcPanel.t, &rcPanel, SURF_TABLES );
}
