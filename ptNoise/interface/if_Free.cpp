
#include <pxwDx09Draw.h>
extern pxwDx09Draw *g_dxdraw;


#include "../../Generic/if_Generic.h"

#include "SurfaceNo.h"
#include "Interface.h"

static fRECT _rcFree;

void if_Free_SetRect()
{
	fRECT rc_clip; g_dxdraw->GetViewClip( &rc_clip );

	float x = rc_clip.r - PANEL_SCALE_W - PANEL_LOGO_W;
	if( x < 0 ) x = 0;
	_rcFree    = rc_clip;
	_rcFree.b  = rc_clip.t + PANEL_SCALE_H;
	_rcFree.r  = x;
}

void if_Free_Put()
{
	fRECT rcFree = {160,  0,288, 48};
	if_gen_tile_h( &_rcFree, &rcFree, 1, 0, SURF_PARTS );
}
