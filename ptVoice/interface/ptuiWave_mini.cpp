
#include <pxMem.h>

#include <pxwDx09Draw.h>
extern pxwDx09Draw*   g_dxdraw;

#include <pxtnPulse_Oscillator.h>

#include "./Interface.h"
#include "./ptuiLayout.h"

#include "./ptuiWave_mini.h"

void ptuiWave_mini::_release()
{
	_b_init = false;
	_map_release ();
	_base_release();
}

ptuiWave_mini::ptuiWave_mini()
{
	_b_init   = false;
	_woice    = NULL ;
	_unit_idx =     0;
}

ptuiWave_mini::~ptuiWave_mini()
{
	_release ();
}

bool ptuiWave_mini::init( WoiceUnit* woice, int32_t unit_idx )
{
	if( _b_init ) return false;

	uint32_t* p_posi        = NULL      ;
	uint32_t* p_nega        = NULL      ;

	uint32_t posi_top_base  = 0xff6ecc22;
	uint32_t posi_btm_base  = 0xff5b9600;
	uint32_t nega_top_base  = 0xff436600;
	uint32_t nega_btm_base  = 0xff365000;

	int32_t  w              = SCREEN_WAVEMINI_W;
	int32_t  h              = SCREEN_WAVEMINI_H;
	int32_t  half_y         = h / 2;

	ptuiANCHOR anc = { 0 };
	anc.flags = ptuiANCHOR_x1_ofs|ptuiANCHOR_x2_w|ptuiANCHOR_y1_ofs|ptuiANCHOR_y2_h;
	anc.x1    = RACK_X + 16;
	anc.x2    = w;
	anc.y1    = RACK_Y + RACK_H * unit_idx + 32;
	anc.y2    = h;

	if( !_base_init( &anc, 0 ) ) goto term;

	if( !_map_init ( w, h, unit_idx ? SURF_WAVE_mini_1 : SURF_WAVE_mini_0 ) ) goto term;

	p_posi = _p_map_posi;
	p_nega = _p_map_nega;

	for( int y = 0; y < h; y++ )
	{
		for( int x = 0; x < w; x++ )
		{
			if( y < half_y ){ *p_posi = posi_top_base ; *p_nega = nega_top_base; }
			else            { *p_posi = posi_btm_base ; *p_nega = nega_btm_base; }
			p_posi++;
			p_nega++;
		}
	}
	_unit_idx     = unit_idx;
	_woice        = woice;
	_b_map_redraw = true ;
	_b_init       = true ;
term:
	if( !_b_init ) _release();

	return _b_init;
}

bool ptuiWave_mini::_try_update()
{
	if( !_b_init ) return false;

	int32_t w           = SCREEN_WAVEMINI_W;
	int32_t h           = SCREEN_WAVEMINI_H;

	double  work_double =                 0;
	int32_t work_long   =                 0;

	pxtnPulse_Oscillator osci( NULL, NULL, NULL, NULL );

	pxtnVOICEUNIT* p_vc = _woice->get_voice( _unit_idx );

	if( !_b_map_redraw ) return false;

	osci.ReadyGetSample( p_vc->wave.points, p_vc->wave.num, p_vc->volume, w, p_vc->wave.reso );

	switch( p_vc->type )
	{
	case pxtnVOICE_Overtone:

		for( int32_t x = 0; x < w; x++ )
		{
			work_double = osci.GetOneSample_Overtone( x );
			work_long   = (int32_t)( work_double * h / 2 );
			int32_t yy = (h/2) - work_long;
			if( yy <     0 ) yy =     0;
			if( yy > (h-1) ) yy = (h-1);
			for( int y =  0; y < yy; y++ ) *( _p_map_view + x + y *w ) = *( _p_map_nega + x + y *w );
			for( int y = yy; y < h ; y++ ) *( _p_map_view + x + y *w ) = *( _p_map_posi + x + y *w );
		}
		break;

	case pxtnVOICE_Coodinate:

		for( int32_t x = 0; x < w; x++ )
		{
			work_double = osci.GetOneSample_Coodinate( x%w );
			work_long   = (int32_t)( work_double * h / 2 * 2 );

			int32_t yy = (h/2) - work_long;
			if( yy <     0 ) yy =     0;
			if( yy > (h-1) ) yy = (h-1);
			for( int y =  0; y < yy; y++ ) *( _p_map_view + x + y *w ) = *( _p_map_nega + x + y *w );
			for( int y = yy; y < h ; y++ ) *( _p_map_view + x + y *w ) = *( _p_map_posi + x + y *w );
		}
		break;
	}
	g_dxdraw->tex_blt( _surf_screen, _p_map_view, w, h );

	_b_map_redraw = false;

	return true;
}

void ptuiWave_mini::_put( const ptuiCursor* p_cur ) const
{
	fRECT rc = { 0, 0, SCREEN_WAVEMINI_W, SCREEN_WAVEMINI_H};
	g_dxdraw->tex_Put_View( _rect.l + 16, _rect.t + 24, &rc, _surf_screen );
}
