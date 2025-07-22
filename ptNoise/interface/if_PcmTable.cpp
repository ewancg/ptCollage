
#include <math.h>


#include <pxwDx09Draw.h>
extern pxwDx09Draw *g_dxdraw;

#include "../../Generic/KeyControl.h"
#include "../../Generic/if_Generic.h"
#include "../../Generic/if_gen_Scroll.h"

#include "../PcmTable.h"

#include "SurfaceNo.h"
#include "Interface.h"


static fRECT         _rc_field = {0};

extern if_gen_Scroll g_ScrlPCM_H;

static uint32_t _back_color   = 0xff606060;
static uint32_t _line_color   = 0xffffa0a0;
static uint32_t _scope_color  = 0xff807060;
static uint32_t _volume_color = 0xffa0a0a0;

static int _zoom = 10;

typedef struct
{
	int32_t start;
	int32_t end  ;
}
_PCMSCOPEPOSITION;

static _PCMSCOPEPOSITION _scope = {0};


void if_PcmTable_Initialize()
{
	pxtnPulse_PCM *p_pcm = PcmTable_Woice_GetPcmPointer();

	g_ScrlPCM_H.SetSize( p_pcm->get_smp_body() );
	g_ScrlPCM_H.SetMove( 100, 100 );

	_scope.start  = 0;
	_scope.end    = 0;
}

void if_PcmTable_SetParameter( int32_t zoom )
{
	int32_t offset   = g_ScrlPCM_H.GetOffset();
	int32_t old_zoom = _zoom;

	_zoom = zoom;

	pxtnPulse_PCM *p_pcm = PcmTable_Woice_GetPcmPointer();

	g_ScrlPCM_H.SetOffset( offset * old_zoom / _zoom );

	g_ScrlPCM_H.SetSize( p_pcm->get_smp_body() / _zoom );
}

void if_PcmTable_SetRect( const fRECT *rc_view )
{
	_rc_field.l = rc_view->l                  ;
	_rc_field.r = rc_view->r                  ;
	_rc_field.t = rc_view->t + PCMTABLE_Y     ;
	_rc_field.b = _rc_field.t + PCMTABLE_H * 2;

	pxtnPulse_PCM *p_pcm = PcmTable_Woice_GetPcmPointer();

	g_ScrlPCM_H.SetRect( &_rc_field );
	g_ScrlPCM_H.SetSize( p_pcm->get_smp_body() / _zoom);
}

const fRECT *if_PcmTable_GetRect()
{
	return &_rc_field;
}

static void _PutSample( const unsigned char* p, int32_t smp_num, int32_t ch, float y )
{
	fRECT rc;

	rc.l = _rc_field.l    ;
	rc.r = _rc_field.l + 1;

	for( int32_t i = 0; i < smp_num; i+= _zoom )
	{
		for( int32_t c = 0; c < ch; c++ )
		{
			rc.t = y + PCMTABLE_H * ( c + 1 ) - *( p + c ) / 2;
			rc.b = y + PCMTABLE_H * ( c + 1 );
			g_dxdraw->FillRect_view( &rc, _volume_color );
		}
		p += ch * _zoom;
		rc.l++;
		rc.r++;
	}
}

static void _PutSample( const char* p, int32_t smp_num, int32_t ch, float y )
{
	fRECT rc;

	rc.l = _rc_field.l    ;
	rc.r = _rc_field.l + 1;

	for( int32_t i = 0; i < smp_num; i+= _zoom )
	{
		for( int32_t c = 0; c < ch; c++ )
		{
			rc.t = y + PCMTABLE_H * ( c + 1 ) - PCMTABLE_H / 2 - *( p + c * 2 ) / 2;
			rc.b = y + PCMTABLE_H * ( c + 1 );
			g_dxdraw->FillRect_view( &rc, _volume_color );
		}
		p += 2 * ch * _zoom;
		rc.l++;
		rc.r++;
	}
}

void if_PcmTable_Put_CursorPosition( float cur_x, float cur_y )
{
	pxtnPulse_PCM *p_pcm = PcmTable_Woice_GetPcmPointer();

	if( p_pcm && p_pcm->get_sps() )
	{
		int32_t pos = (int32_t)( (double)( g_ScrlPCM_H.GetOffset() + cur_x ) * ( 44100.0 / p_pcm->get_sps() ) );
		if_gen_num6_clip( _rc_field.l + 8, _rc_field.t + 8, pos * _zoom, 6, &_rc_field );
	}
}

bool if_PcmTable_IsHitPCM( float cur_x, float cur_y )
{
	if( cur_x >= _rc_field.l &&
		cur_x <  _rc_field.r &&
		cur_y >= _rc_field.t &&
		cur_y <  _rc_field.t + PCMTABLE_H * 2 )
	{
		return true;
	}
	return false;
}

void if_PcmTable_Scope_SetStart( float cur_x )
{
	pxtnPulse_PCM *p_pcm = PcmTable_Woice_GetPcmPointer();

	_scope.start = (int32_t)( cur_x - _rc_field.l + g_ScrlPCM_H.GetOffset() ) * _zoom;
	if( _scope.start <                     0 ) _scope.start = 0;
	if( _scope.start > p_pcm->get_smp_body() ) _scope.start = p_pcm->get_smp_body();
}

void if_PcmTable_Scope_SetEnd(   float cur_x )
{
	pxtnPulse_PCM *p_pcm = PcmTable_Woice_GetPcmPointer();

	_scope.end = (int32_t)( cur_x - _rc_field.l + g_ScrlPCM_H.GetOffset() ) * _zoom;
	if( _scope.end <                     0 ) _scope.end = 0;
	if( _scope.end > p_pcm->get_smp_body() ) _scope.end = p_pcm->get_smp_body();

}

bool if_PcmTable_Scope_GetScope( int32_t* p_start, int32_t* p_end )
{
	int32_t start;
	int32_t end  ;

	if( _scope.start <= _scope.end )
	{
		start = _scope.start;
		end   = _scope.end  ;
	}
	else
	{
		start = _scope.end  ;
		end   = _scope.start;
	}

	if( end <= start ) return false;
	if( p_start ) *p_start = start;
	if( p_end   ) *p_end   = end  ;
	return true;
}

bool if_PcmTable_Scope_IsHitPCM( float cur_x, float cur_y )
{
	int32_t start;
	int32_t end  ;

	if( !if_PcmTable_Scope_GetScope( &start, &end ) ) return false;

	int32_t offset = g_ScrlPCM_H.GetOffset();

	if( cur_x >= _rc_field.l + start / _zoom - offset &&
		cur_x <  _rc_field.l + end   / _zoom - offset &&
		cur_y >= _rc_field.t  &&
		cur_y <  _rc_field.t + PCMTABLE_H * 2 )
	{
		return true;
	}
	return false;
}

void if_PcmTable_Put( const fRECT *rc_view )
{
	fRECT rc;

	int32_t  start;
	int32_t  end  ;

	g_dxdraw->FillRect_view( &_rc_field, _back_color );

	if( if_PcmTable_Scope_GetScope( &start, &end ) )
	{
		rc.t = _rc_field.t;
		rc.b = _rc_field.b;
		rc.l = start / _zoom - g_ScrlPCM_H.GetOffset() + _rc_field.l;
		rc.r = end   / _zoom - g_ScrlPCM_H.GetOffset() + _rc_field.l;

		if( rc.l < _rc_field.l ) rc.l = _rc_field.l;
		if( rc.r > _rc_field.r ) rc.r = _rc_field.r;

		g_dxdraw->FillRect_view( &rc, _scope_color );
	}


	start = g_ScrlPCM_H.GetOffset();
	end   = g_ScrlPCM_H.GetOffset() + (int32_t)_rc_field.w();

	start  *= _zoom;
	end    *= _zoom;

	pxtnPulse_PCM *p_pcm = PcmTable_Woice_GetPcmPointer();

	int32_t ch  = p_pcm->get_ch ();
	int32_t bps = p_pcm->get_bps();
	int32_t sps = p_pcm->get_sps();

	if( p_pcm && p_pcm->get_p_buf() )
	{
		unsigned char *p  = (unsigned char*)p_pcm->get_p_buf();
		int32_t           smp_body = p_pcm->get_smp_body();

		if( end > smp_body ) end = smp_body;
		if( bps == 8 ) _PutSample( (unsigned char*)&p[ start *     ch     ], end - start, ch, _rc_field.t );
		else           _PutSample( (char*         )&p[ start * 2 * ch + 1 ], end - start, ch, _rc_field.t );
	}

	// 縦線
	float hz100 = (float)(int32_t)( sps / 100 );

	rc.t = _rc_field.t;
	rc.b = _rc_field.b;

	if( hz100 > 0 )
	{
		for( rc.l = hz100; rc.l < _rc_field.r; rc.l += hz100 )
		{
			rc.r = rc.l + 1;
		}
	}

	// 横線
	rc.l = 0;
	rc.r = _rc_field.r;

	for( int32_t c = 0; c < 4; c++ )
	{
		rc.t = _rc_field.t + PCMTABLE_H * ( c + 1 ) - PCMTABLE_H / 2;
		rc.b = rc.t + 1;
		g_dxdraw->FillRect_view( &rc, _line_color );
	}
}
