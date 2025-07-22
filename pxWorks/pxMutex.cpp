
#ifndef pxSTDAFX_H
#include <stdlib.h>
#endif


#include <pxwrMutex.h>

#include "./pxMutex.h"


pxMutex:: pxMutex()
{
	_mtx = NULL;
}

pxMutex::~pxMutex()
{
	if( !_mtx ) return;
	delete static_cast<pxwrMutex*>(_mtx); _mtx = NULL;
}

bool pxMutex::init()
{
	bool b_ret = false;
	if( !(_mtx = new pxwrMutex())               ) goto term;
	if( !static_cast< pxwrMutex*>(_mtx)->init() ) goto term;
	b_ret = true;
term:
	return b_ret;
}

void pxMutex::lock   ()
{
	if( !_mtx ) return;
	static_cast<pxwrMutex*>(_mtx)->lock();
}

bool pxMutex::trylock()
{
	if( !_mtx ) return false;
	return static_cast<pxwrMutex*>(_mtx)->trylock();
}

void pxMutex::unlock ()
{
	if( !_mtx ) return;
	static_cast<pxwrMutex*>(_mtx)->unlock();
}
