

#include <pxwDx09Draw.h>
extern pxwDx09Draw *g_dxdraw;

#include "../../Generic/if_Generic.h"

#include "SurfaceNo.h"
#include "Interface.h"

static fRECT _rcFree = {0};

void if_Free_SetRect( const fRECT *rc_view )
{
	float x = rc_view->r - HEADER_W; if( x < 0 ) x = 0;
	_rcFree   = *rc_view;
	_rcFree.b = rc_view->t + HEADER_H;
	_rcFree.r = x;
}

void if_Free_Put()
{
	fRECT rcFree = {240,144,368,192};
	if_gen_tile_h( &_rcFree, &rcFree, 1, 0, SURF_FIELDS );
}
