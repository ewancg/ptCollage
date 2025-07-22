
#include <pxStdDef.h>

#include <pxwDx09Draw.h>
extern pxwDx09Draw*  g_dxdraw;

#include "../ptVoice.h"

#include "./ptuiLayout.h"

#include "./ptuiReleaseTime.h"

void ptuiReleaseTime::_release()
{
	_b_init = false;
	_base_release();
	SAFE_DELETE( _knob );
}

ptuiReleaseTime::ptuiReleaseTime()
{
	_b_init       = false;
	_start_volume =     0;
	_woice        = NULL ;
	_knob         = NULL ;
}

ptuiReleaseTime::~ptuiReleaseTime()
{
	_release();
}

bool ptuiReleaseTime::init( WoiceUnit* woice )
{
	if( _b_init ) return false;

	ptuiANCHOR anc = { 0 };
	anc.flags = ptuiANCHOR_x1_ofs|ptuiANCHOR_x2_w|ptuiANCHOR_y1_ofs|ptuiANCHOR_y2_h;
	anc.x1    = RELEASETIME_X;
	anc.x2    = RELEASETIME_W;
	anc.y1    = RELEASETIME_Y;
	anc.y2    = RELEASETIME_H;

	if( !_base_init( &anc, 1 ) ) goto term;

	{
		PTUIKNOB prm;
		prm.b_vertical  = false;
		prm.number_x    =  80;
		prm.number_y    =   8;
		prm.zero_x      = 120;
		prm.zero_y      =  12;
		prm.volume_rate =  10;
		_knob = new ptuiKnob( &prm );
	}

	_woice  = woice;
	_b_init = true ;
term:
	if( !_b_init ) _release();
	return _b_init;
}

void ptuiReleaseTime::_put( const ptuiCursor* p_cur ) const
{
	{ fRECT rc = {  0,264,232,288}; g_dxdraw->tex_Put_View( _rect.l, _rect.t, &rc, SURF_PARTS ); }

	pxtnVOICEUNIT* p_vc = _woice->get_voice(); if( !p_vc ) return;
	int32_t        e    = p_vc->envelope.head_num + p_vc->envelope.body_num;
	int32_t        volume = ( p_vc->envelope.points[ e ].x );

	_knob->put( &_rect, volume, _ani_nos[ 0 ] );

}

bool ptuiReleaseTime::_search_button( const ptuiCursor* p_cur, int32_t* p_tgt_id ) const
{
	const pxtnVOICEUNIT* p_vc   = _woice->get_voice(); if( !p_vc ) return false;
	int32_t        e      = p_vc->envelope.head_num + p_vc->envelope.body_num;
	int32_t        volume = ( p_vc->envelope.points[ e ].x );// / _VOLUME_RATE;

	if( !_knob->is_touch( &_rect, volume, p_cur ) ) return false;
	if( p_tgt_id ) *p_tgt_id = 0;
	return true;
}

bool ptuiReleaseTime::_get_volume_int( int32_t* p_volume ) const
{
	if( !p_volume ) return false;
	const pxtnVOICEUNIT* p_vc = _woice->get_voice(); if( !p_vc ) return false;
	int32_t        e    = p_vc->envelope.head_num + p_vc->envelope.body_num;

	*p_volume = p_vc->envelope.points[ e ].x;
	return true;
}

bool ptuiReleaseTime::_set_volume_int( int32_t    volume )
{
	if( !_b_init ) return false;
	if( volume <     1 ) volume =    1;
	if( volume >  1000 ) volume = 1000;

	pxtnVOICEUNIT* p_vc = _woice->get_voice(); if( !p_vc ) return false;
	int32_t        e    = p_vc->envelope.head_num + p_vc->envelope.body_num;
	p_vc->envelope.points[ e ].x = volume;

	_woice->frame_alte_set( WOICEUNIT_ALTE_enve_voice, -1 );
	return true;
}


bool ptuiReleaseTime::_set_volume_default()
{
	return _set_volume_int( 1 );
}

bool ptuiReleaseTime::_cursor_free( ptuiCursor* p_cur )
{
	int32_t idx = 0;

	if( !p_cur->is_rect( &_rect )      ) return false;
	if( !_search_button( p_cur, &idx ) ) return false;

	if( p_cur->is_trigger_left() )
	{
		_get_volume_int( &_start_volume );
		p_cur->set_action( this, ptuiCURACT_drag_unit, idx );
		_unit_anime_set( idx, 2 );
	}
	else if( p_cur->is_trigger_right() )
	{
		p_cur->set_action( this, ptuiCURACT_click_hold, idx );
		_set_volume_default();
		_unit_anime_set( idx, 2 );
	}
	else
	{
		_unit_anime_set( idx, 1 );
	}

	return true;
}

bool ptuiReleaseTime::_cursor_drag_unit( ptuiCursor* p_cur )
{
	int32_t idx = 0;
	p_cur->get_target_index( &idx );

	if( p_cur->is_click_left() && p_cur->is_click_right() )
	{
		_set_volume_int( _start_volume );
		_unit_anime_set( idx, 0 );
		p_cur->set_action_free();
		return true;
	}
	else
	{
		int32_t now_x  ;
		int32_t start_x;
		{ int32_t fx; p_cur->get_pos      ( &fx, NULL ); _knob->make_volume( &_rect, &now_x  , fx ); }// _pos_make( &now_x  , fx ); }
		{ int32_t fx; p_cur->get_pos_start( &fx, NULL ); _knob->make_volume( &_rect, &start_x, fx ); }
		_set_volume_int( _start_volume + ( now_x - start_x ) );

		if( !p_cur->is_click_left() )
		{
			_unit_anime_set( idx, 0 );
			p_cur->set_action_free();
		}
	}
	return true;
}

bool ptuiReleaseTime::_cursor_click_hold( ptuiCursor* p_cur )
{
	int32_t idx = 0;
	p_cur->get_target_index( &idx );

	if( p_cur->is_click_left() && p_cur->is_click_right() )
	{
		_set_volume_int( _start_volume );
		_unit_anime_set( idx, 0 );
		p_cur->set_action_free();
		return true;
	}

	if( !p_cur->is_click_left() )
	{
		_unit_anime_set( idx, 0 );
		p_cur->set_action_free();
	}
	return true;
}
