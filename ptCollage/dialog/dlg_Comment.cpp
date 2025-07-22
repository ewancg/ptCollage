﻿
#include <richedit.h>

#include <pxMem.h>
#include <pxShiftJIS.h>
#include <pxTText.h>

#include <pxtnService.h>
extern pxtnService *g_pxtn;

#include <pxwWindowRect.h>

#include "../../Generic/Japanese.h"

#include "../resource.h"


static bool _malloc_zero( void **pp, int32_t size )
{
	*pp = malloc( size ); if( !( *pp ) ) return false;
	memset( *pp, 0, size );              return true;
}

bool _InitDialog( HWND hDlg )
{
	pxTText tt;
	if( !tt.set_sjis_to_t( g_pxtn->text->get_comment_buf( NULL ) ) ) return false;
	SetDlgItemText( hDlg, IDC_COMMENT, tt.tchr() );
	return true;
}

bool _EnableDialog( HWND hDlg )
{
	bool    b_ret    = false;
	TCHAR*  buf_ctrl = NULL ;
	int32_t len      = GetWindowTextLength( GetDlgItem( hDlg, IDC_COMMENT ) );

	pxTText tt;

	if( !pxMem_zero_alloc( (void **)&buf_ctrl, (len + 1) * sizeof(TCHAR) ) ) return false;

	GetDlgItemText( hDlg, IDC_COMMENT, buf_ctrl, len + 1 );

	if( !tt.set_TCHAR_to_sjis( buf_ctrl ) ) goto term;

    static int32_t comment_size;
    comment_size = 0;
	pxShiftJIS_check_size( tt.sjis(), &comment_size, true );

	if( !g_pxtn->text->set_comment_buf( tt.sjis(), comment_size ) ) goto term;

	b_ret = true;
term:
	pxMem_free( (void**)&buf_ctrl );
	return b_ret;
}

#ifdef px64BIT
INT_PTR
#else
BOOL CALLBACK
#endif
dlg_Comment( HWND hDlg, UINT msg, WPARAM w, LPARAM l )
{
	switch( msg )
	{

	case WM_INITDIALOG:

		Japanese_DialogItem_Change( hDlg );
		pxwWindowRect_center      ( hDlg );
		_InitDialog               ( hDlg );
		break;

	case WM_COMMAND:

		switch( LOWORD(w) )
		{
		case IDOK:
			if( !_EnableDialog( hDlg ) )
			{
				Japanese_MessageBox( hDlg, _T("set comment"), _T("error"), MB_OK|MB_ICONEXCLAMATION );
				break;
			}
			EndDialog( hDlg, true );
			break;

		case IDCANCEL:
			EndDialog( hDlg, false );
			break;
		}
		default:return false;
	
	}
	return true;
}
