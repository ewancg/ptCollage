
#include "./pxwMutex.h"

pxwMutex:: pxwMutex()
{
	_cs = NULL;
}
pxwMutex::~pxwMutex()
{
	if( !_cs ) return;
	DeleteCriticalSection( _cs );
	delete _cs;
	_cs = NULL;
}

bool pxwMutex::init   ()
{
	if( !(_cs = new CRITICAL_SECTION) ) return false;
	InitializeCriticalSection( _cs );
	return true;
}

void pxwMutex::lock   ()
{
	if( !_cs ) return;
	EnterCriticalSection( _cs );
}

bool pxwMutex::trylock()
{
	if( !_cs ) return false;
	return TryEnterCriticalSection( _cs ) ? true : false;
}

void pxwMutex::unlock ()
{
	if( !_cs ) return;
	LeaveCriticalSection( _cs );
}
