#include "StdAfx.h"

#include <pxDebugLog.h>

void mbox_c_ERR( HWND hWnd, const char *fmt, ... )
{
	char str[ 512 ];

	va_list ap; va_start( ap, fmt ); vsprintf( str, fmt, ap ); va_end( ap );

	MessageBoxA( hWnd, str, "エラー", MB_OK|MB_ICONEXCLAMATION );
}

void mbox_t_ERR( HWND hWnd, const TCHAR *fmt, ... )
{
	TCHAR str[ 512 ];

	va_list ap; va_start( ap, fmt ); _vstprintf_s( str, 512, fmt, ap ); va_end( ap );

	MessageBox( hWnd, str, _T("エラー"), MB_OK|MB_ICONEXCLAMATION );
}
