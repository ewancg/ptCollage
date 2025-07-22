
#include <pxwDx09Draw.h>
extern pxwDx09Draw *g_dxdraw;

#include "../../Generic/if_Generic.h"

#include "../ptVoice.h"

#include "./ptuiSwitch.h"

ptuiSwitch::ptuiSwitch( const PTUISWITCH* prm )
{
	_prm  = *prm ;
}

bool ptuiSwitch::is_touch( const fRECT* rc_prnt, const ptuiCursor* p_cur ) const
{
	int32_t l = rc_prnt->l + _prm.x;
	int32_t t = rc_prnt->t + _prm.y;
	int32_t r = rc_prnt->l + _prm.x + _prm.p_rc_src->w();
	int32_t b = rc_prnt->t + _prm.y + _prm.p_rc_src->h();

	return p_cur->is_rect( l, t, r, b );
}

void ptuiSwitch::put( const fRECT* rc_prnt, int32_t value ) const
{
	fRECT rc = *_prm.p_rc_src;
	float w  = rc.w();
	float h  = rc.h();
	float x  = rc_prnt->l + _prm.x;
	float y  = rc_prnt->t + _prm.y;

	rc.l += w * _prm.img_idx;
	rc.r += w * _prm.img_idx;

	rc.t += h*value; rc.b += h*value;

	g_dxdraw->tex_Put_Clip( x, y, &rc, SURF_PARTS, rc_prnt );
}

void ptuiSwitch::set_img_idx( int32_t img_idx )
{
	_prm.img_idx = img_idx;
}
