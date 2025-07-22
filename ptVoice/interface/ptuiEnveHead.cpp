
#include <pxMem.h>

#include <pxwDx09Draw.h>
extern pxwDx09Draw *g_dxdraw;

#include "../ptVoice.h"

#include "./ptuiLayout.h"

#include "./ptuiEnveHead.h"


void ptuiEnveHead::_release()
{
	_b_init = false;

	if( _btns )
	{
		for( int i = 0; i < _BTNID_num; i++ ) SAFE_DELETE( _btns[ i ] );
		pxMem_free( (void**)&_btns );
	}

	_base_release();
}

ptuiEnveHead::ptuiEnveHead()
{
	_b_init = false;
	_woice  = NULL ;
	_btns   = NULL ;
}

ptuiEnveHead::~ptuiEnveHead()
{
	_release();
}

static const fRECT _rc_zooms = {280,208,320,224};
static const fRECT _rc_close = {136, 48,216, 64};

bool ptuiEnveHead::init( WoiceUnit* woice )
{
	if( _b_init ) return false;

	ptuiANCHOR anc = { 0 };
	anc.flags = ptuiANCHOR_x1_ofs|ptuiANCHOR_x2_w|ptuiANCHOR_y1_ofs|ptuiANCHOR_y2_h;
	anc.x1    = ENVEHEAD_X;
	anc.x2    = ENVEHEAD_W;
	anc.y1    = ENVEHEAD_Y;
	anc.y2    = ENVEHEAD_H;

	if( !_base_init( &anc, _BTNID_num ) ) goto term;

	if( !pxMem_zero_alloc( (void**)&_btns, sizeof(ptuiSwitch*) * _BTNID_num ) ) goto term;

	{
		PTUISWITCH prm = {0};
		prm.x        =         16;
		prm.y        =          4;
		prm.p_rc_src = &_rc_zooms;

		for( int i = 0; i < 3; i++ )
		{
			prm.img_idx = i;
			_btns[ i ] = new ptuiSwitch( &prm );
			prm.x += 48;
		}
	}

	{
		PTUISWITCH prm = {0};
		prm.x        =        240;
		prm.y        =          0;
		prm.p_rc_src = &_rc_close;
		_btns[ _BTNID_close ] = new ptuiSwitch( &prm );
	}

	_woice  = woice;
	_b_init = true ;
term:
	if( !_b_init ) _release();

	return _b_init;
}

void ptuiEnveHead::_put( const ptuiCursor *p_cur ) const
{
	if( !_b_init ) return;
	const pxtnVOICEUNIT* p_vc = _woice->get_voice();

	float zoom = _woice->zoom_get();

	if     ( zoom == 0.1f )
	{
		_btns[ _BTNID_01 ]->put( &_rect, 2 );
		_btns[ _BTNID_05 ]->put( &_rect, _ani_nos[ _BTNID_05 ] );
		_btns[ _BTNID_10 ]->put( &_rect, _ani_nos[ _BTNID_10 ] );
	}
	else if( zoom == 0.5f )
	{
		_btns[ _BTNID_01 ]->put( &_rect, _ani_nos[ _BTNID_01 ] );
		_btns[ _BTNID_05 ]->put( &_rect, 2 );
		_btns[ _BTNID_10 ]->put( &_rect, _ani_nos[ _BTNID_10 ] );
	}
	else if( zoom == 1.0f )
	{
		_btns[ _BTNID_01 ]->put( &_rect, _ani_nos[ _BTNID_01 ] );
		_btns[ _BTNID_05 ]->put( &_rect, _ani_nos[ _BTNID_05 ] );
		_btns[ _BTNID_10 ]->put( &_rect, 2 );
	}

	_btns[ _BTNID_close ]->put( &_rect, _ani_nos[ _BTNID_close ] );
}

bool ptuiEnveHead::_search_a_button( const ptuiCursor* p_cur, int32_t* p_idx )
{
	for( int i = 0; i < _BTNID_num; i++ )
	{
		if( _btns[ i ]->is_touch( &_rect, p_cur ) )
		{
			if( p_idx ) *p_idx = i;
			return true;
		}
	}
	return false;
}

bool ptuiEnveHead::_cursor_free( ptuiCursor* p_cur )
{
	if( !_b_init ) return false;

	int32_t idx = 0;

	if( !p_cur->is_rect( &_rect )      ) return false;

	if( _search_a_button( p_cur, &idx ) )
	{
		if( p_cur->is_trigger_left()  )
		{
			p_cur->set_action( this, ptuiCURACT_click_hold, idx );
			_unit_anime_set( idx, 2 );
		}
		else
		{
			_unit_anime_set( idx, 1 );
		}
		return true;
	}
	return false;
}

bool ptuiEnveHead::_cursor_click_hold( ptuiCursor* p_cur )
{
	int32_t idx = 0;

	float old_zoom = _woice->zoom_get();

	if( !p_cur->get_target_index( &idx ) ) return false;

	if( p_cur->is_click_left() && p_cur->is_click_right() )
	{
		p_cur->set_action_free();
		_unit_anime_set( idx, 0 );
	}
	else if( !p_cur->is_click_left() )
	{
		p_cur->set_action_free();

		switch( idx )
		{
		case _BTNID_01   : _woice->zoom_set( 0.1f ); break;
		case _BTNID_05   : _woice->zoom_set( 0.5f ); break;
		case _BTNID_10   : _woice->zoom_set( 1.0f ); break;
		case _BTNID_close: _woice->mode_set( WOICEUNIT_MODE_rack ); break;
		default: return false;
		}
		_unit_anime_set( idx, 0 );
	}
	else
	{
		_unit_anime_set( idx, 2 );
	}
	return true;
}
