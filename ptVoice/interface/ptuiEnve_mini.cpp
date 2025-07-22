
#include <pxMem.h>

#include <pxwDx09Draw.h>
extern pxwDx09Draw*   g_dxdraw;

#include "./Interface.h"
#include "./ptuiLayout.h"

#include "./ptuiEnve_mini.h"

#define _MAP_RATE_Y 2.0f

void ptuiEnve_mini::_release()
{
	_b_init = false;
	_map_release ();
	_base_release();
}

ptuiEnve_mini:: ptuiEnve_mini()
{
	_b_init   = false;
	_woice    = NULL ;
	_unit_idx =     0;
}

ptuiEnve_mini::~ptuiEnve_mini()
{
	_release();
}

bool ptuiEnve_mini::init( WoiceUnit* woice, int32_t unit_idx )
{
	if( _b_init ) return false;

	uint32_t* p_posi = NULL;
	uint32_t* p_nega = NULL;

	uint32_t posi_top_base  = 0xff226ecc;
	uint32_t nega_base      = 0xff004366;

	int32_t w = SCREEN_ENVEMINI_W;
	int32_t h = SCREEN_ENVEMINI_H;

	ptuiANCHOR anc = { 0 };
	anc.flags = ptuiANCHOR_x1_ofs|ptuiANCHOR_x2_w|ptuiANCHOR_y1_ofs|ptuiANCHOR_y2_h;
	anc.x1    = RACK_X + 120;
	anc.x2    = w;
	anc.y1    = RACK_Y + RACK_H * unit_idx + 32;
	anc.y2    = h;

	if( !_base_init( &anc, ptvMAX_ENVELOPEPOINT ) ) goto term;

	if( !_map_init ( w, h, unit_idx ? SURF_ENVE_mini_1 : SURF_ENVE_mini_0 ) ) goto term;

	p_posi = _p_map_posi;
	p_nega = _p_map_nega;

	for( int y = 0; y < h; y++ )
	{
		for( int x = 0; x < w; x++ )
		{
			*p_posi = posi_top_base ;
			*p_nega = nega_base     ;
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


bool ptuiEnve_mini::_try_update()
{
	int32_t e, e_num;
	int32_t y_now;
	int32_t x_now;
	int32_t zoom_stride;

	int32_t w = SCREEN_ENVEMINI_W;
	int32_t h = SCREEN_ENVEMINI_H;

	const pxtnVOICEUNIT* p_vc   = _woice->get_voice();
	const pxtnPOINT*     points = p_vc->envelope.points;

	zoom_stride = 20;

	for( e_num = 1; e_num < ptvMAX_ENVELOPEPOINT; e_num++ ){ if( !points[ e_num ].x && !points[ e_num ].y ) break; }

	// redraw..
	if( !_b_map_redraw ) return true;

	uint32_t *p_src = _p_map_view;
	int32_t  offset = 0;
	int32_t  src_x;

	e     = 0;
	x_now = offset * zoom_stride;
	y_now = 0;

	for( int x = 0; x < w; x++ )
	{
		src_x = ( offset + x );

		while( e < e_num && points[ e ].x - x_now <= 0 ){ x_now -= points[ e ].x; y_now = points[ e ].y; e++; }

		if(     !e         ) y_now =                       points[ e ].y                       * x_now / points[ e ].x;
		else if( e < e_num ) y_now = points[ e - 1 ].y + ( points[ e ].y - points[ e - 1 ].y ) * x_now / points[ e ].x;

		int32_t t = h - (int32_t)( (float)y_now / _MAP_RATE_Y );
		int32_t b = h;
		if( t < 0 ) t = 0;
		uint32_t *p = _p_map_view;
		for( int32_t y = 0; y < t; y++ ) *(_p_map_view + x + y * w ) =  *(_p_map_nega + src_x + y * w );
		for( int32_t y = t; y < b; y++ ) *(_p_map_view + x + y * w ) =  *(_p_map_posi + src_x + y * w );
		x_now += zoom_stride;
	}

	g_dxdraw->tex_blt( _surf_screen, _p_map_view, w, h );

	_b_map_redraw = false;

	return true;
}


void ptuiEnve_mini::_put( const ptuiCursor* p_cur ) const
{
	int32_t w = SCREEN_ENVEMINI_W;
	int32_t h = SCREEN_ENVEMINI_H;

	{ fRECT rc = { 0, 0, w, h}; g_dxdraw->tex_Put_View( _rect.l + 16, _rect.t + 24, &rc, _surf_screen ); }
}

