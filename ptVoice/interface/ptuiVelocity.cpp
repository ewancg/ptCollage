
#include <pxwDx09Draw.h>
extern pxwDx09Draw *g_dxdraw;

#include "../ptvVelocity.h"

#include "./ptuiLayout.h"

#include "./ptuiVelocity.h"

void ptuiVelocity::_release()
{
	_b_init = false;
	SAFE_DELETE( _knob );
	_base_release();
}

ptuiVelocity::ptuiVelocity()
{
	_b_init       = false;
	_start_volume =     0;
	_knob         = NULL ;
}

ptuiVelocity::~ptuiVelocity()
{
	_release();
}

bool ptuiVelocity::init()
{
	if( _b_init ) return false;

	ptuiANCHOR anc = { 0 };
	anc.flags = ptuiANCHOR_x1_w|ptuiANCHOR_x2_ofs|ptuiANCHOR_y1_h|ptuiANCHOR_y2_ofs;
	anc.x1    = VELOCITYVOLUME_W;
	anc.x2    = VELOCITYVOLUME_x2_ofs;
	anc.y1    = VELOCITYVOLUME_H;
	anc.y2    = VELOCITYVOLUME_y2_ofs;

	if( !_base_init( &anc, 1 ) ) goto term;


	{
		PTUIKNOB prm;
		prm.b_vertical  = false;
		prm.number_x    =    64;
		prm.number_y    =     8;
		prm.zero_x      =    16;
		prm.zero_y      =    32;
		prm.volume_rate =     2;
		_knob = new ptuiKnob( &prm );
	}

	_b_init = true;
term:
	if( !_b_init ) _release();
	return _b_init;
}

void ptuiVelocity::_put( const ptuiCursor* p_cur ) const
{
	{ fRECT rc  = {256,352,352,400}; g_dxdraw->tex_Put_Clip( _rect.l, _rect.t, &rc, SURF_PARTS, &_rect ); }

	_knob->put( &_rect, ptvVelocity_Get(), _ani_nos[ 0 ] );
}

bool ptuiVelocity::_search_button    ( const ptuiCursor* p_cur, int32_t* p_tgt_id ) const
{
	if( !_knob->is_touch( &_rect, ptvVelocity_Get(), p_cur ) ) return false;
	if( p_tgt_id ) *p_tgt_id = 0;
	return true;
}

bool ptuiVelocity::_get_volume_int   ( int32_t* p_volume ) const
{
	*p_volume = ptvVelocity_Get();
	return true;
}

bool ptuiVelocity::_set_volume_int   ( int32_t    volume )
{
	if( volume <    0 ) volume =    0;
	if( volume >  128 ) volume =  128;
	ptvVelocity_Set( volume );
	return true;
}

bool ptuiVelocity::_set_volume_default()
{
	ptvVelocity_Set( 104 );
	return true;
}

bool ptuiVelocity::_cursor_free( ptuiCursor* p_cur )
{
	int32_t idx = 0;

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

bool ptuiVelocity::_cursor_drag_unit( ptuiCursor* p_cur )
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
		{ int32_t fx; p_cur->get_pos      ( &fx, NULL ); _knob->make_volume( &_rect, &now_x  , fx ); }
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

bool ptuiVelocity::_cursor_click_hold( ptuiCursor* p_cur )
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

