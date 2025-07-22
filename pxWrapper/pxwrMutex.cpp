
#ifdef pxPLATFORM_windows
#include <pxwMutex.h>
#else
#include <pxpMutex.h>
#endif

#include "./pxwrMutex.h"


pxwrMutex:: pxwrMutex()
{
	_mtx = NULL;
}
pxwrMutex::~pxwrMutex()
{
	if( !_mtx ) return;
#ifdef pxPLATFORM_windows
	delete static_cast<pxwMutex*>(_mtx);
#else
	delete static_cast<pxpMutex*>(_mtx);
#endif
	_mtx = NULL;
}

bool pxwrMutex::init   ()
{
	if( _mtx ) return false;

	bool b_ret = false;
#ifdef pxPLATFORM_windows
	if( !(_mtx = new pxwMutex() ) || !static_cast<pxwMutex*>(_mtx)->init() ) goto term;
#else
	if( !(_mtx = new pxpMutex() ) || !static_cast<pxpMutex*>(_mtx)->init() ) goto term;
#endif
	b_ret = true;
term:
	return b_ret;
}

void pxwrMutex::lock   ()
{
	if( !_mtx ) return;
#ifdef pxPLATFORM_windows
	static_cast<pxwMutex*>(_mtx)->lock();
#else
	static_cast<pxpMutex*>(_mtx)->lock();
#endif
}

bool pxwrMutex::trylock()
{
	if( !_mtx ) return false;
#ifdef pxPLATFORM_windows
	return static_cast<pxwMutex*>(_mtx)->trylock();
#else
	return static_cast<pxpMutex*>(_mtx)->trylock();
#endif
}

void pxwrMutex::unlock ()
{
	if( !_mtx ) return;
#ifdef pxPLATFORM_windows
	static_cast<pxwMutex*>(_mtx)->unlock();
#else
	static_cast<pxpMutex*>(_mtx)->unlock();
#endif
}
