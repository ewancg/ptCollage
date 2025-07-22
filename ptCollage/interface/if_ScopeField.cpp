
#include <pxtnService.h>
extern pxtnService *g_pxtn;


#include <pxwDx09Draw.h>
extern pxwDx09Draw *g_dxdraw;

#include "../../Generic/if_gen_Scroll.h"

#include "SurfaceNo.h"
#include "Interface.h"
#include "if_BaseField.h"

static uint32_t _color_field = 0xff004020;
static uint32_t _color_scope = 0xff00f080;

static fRECT    _rcField = {0};

extern if_gen_Scroll g_ScrlEventH;

typedef struct
{
	int32_t clock1;
	int32_t clock2;
}
_SCOPESTRUCT;

static _SCOPESTRUCT _scope;

// 初期化
bool if_ScopeField_init( const pxPalette* palpng )
{
	if( !palpng->get_color( COLORINDEX_scope_field, &_color_field ) ) return false;
	if( !palpng->get_color( COLORINDEX_scope_line , &_color_scope ) ) return false;
	_scope.clock1 = 0;
	_scope.clock2 = 0;
	return true;
}

void if_ScopeField_Zero()
{
	_scope.clock1 = 0;
	_scope.clock2 = 0;
}

// 領域を設定
void if_ScopeField_SetRect( const fRECT *rc_view )
{
	_rcField.l= rc_view->l + NAMETRAY_WIDTH;
	_rcField.r= rc_view->r - SCROLLBUTTONSIZE;
	_rcField.t= rc_view->t + HEADER_H + MEASNO_HEIGHT + STARTFIELD_HEIGHT + 1;
	_rcField.b= rc_view->t + HEADER_H + MEASNO_HEIGHT + STARTFIELD_HEIGHT + SCOPE_HEIGHT - 1;
}

// 領域を取得
fRECT* if_ScopeField_GetRect()
{
	return &_rcField;
}

// 選択範囲を取得
void if_ScopeField_GetSelected( int32_t *p_clock1, int32_t *p_clock2 )
{
	*p_clock1 = _scope.clock1;
	*p_clock2 = _scope.clock2;
}

// 選択範囲を取得
void if_ScopeField_GetSelected( int32_t *p_meas1, int32_t *p_beat1, int32_t *p_clock1,
								int32_t *p_meas2, int32_t *p_beat2, int32_t *p_clock2 )
{
	int32_t beat_clock;
	int32_t beat_num;

	beat_clock = g_pxtn->master->get_beat_clock();
	beat_num   = g_pxtn->master->get_beat_num();

	*p_meas1  =   _scope.clock1 / ( beat_clock   * beat_num );
	*p_beat1  = ( _scope.clock1 /   beat_clock ) % beat_num;
	*p_clock1 =   _scope.clock1 %   beat_clock;
	*p_meas2  =   _scope.clock2 / ( beat_clock   * beat_num );
	*p_beat2  = ( _scope.clock2 /   beat_clock ) % beat_num;
	*p_clock2 =   _scope.clock2 %   beat_clock;
}

void if_ScopeField_Put()
{
	fRECT   rect = {0};

	int32_t beat_w     = if_BaseField_GetBeatWidth();
	float   offset_x   = g_ScrlEventH.GetOffset   ();
	int32_t beat_clock = g_pxtn->master->get_beat_clock();

	g_dxdraw->FillRect_view( &_rcField, _color_field );

	if( _scope.clock1 == _scope.clock2 )
	{
		rect.l = ( _scope.clock1  * beat_w / beat_clock ) - offset_x + _rcField.l;
		rect.r = rect.l     + 2;
		rect.t = _rcField.t + 3;
		rect.b = _rcField.b - 3;
	}
	else
	{
		rect.l = ( _scope.clock1  * beat_w / beat_clock ) - offset_x + _rcField.l;
		rect.r = ( _scope.clock2  * beat_w / beat_clock ) - offset_x + _rcField.l;
		rect.t = _rcField.t + 5;
		rect.b = _rcField.b - 5;
	}

	if( rect.l < _rcField.l ) rect.l = _rcField.l;
	if( rect.r > _rcField.r ) rect.r = _rcField.r;
	g_dxdraw->FillRect_view( &rect, _color_scope );

}

void if_ScopeField_SetScope( int32_t clock1, int32_t clock2 )
{
	int32_t w;
	if( clock2 < clock1 )
	{
		w      = clock1;
		clock1 = clock2;
		clock2 = w;
	}
	_scope.clock1 = clock1;
	_scope.clock2 = clock2;
}

void if_ScopeField_SetScopeAll()
{
	if_ScopeField_SetScope( 0, g_pxtn->master->get_this_clock( g_pxtn->master->get_meas_num(), 0, 0 ) );
}
