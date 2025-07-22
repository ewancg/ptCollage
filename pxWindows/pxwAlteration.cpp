#include "./pxwAlteration.h"

pxwAlteration:: pxwAlteration()
{
	_hwnd   = NULL ;
	_b_alte = false;
}

void pxwAlteration::set_window( HWND hwnd )
{
	_hwnd   = hwnd;
}

void pxwAlteration::off()
{
	if( _hwnd )
	{
		TCHAR str[MAX_PATH] = { 0 };
		GetWindowText( _hwnd, str, MAX_PATH );
		int a = _tcslen( str );
		if( a && str[a-1] == '*' ){ str[a-1] = '\0'; SetWindowText( _hwnd, str ); }
	}

	_b_alte = false;
}

void pxwAlteration::set  ()
{
	if( _hwnd )
	{
		TCHAR str[MAX_PATH] = { 0 };
		GetWindowText( _hwnd, str, MAX_PATH );
		int a = _tcslen( str );
		if( a && str[a-1] != '*' ){ _tcscat( str, _T("*") ); SetWindowText( _hwnd, str ); }
	}
	_b_alte = true ;
}

bool pxwAlteration::is   () const
{
	return _b_alte;
}

