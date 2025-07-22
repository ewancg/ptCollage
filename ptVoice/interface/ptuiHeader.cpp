#include <pxStdDef.h>

#include <pxMem.h>

#include <pxwDx09Draw.h>
extern pxwDx09Draw *g_dxdraw;

#include "../../Generic/if_Generic.h"

#include "../ptVoice.h"

#include "./ptuiHeader.h"

#include "./ptuiLayout.h"

void ptuiHeader::_release()
{
	_b_init = false;
	_base_release();
}

ptuiHeader::ptuiHeader(  )
{
	_b_init = false;
	_woice  = NULL ;
}

ptuiHeader::~ptuiHeader()
{
	_release();
}

bool ptuiHeader::init( WoiceUnit* woice )
{
	if( _b_init  ) return false;

	ptuiANCHOR anc = { 0 };
	anc.flags = ptuiANCHOR_x1_ofs|ptuiANCHOR_x2_ofs|ptuiANCHOR_y1_ofs|ptuiANCHOR_y2_h;
	anc.x1    = HEADER_X     ;
	anc.x2    = HEADER_x2_ofs;
	anc.y1    = HEADER_Y     ;
	anc.y2    = HEADER_H     ;

	if( !_base_init( &anc, WOICEUNIT_MODE_num ) ) goto term;

	_woice  = woice;
	_b_init = true ;
term:
	return _b_init;
}

void ptuiHeader::_put( const ptuiCursor *p_cur ) const
{
	fRECT   rcButton = {280,  0,296, 16};
	fRECT   rc;
	{
		fRECT rc_l = {512,256,520,304};
		fRECT rc_m = {520,256,736,304};
		fRECT rc_r = {736,256,744,304};

		rc = _rect; rc.l += 8; rc.r -= 8;
		if_gen_tile_h( &rc, &rc_m, 1, 0, SURF_PARTS );
		g_dxdraw->tex_Put_View( _rect.l  , _rect.t, &rc_l, SURF_PARTS );
		g_dxdraw->tex_Put_View( _rect.r-8, _rect.t, &rc_r, SURF_PARTS );
	}
}
