
#include <pxStdDef.h>

#define MAX_KEY     0x100
#define CLICK_LEFT  0x01
#define CLICK_RIGHT 0x10

//トリガの生成
static char _key     [MAX_KEY] = {0};
static char _key_old [MAX_KEY] = {0};
static char _key_trg [MAX_KEY] = {0};
static char _key_ntrg[MAX_KEY] = {0};

static int32_t  _click            =  0;
static int32_t  _click_old        =  0;
static int32_t  _click_trg        =  0;
static int32_t  _click_rtrg       =  0;
static int32_t  _wheel            =  0;
static int32_t  _wheel_old        =  0;
static int32_t  _wheel_trg        =  0;

static bool _bCapture         = false;

void KeyControl_Clear()
{
	memset( _key,      0, MAX_KEY );
	memset( _key_old , 0, MAX_KEY );
	memset( _key_trg , 0, MAX_KEY );
	memset( _key_ntrg, 0, MAX_KEY );
	_click      = 0;
	_click_old  = 0;
	_click_trg  = 0;
	_click_rtrg = 0;
	_wheel      = 0;
	_wheel_old  = 0;
	_wheel_trg  = 0;
}

void KeyControl_WM_MESSAGE( HWND hWnd, UINT msg, WPARAM w )
{
	switch( msg )
	{
	// キーが 押された/離された
	case WM_KEYDOWN    : _key[ w ] = 1; break;
	case WM_KEYUP      : _key[ w ] = 0; break;

	// マウス
	case WM_LBUTTONDOWN: _click |=  CLICK_LEFT ; if( !_bCapture                ){ _bCapture = true ; SetCapture( hWnd ); } break;
	case WM_RBUTTONDOWN: _click |=  CLICK_RIGHT; if( !_bCapture                ){ _bCapture = true ; SetCapture( hWnd ); } break;
	case WM_LBUTTONUP  : _click &= ~CLICK_LEFT ; if( !( _click & CLICK_RIGHT ) ){ _bCapture = false; ReleaseCapture(  ); } break;
	case WM_RBUTTONUP  : _click &= ~CLICK_RIGHT; if( !( _click & CLICK_LEFT  ) ){ _bCapture = false; ReleaseCapture(  ); } break;
	}
}

bool KeyControl_IsCapture()
{
	return _bCapture ? true : false;
}


void KeyControl_WM_MOUSEWHEEL( HWND hWnd, UINT message, WPARAM wParam )
{
	if( (short)HIWORD(wParam) > 0 ) _wheel++;
	if( (short)HIWORD(wParam) < 0 ) _wheel--;
}

void KeyControl_UpdateTrigger()
{
	int32_t i;

	for( i = 0; i < MAX_KEY; i++ )
	{
		if( !_key_old[ i ] &&  _key[ i ] ) _key_trg [ i ] = 1;
		else                               _key_trg [ i ] = 0;
		if(  _key_old[ i ] && !_key[ i ] ) _key_ntrg[ i ] = 1;
		else                               _key_ntrg[ i ] = 0;
		_key_old[i] = _key[i];
	}

	_click_trg  =  _click & ~_click_old;
	_click_rtrg = ~_click &  _click_old;
	_click_old  =  _click;

	if(      _wheel < _wheel_old ) _wheel_trg = -1;
	else if( _wheel > _wheel_old ) _wheel_trg =  1;
	else                           _wheel_trg =  0;
	_wheel_old = _wheel;
}

int32_t KeyControl_GetWheel(){ return _wheel_trg; }

bool KeyControl_IsKey( int32_t vk )
{
	if( _key[ vk ] ) return true;
	return false;
}

bool KeyControl_IsKeyTrigger ( int32_t vk ){ return _key_trg [ vk ] ? true : false; }
bool KeyControl_IsKeyNtrigger( int32_t vk ){ return _key_ntrg[ vk ] ? true : false; }
bool KeyControl_IsClickLeft  (            ){ if( _click & CLICK_LEFT  ) return true; return false; }
bool KeyControl_IsClickRight (            ){ if( _click & CLICK_RIGHT ) return true; return false; }

bool KeyControl_IsClickLeftTrigger()
{
	if( _click_trg & CLICK_LEFT ) return true;
	return false;
}

bool KeyControl_IsClickRightTrigger()
{
	if( _click_trg & CLICK_RIGHT ) return true;
	return false;
}

bool KeyControl_IsClickLeftRtrigger()
{
	if( _click_rtrg & CLICK_LEFT ) return true;
	return false;
}

bool KeyControl_IsClickRightRtrigger()
{
	if( _click_rtrg & CLICK_RIGHT ) return true;
	return false;
}

