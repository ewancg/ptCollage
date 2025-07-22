
#include <pxStdDef.h>

#include <pxMem.h>

#include <pxwDx09Draw.h>
extern pxwDx09Draw *g_dxdraw;

#include <pxtonewinXA2.h>
extern pxtonewinXA2* g_strm_xa2;

#include "../CursorKeyCtrl.h"
extern CursorKeyCtrl* g_curkey;

#include "../WoiceUnit.h"
extern WoiceUnit*     g_vunit ;

#include "../../Generic/if_Generic.h"

#include "./ptuiWorkTemp.h"

#include "./ptuiLayout.h"

#define _BTN_PUSH_X      80
#define _BTN_PUSH_Y       8
#define _BUTTON_W        16
#define _BUTTON_H        16
#define _BUTTON_INTERVAL  8

void ptuiWorkTemp::_release()
{
	_b_init = false;

	if( _units )
	{
		for( int u = 0; u < _unit_num; u++ ) SAFE_DELETE( _units[ u ].temp_woice );
		pxMem_free( (void**)&_units );
		_unit_num = 0;
	}
	_base_release();
}

ptuiWorkTemp::ptuiWorkTemp()
{
	_b_init = false;
	_units  = NULL ;
	_last_u =    -1;
	_woice  = NULL ;
}

ptuiWorkTemp::~ptuiWorkTemp()
{
	_release();
}

void ptuiWorkTemp::last_unit_clear()
{
	_last_u = -1;
}

bool ptuiWorkTemp::init()
{
	if( _b_init ) return false;

	ptuiANCHOR anc = { 0 };
	anc.flags = ptuiANCHOR_x1_w|ptuiANCHOR_x2_ofs|ptuiANCHOR_y1_ofs|ptuiANCHOR_y2_h;
	anc.x1    = WORKTEMP_W     ;
	anc.x2    = WORKTEMP_x2_ofs;
	anc.y1    =               0;
	anc.y2    = WORKTEMP_H     ;

	if( !_base_init( &anc, ptvMAX_WORKTEMP ) ) goto term;

	_woice = g_vunit;

	if( !pxMem_zero_alloc( (void**)&_units, sizeof(WORKTEMPUNIT) * ptvMAX_WORKTEMP ) ) goto term;
	_unit_num = ptvMAX_WORKTEMP;

	for( int w = 0; w < ptvMAX_WORKTEMP; w++ )
	{
		_units[ w ].temp_woice = new WoiceUnit();
		if( !_units[ w ].temp_woice->init( g_strm_xa2 ) ) goto term;
	}

	_b_init = true;
term:
	if( !_b_init ) _release();

	return _b_init;
}

void ptuiWorkTemp::_put( const ptuiCursor *p_cur ) const
{
	fRECT   rc_panel = {  0,352,232,400};
	fRECT   rc_push  = {184,448,200,464};
	fRECT   rc_temp  = {184,464,200,480};
	fRECT   rc       = {0};

	g_dxdraw->tex_Put_View( _rect.l, _rect.t, &rc_panel, SURF_PARTS );

	float x = _rect.l + _BTN_PUSH_X;
	float y = _rect.t + _BTN_PUSH_Y;

	for( int i = 0; i < _unit_num; i++ )
	{
		// temp.
		rc = rc_temp;
		rc.l += _units[ i ].temp_ani_no * _BUTTON_W;
		rc.r  = rc.l +                    _BUTTON_W;

		if( _last_u == i )
		{
			rc.t +=        _BUTTON_H * 2;
			rc.b  = rc.t + _BUTTON_H;
		}
		else if( _units[ i ].b_temp_on )
		{
			rc.t +=        _BUTTON_H;
			rc.b  = rc.t + _BUTTON_H;
		}
		g_dxdraw->tex_Put_Clip( x, y, &rc, SURF_PARTS, &_rect );

		// push.
		rc = rc_push;
		rc.l += _units[ i ].push_ani_no * _BUTTON_W;
		rc.r  = rc.l +                    _BUTTON_W;
		g_dxdraw->tex_Put_Clip( x, y + _BUTTON_H, &rc, SURF_PARTS, &_rect );


		x += _BUTTON_W + _BUTTON_INTERVAL;
	}
}

bool ptuiWorkTemp::_search_button( const ptuiCursor* p_cur, int32_t* p_tgt_id ) const
{
	float x = _rect.l + _BTN_PUSH_X;
	float y = _rect.t + _BTN_PUSH_Y;

	for( int i = 0; i < _unit_num; i++ )
	{
		// temp.
		if( p_cur->is_rect( x, y, x + _BUTTON_W, y + _BUTTON_H ) ){ *p_tgt_id = i; return true; }

		// push.
		if( p_cur->is_rect( x, y + _BUTTON_H, x + _BUTTON_W, y + _BUTTON_H * 2 ) ){ *p_tgt_id = i + _unit_num; return true; }

		x += _BUTTON_W + _BUTTON_INTERVAL;
	}

	return false;
}

void ptuiWorkTemp::_anime_reset()
{
	for( int32_t i = 0; i < _unit_num; i++ )
	{
		_units[ i ].temp_ani_no = 0;
		_units[ i ].push_ani_no = 0;
	}
}

void ptuiWorkTemp::_anime_set  ( int32_t tgt_id, int32_t ani_no )
{
	if( tgt_id < _unit_num ) _units[ tgt_id % _unit_num ].temp_ani_no = ani_no;
	else                     _units[ tgt_id % _unit_num ].push_ani_no = ani_no;
}

bool ptuiWorkTemp::_cursor_free(  ptuiCursor* p_cur )
{
	int32_t idx = 0;

	_anime_reset();

	if( !p_cur->is_rect( &_rect )      ) return false;
	if( !_search_button( p_cur, &idx ) ) return false;

	// L click.
	if( p_cur->is_trigger_left()  ){ _anime_set( idx, 2 ); p_cur->set_action( this, ptuiCURACT_click_hold, idx ); }
	else                                  { _anime_set( idx, 1 ); }

	return true;
}

bool ptuiWorkTemp::_cursor_click_hold(  ptuiCursor* p_cur )
{
	int32_t idx = 0;

	if( !p_cur->get_target_index( &idx ) ) return false;

	// drag cancel.
	if( p_cur->is_click_left() && p_cur->is_click_right() )
	{
		p_cur->set_action_free();
		_anime_set( idx, 0 );
		return true;
	}

	// drag end.
	if( !p_cur->is_click_left() )
	{
		p_cur->set_action_free();

		_anime_set( idx, 0 );

		int32_t i = idx%_unit_num;

		if( idx < _unit_num )
		{
			if( !_units[ i ].temp_woice->copy_ptv_woice_to( _woice ) ) return false;
			_last_u = i;
			_woice->frame_alte_set( WOICEUNIT_ALTE_all, -1 );
		}
		else
		{
			if( !_woice->copy_ptv_woice_to( _units[ i ].temp_woice ) ) return false;
			_units[ i ].b_temp_on = true;
			_last_u = i;
		}
	}
	return true;
}
