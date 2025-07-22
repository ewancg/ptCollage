// '15/12/17 pxMouse.cpp

#include "./pxMouse.h"

#include <pxwrMouse.h>

pxMouse:: pxMouse( void* hwnd )
{
	_mouse     = new pxwrMouse( hwnd );

	_wheel     = 0;
	_wheel_old = 0;
	_wheel_trg = 0;
}

pxMouse::~pxMouse()
{
	if( _mouse ) delete _mouse;
}

int     pxMouse::get_x   () const{ return static_cast<pxwrMouse*>(_mouse)->get_x   (); }
int     pxMouse::get_y   () const{ return static_cast<pxwrMouse*>(_mouse)->get_y   (); }
uint8_t pxMouse::get_now () const{ return static_cast<pxwrMouse*>(_mouse)->get_now (); }
uint8_t pxMouse::get_trg () const{ return static_cast<pxwrMouse*>(_mouse)->get_trg (); }
uint8_t pxMouse::get_ntrg() const{ return static_cast<pxwrMouse*>(_mouse)->get_ntrg(); }

void    pxMouse::set_click_l ( bool b ){ static_cast<pxwrMouse*>(_mouse)->set_click_l ( b ); }
void    pxMouse::set_click_r ( bool b ){ static_cast<pxwrMouse*>(_mouse)->set_click_r ( b ); }
void    pxMouse::set_position(        ){ static_cast<pxwrMouse*>(_mouse)->set_position(   ); }


void    pxMouse::wheel( int32_t v )
{
	_wheel += v;
}


void    pxMouse::trigger_update ()
{
	static_cast<pxwrMouse*>(_mouse)->trigger_update();

	if     ( _wheel < _wheel_old ) _wheel_trg = -1;
	else if( _wheel > _wheel_old ) _wheel_trg =  1;
	else                           _wheel_trg =  0;
	_wheel_old = _wheel;
}

int32_t pxMouse::wheel_get() const{ return _wheel_trg; }

