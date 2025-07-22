﻿
#include <pxDebugLog.h>

#include <pxFile2.h>
static pxFile2* _app_file_profile = NULL;
static pxFile2* _app_file_data    = NULL;
#include <pxPath.h>

#include <pxwFilePath.h>
#include <pxwXAudio2Keep.h>

#include "resource.h"

HWND         g_hDlg                   = NULL ;
TCHAR        g_dir_module[ MAX_PATH ] = { 0 };

static bool  _bSuspend = false;
static TCHAR _input_path[ MAX_PATH ];


DWORD CALLBACK thrd_Search( LPVOID l );
bool thrd_Search_Init     ();
void thrd_Search_Release  ();

static const TCHAR* _app_name_t_en = _T("pxtone droplist");

#pragma comment(lib,"version")

static int32_t _GetCompileVersion( int32_t *p1, int32_t *p2, int32_t *p3, int32_t *p4 )
{
	LPVOID           p       = NULL;
	DWORD            dummy;
	DWORD            size;
	VS_FIXEDFILEINFO *info;
	UINT             vSize; 
	TCHAR            path[ MAX_PATH ];

	int32_t v[ 4 ];

	memset( v, 0, sizeof(int32_t) * 4 );
	if( p1 ) *p1 = 0;
	if( p2 ) *p2 = 0;
	if( p3 ) *p3 = 0;
	if( p4 ) *p4 = 0;

	GetModuleFileName( NULL, path, MAX_PATH );

	size = GetFileVersionInfoSize( path, &dummy ); 
	if( !size ) goto End;

	p = malloc( size ); 
	if( !p                                                    ) goto End;
	if( !GetFileVersionInfo( path, 0, size, p )               ) goto End;
	if( !VerQueryValue( p, _T("\\"), (LPVOID*)&info, &vSize ) ) goto End;

	v[ 0 ] = HIWORD(info->dwFileVersionMS);
	v[ 1 ] = LOWORD(info->dwFileVersionMS);
	v[ 2 ] = HIWORD(info->dwFileVersionLS);
	v[ 3 ] = LOWORD(info->dwFileVersionLS);

	if( p1 ) *p1 = v[ 0 ];
	if( p2 ) *p2 = v[ 1 ];
	if( p3 ) *p3 = v[ 2 ];
	if( p4 ) *p4 = v[ 3 ];

End:
	if( p ) free( p );

	return v[ 0 ] * 1000 + v[ 1 ] * 100 + v[ 2 ] * 10 + v[ 3 ];
}


static BOOL CALLBACK _Procedure( HWND hDlg, UINT msg, WPARAM w, LPARAM l )
{
	static DWORD dw;
	static HANDLE  hThread = NULL;

	switch( msg ){

	//ダイアログ起動
	case WM_INITDIALOG:
		g_hDlg = hDlg;
		SetDlgItemText( hDlg, IDC_PATH, _input_path );
		hThread = CreateThread( NULL, 0, thrd_Search, &_bSuspend, 0, &dw );

		return 1;

	//ボタンクリック
	case WM_COMMAND:

		switch( LOWORD( w ) ){
		//キャンセル
		case IDCANCEL:
			EndDialog( hDlg, false );
			break;

		case IDC_STOP:
			EnableWindow( GetDlgItem( hDlg, IDC_STOP ), false );
			_bSuspend  = true;
			break;
		}

		default:return false;
	
	}
	return true;
}

int WINAPI _tWinMain( HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpCmd, int nCmd )
{
	InitCommonControls();
	if( FAILED( CoInitializeEx( NULL, COINIT_MULTITHREADED ) ) ) return 0;


	// for xaudio2_7.dll_unloaded bug.
	pxwXAudio2Keep_loadlib* xa2_keep = new pxwXAudio2Keep_loadlib();
#ifdef _DEBUG
	if( !xa2_keep->invoke( true  ) )
#else
	if( !xa2_keep->invoke( false ) )
#endif
	{ MessageBox( NULL, _T("keep XAudio2 Error"), _app_name_t_en, MB_OK|MB_ICONERROR ); return -1; }


	pxwFilePath_GetModuleDirectory( g_dir_module );

	_app_file_data    = new pxFile2(); _app_file_data   ->init_base( _T("data_ptd"), false );
	_app_file_profile = new pxFile2(); _app_file_profile->init_base( _T("temp_ptd"), true  );
	pxPath_setMode( pxPathMode_auto );

	if( !pxDebugLog_init( _T("temp_ptd"), _T("debuglog") ) ) return -1;

	dlog_c( "version %d.", _GetCompileVersion( 0, 0, 0, 0 ) );

	thrd_Search_Init();

	memset( _input_path, 0, MAX_PATH );

	{
		const TCHAR*  p_file_name = _T("last_path.txt");
		pxDescriptor* desc        = NULL;

		if( pxwFilePath_ArgToPath( lpCmd, _input_path ) )
		{
			if( _app_file_profile->open_w( &desc, p_file_name, NULL, NULL ) )
			{
				desc->w_asfile( _input_path, sizeof(TCHAR), MAX_PATH );
			}
		}
		else
		{
			if( _app_file_profile->open_r( &desc, p_file_name, NULL, NULL ) )
			{
				desc->r( _input_path, sizeof(TCHAR), MAX_PATH );
			}
		}
		SAFE_DELETE( desc );

		if( !PathIsDirectory( _input_path ) ) return 0;
	}


	DialogBox( hInst, _T("DLG_PROGRESS"), NULL, _Procedure );

	thrd_Search_Release();

	SAFE_DELETE( xa2_keep );

	return 1;
}