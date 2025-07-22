

#include <pxwDx09Draw.h>
extern pxwDx09Draw *g_dxdraw;

#include "../../Generic/if_gen_Scroll.h"
#include "../../Generic/if_Generic.h"


#include "SurfaceNo.h"
#include "Interface.h"

static fRECT _rcField = {0};


void if_WoiceDummy_SetRect( const fRECT *rc_view )
{
	_rcField.l = rc_view->l + NAMETRAY_WIDTH  ;
	_rcField.r = rc_view->r - SCROLLBUTTONSIZE;
	_rcField.t = rc_view->t + HEADER_H        ;
	_rcField.b = rc_view->t + HEADER_H + TOOLPANEL_HEIGHT;

}


fRECT*if_WoiceDummy_GetRect()
{
	return &_rcField;
}

// ユニットネームを表示
void if_WoiceDummy_Put()
{
	fRECT rcTile;
	static const fRECT rc[] =
	{
		{176, 88,184,136},
		{184, 88,264,136},
		{264, 88,272,136},
	};
	rcTile    = _rcField;
	rcTile.l += 8;
	rcTile.r -= 8;
	g_dxdraw->tex_Put_View( _rcField.l    , _rcField.t, &rc[ 0 ],       SURF_TABLES );
	if_gen_tile_h         ( &rcTile       ,             &rc[ 1 ], 1, 0, SURF_TABLES );
	g_dxdraw->tex_Put_View( _rcField.r - 8, _rcField.t, &rc[ 2 ],       SURF_TABLES );
}

