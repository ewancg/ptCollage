﻿
#pragma comment(lib,"d3d9")
#pragma comment(lib,"d3dx9")

#include <pxDebugLog.h>
#include <pxtnPulse_Oggv.h>

#include <pxFile2.h>
static pxFile2* _app_file_common  = NULL;
static pxFile2* _app_file_data    = NULL;
static pxFile2* _app_file_profile = NULL;
#include <pxPath.h>

#include <pxStrT.h>
TCHAR* g_posted_path = NULL;

#include <pxLocalize.h>
pxLocalize* g_local = NULL ;

#include <pxwFilePath.h>
#include <pxwWindowRect.h>
#include <pxwTextOverride.h>
#include <pxwXAudio2Keep.h>

#include <pxwAlteration.h>
pxwAlteration*          g_alte     = NULL;

#include <pxtnPulse_NoiseBuilder.h>
pxtnPulse_NoiseBuilder *g_ptn_bldr = NULL;

#include <pxtnService.h>
pxtnService*       g_pxtn = NULL;

#include <pxtonewinXA2.h>
pxtonewinXA2*   g_strm_xa2 = NULL;
#include <pxtonewinWoice.h>
pxtonewinWoice* g_strm_woi = NULL;

#include <pxtnPulse_Frequency.h>
pxtnPulse_Frequency *g_freq = NULL;

#include <pxSurface.h>
static pxSurface* _surf_palette = NULL;

#include "../Generic/cls_ExistingWindow.h"
#include "../Generic/MessageBox.h"
#include "../Generic/if_Generic.h"
#include "../Generic/Japanese.h"
#include "../Generic/Menu_HistoryW.h"

#include "../Generic/pxMidiIn.h"
pxMidiIn*      g_midi_in = NULL;

#include <pxwDx09Draw.h>
pxwDx09Draw*   g_dxdraw  = NULL;

#include <pxwPathDialog.h>
pxwPathDialog* g_path_dlg_proj  = NULL;
pxwPathDialog* g_path_dlg_tune  = NULL;
pxwPathDialog* g_path_dlg_build = NULL;

pxwPathDialog* g_path_dlg_wav   = NULL;
pxwPathDialog* g_path_dlg_ogg   = NULL;
pxwPathDialog* g_path_dlg_ptv   = NULL;
pxwPathDialog* g_path_dlg_ptn   = NULL;
pxwPathDialog* g_path_dlg_add   = NULL;

static const TCHAR* _title_proj_save_j = _T("プロジェクトの保存"        );
static const TCHAR* _title_proj_load_j = _T("プロジェクトの読み込み"    );
static const TCHAR* _title_tune_save_j = _T("曲ファイルの保存"          );
static const TCHAR* _title_build_j     = _T("WAV形式で出力"             );
static const TCHAR* _title_wav_expt_j  = _T("WAV音源をエクスポート"     );
static const TCHAR* _title_ogg_expt_j  = _T("OGG音源をエクスポート"     );
static const TCHAR* _title_ptv_expt_j  = _T("ptvoice音源をエクスポート" );
static const TCHAR* _title_ptn_expt_j  = _T("ptnoise音源をエクスポート" );

static const TCHAR* _title_proj_save_e = _T("Save Project.."            );
static const TCHAR* _title_proj_load_e = _T("Load Project.."            );
static const TCHAR* _title_tune_save_e = _T("Save pttune.."             );
static const TCHAR* _title_build_e     = _T("output *.wav"              );
static const TCHAR* _title_wav_expt_e  = _T("Export wav"                );
static const TCHAR* _title_ogg_expt_e  = _T("Export ogg"                );
static const TCHAR* _title_ptv_expt_e  = _T("Export ptvoice"            );
static const TCHAR* _title_ptn_expt_e  = _T("Export ptnoise"            );



#include "../pxtoneTool/pxtoneTool.h"
#include "../ptConfig/ptConfig.h"

#include "./interface/SurfaceNo.h"
#include "./interface/Interface.h"
#include "./interface/if_Player.h"
#include "./interface/if_Projector.h"
#include "./interface/if_UnitTray.h"
#include "./interface/if_WoiceTray.h"

#include "./resource.h"

#include "./ptCollage.h"

#include "./UndoEvent.h"
#include "./JapaneseTable.h"
#include "./Project.h"
#include "./ScopeEvent.h"
#include "./Unit.h"
#include "./Woice.h"

#include "./MidiInput.h"

#define _DEFAULT_WINDOW_W	640
#define _DEFAULT_WINDOW_H	480
#define _MAX_HISTORY_NUM     20

int32_t    g_MinimizeWidth;
int32_t    g_MinimizeHeight;

HINSTANCE  g_hInst;
HWND       g_hWnd_Main  = NULL;
HMENU      g_hMenu_Main = NULL;

TCHAR      g_dir_module[ MAX_PATH ] = {0};
	       
TCHAR      g_app_name[ 32 ] = {0};
TCHAR*     gClassName_Main  = _T("Main"     );
TCHAR*     g_main_rect_name = _T("main.rect");

static const TCHAR* _app_name_jp = _T("ピストンコラージュ");
static const TCHAR* _app_name_en = _T("pxtone Collage"    );

LRESULT CALLBACK WindowProc_Main( HWND hWnd, UINT msg, WPARAM w, LPARAM l );

bool Interface_init( HWND hWnd, const pxPalette* palette, const pxFile2* file_profile );
void Interface_release();

int32_t GetCompileVersion( int32_t *p1, int32_t *p2, int32_t *p3, int32_t *p4 );
int32_t GetDateLimit( SYSTEMTIME *st_limit1, SYSTEMTIME *st_limit2 );

bool    pxtoneProject_load_and_init_tools( HWND hWnd, const TCHAR *path, bool *pb_cancel, bool *pb_save_failed );
void    MainProc_set_file_profile( const pxFile2* file_profile );

bool RegistWindowClass(
	   HINSTANCE hInst,
	   TCHAR      *class_name,
	   WNDPROC   lpfnWndProc,
	   HICON     hIcon,
	   HBRUSH    hbrBackground )
{

    WNDCLASSEX wc;

	memset( &wc, 0, sizeof(WNDCLASSEX) );

    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.lpszClassName = class_name;
	wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = lpfnWndProc;
    wc.hInstance     = hInst;        //インスタンス
    wc.hbrBackground = hbrBackground;
    wc.hIcon         = hIcon;//LoadIcon(   NULL, IDI_APPLICATION );
//	wc.hIconSm       = hIconSm;//LoadIcon( NULL, IDI_APPLICATION );
    wc.hCursor       = LoadCursor( NULL, IDC_ARROW       );

    if( !RegisterClassEx( &wc ) ) return false;

	return true;
}


// I/O..
static bool _io_read( void* user, void* p_dst, int32_t size, int32_t num )
{
	if( fread( p_dst, size, num, (FILE*)user ) != num ) return false; return true;
}
static bool _io_write( void* user, const void* p_dst, int32_t size, int32_t num )
{
	if( fwrite( p_dst, size, num, (FILE*)user ) != num ) return false; return true;
}
static  bool _io_seek( void* user,       int   mode , int32_t size              )
{
	if( fseek( (FILE*)user, size, mode ) ) return false; return true;
}
static bool _io_pos( void* user, int32_t* p_pos )
{
	fpos_t sz = 0;
	if( fgetpos( (FILE*)user, &sz ) ) return false;
	*p_pos  = (int32_t)sz;
	return true;
}



int WINAPI wWinMain( HINSTANCE hInst, HINSTANCE hPrevInst, LPWSTR lpCmd, int nCmd )
{
	InitCommonControls( );

	if( FAILED( CoInitializeEx( NULL, COINIT_MULTITHREADED ) ) ) return 0;

	// for xaudio2_7.dll_unloaded bug.
	pxwXAudio2Keep_loadlib* xa2_keep = new pxwXAudio2Keep_loadlib();
#ifdef _DEBUG
	if( !xa2_keep->invoke( true  ) )
#else
	if( !xa2_keep->invoke( false ) )
#endif
	{ MessageBox( NULL, _T("keep XAudio2 Error"), _app_name_en, MB_OK|MB_ICONERROR ); return -1; }


#ifdef DEBUGGER_RELEASE
	{
		SYSTEMTIME st   ;
		int32_t        today;

		GetLocalTime( &st );
		today = st.wYear * 10000 + st.wMonth * 100 + st.wDay;
		if( today < 20070609 ){ MessageBox( NULL, "-1", "error", MB_OK|MB_ICONEXCLAMATION ); return 1; }
		if( today > 20070630 ){ MessageBox( NULL, " 1", "error", MB_OK|MB_ICONEXCLAMATION ); return 1; }
		MessageBox( NULL, "Debugger Release.", "pxtone Collage", MB_OK|MB_ICONINFORMATION );
	}
#endif

	cls_EXISTINGWINDOW existing_window;
	static TCHAR*      mutex_name   = _T("ptcollage"    );
	static TCHAR*      mapping_name = _T("map_ptcollage");
	TCHAR              path_drop[ MAX_PATH ] = {};

	g_hInst = hInst;

	// priority.
	SetThreadPriority( GetCurrentThread(), THREAD_PRIORITY_HIGHEST );

	//汎用のパスを取得-------------------------------------
	pxwFilePath_GetModuleDirectory( g_dir_module );

	_app_file_common  = new pxFile2(); _app_file_common ->init_base( _T("data_common"), false );
	_app_file_data    = new pxFile2(); _app_file_data   ->init_base( _T("data_ptc"   ), false );
	_app_file_profile = new pxFile2(); _app_file_profile->init_base( _T("temp_ptc"   ), true  );
	pxPath_setMode( pxPathMode_auto );

	pxDebugLog_init( _T("temp_ptc"), _T("debuglog") );

	Woice_init               ( _app_file_profile );
	pxwWindowRect_init       ( _app_file_profile );
	MainProc_set_file_profile( _app_file_profile );

	dlog_c( "version %d.", GetCompileVersion( 0, 0, 0, 0 ) );

	g_local = new pxLocalize();
	if( !g_local->init( _T("localize") ) ) goto term;
	g_local->set( pxLOCALREGION_ja );

    _app_file_data->set_localize( g_local );

	if( pxwFilePath_ArgToPath( lpCmd, path_drop ) ) pxStrT_copy_allocate( &g_posted_path, path_drop );

	if( !existing_window.Check( mutex_name, mapping_name, WM_USER_RELATEDFILE ) ) return 0;

	// japanese..
	{
		TCHAR path[ MAX_PATH ] = {0}; _stprintf_s( path, MAX_PATH, _T("%s\\%s"), g_dir_module, _T("japanese.ico") );
		FILE* fp = _tfopen( path, _T("rb") );
		if( fp ){ fclose( fp ); JapaneseTable_init( true  ); }
		else    {               JapaneseTable_init( false ); }
    }

	if( Japanese_Is() ) _tcscpy( g_app_name, _app_name_jp );
	else                _tcscpy( g_app_name, _app_name_en );

	//ウインドウクラスを定義
	if( !RegistWindowClass( hInst,
			gClassName_Main,
			WindowProc_Main,
			LoadIcon( hInst, _T("0") ),
			(HBRUSH)GetStockObject(NULL_BRUSH) ) )
	{
		return false;
	}

    g_hMenu_Main = LoadMenu( hInst, _T("MENU_MAIN") );

	Japanese_MenuItem_Change( g_hMenu_Main );

	int width_window;
	int height_window;
	width_window  = GetSystemMetrics(SM_CXFRAME)*2 + _DEFAULT_WINDOW_W;

	height_window = GetSystemMetrics(SM_CYFRAME)*2 +
					GetSystemMetrics(SM_CYCAPTION) +
					GetSystemMetrics(SM_CYMENU)    + _DEFAULT_WINDOW_H;

	g_hWnd_Main    = CreateWindow(
					gClassName_Main,//ウインドウクラスの名前
					g_app_name,//タイトル
					WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN,
					CW_USEDEFAULT, CW_USEDEFAULT,// x, y
					width_window, height_window, // w, h
					HWND_DESKTOP,                //親ウインドウ
                    g_hMenu_Main, hInst, NULL );
    if( !existing_window.Mapping( mutex_name, mapping_name, g_hWnd_Main ) ) return 0;

    {
		UINT table[ _MAX_HISTORY_NUM ] =
		{
			IDM_HISTORY_0 , IDM_HISTORY_1 , IDM_HISTORY_2 ,
			IDM_HISTORY_3 , IDM_HISTORY_4 , IDM_HISTORY_5 ,
			IDM_HISTORY_6 , IDM_HISTORY_7 , IDM_HISTORY_8 ,
			IDM_HISTORY_9 ,
			IDM_HISTORY_10, IDM_HISTORY_11, IDM_HISTORY_12,
			IDM_HISTORY_13, IDM_HISTORY_14, IDM_HISTORY_15,
			IDM_HISTORY_16, IDM_HISTORY_17, IDM_HISTORY_18,
			IDM_HISTORY_19,
        };

		Menu_HistoryW_init( GetSubMenu( GetSubMenu( g_hMenu_Main, 0 ), 1 ), _MAX_HISTORY_NUM, table, IDM_HISTORY_D, _app_file_profile );
		Menu_HistoryW_Load();
    }

	{
		pxwTextOverride ovr;
		pxDescriptor*   desc = NULL;

		if( _app_file_data->open_localize( &desc, _T("words-menu-main.txt"), NULL ) )
		{
			if( !ovr.override_menu( GetMenu( g_hWnd_Main ), desc, true ) )
			{
				const TCHAR* inv_name =  ovr.get_inv_name();
				if( inv_name ) dlog_t( "inv-menu-local:", inv_name );
				else           dlog_c( "inv-menu-local:"           );
			}
		}
		SAFE_DELETE( desc );
    }

	// Load RECT
	pxwWindowRect_load( g_hWnd_Main, g_main_rect_name, true, true );

	// DirectDrawの初期化
	{
		g_dxdraw = new pxwDx09Draw( _app_file_data );
		if( !g_dxdraw->init( g_hWnd_Main/*, xsize, ysize*/ ) ){ mbox_c_ERR( NULL, "dxdraw." ); return false; }
	}

	{// オフセットを設定
		g_MinimizeWidth  = HEADER_W + GetSystemMetrics(SM_CXFRAME)*2;
		g_MinimizeHeight = MINVIEW_HEIGHT + VOLUME_HEIGHT +
							GetSystemMetrics(SM_CYFRAME)*2 +
							GetSystemMetrics(SM_CYCAPTION) +
							GetSystemMetrics(SM_CYMENU) ;
	}

	{// LOADING..表示
		DWORD count;

		count = GetTickCount();

		if( !if_gen_splash( g_hWnd_Main, g_dxdraw, SURF_LOADING, 2 ) ){ mbox_c_ERR( NULL, "error: splash." ); goto term; }

		g_midi_in = new pxMidiIn();

		{
			bool b_err = false;

			_surf_palette = new pxSurface();

			{
				pxDescriptor* desc = NULL;
				if( _app_file_common->open_r( &desc, _T("img"), _T("colors.png"  ), NULL ) )
				{
					if( !_surf_palette->png_read( desc, 0, 0, NULL ) ){ mbox_c_ERR( NULL, "color:default" ); SAFE_DELETE( desc ); return false; }
					g_dxdraw->default_palette_set( _surf_palette->get_palette() );
				}
				SAFE_DELETE( desc );
			}

			if( !g_dxdraw->tex_load( _T("img"), _T("fields.png" ), SURF_FIELDS  ) ) b_err = true;
			if( !g_dxdraw->tex_load( _T("img"), _T("dialogs.png"), SURF_DIALOGS ) ) b_err = true;
			if( !g_dxdraw->tex_load( _T("img"), _T("menus.png"  ), SURF_MENUS   ) ) b_err = true;
			if( !g_dxdraw->tex_load( _T("img"), _T("tables.png" ), SURF_TABLES  ) ) b_err = true;

			pxGLYPH_PARAM1 prm = {0};
			_tcscpy( prm.font_name, _T("MS Gothic") );
			prm.font_h      = 12;
			prm.font_argb   = 0xff00f080;
			prm.type        = pxGLYPH_mono;
			prm.b_font_bold = false;
			prm.grid_x      = 32;
			prm.grid_y      = 32;

			_surf_palette->get_palette()->get_color( COLORINDEX_font_unit, &prm.font_argb );

			for( int i = 0; i < 10; i++ )
			{
				if( !g_dxdraw->tex_create( UNITNAME_WIDTH , UNITNAME_HEIGHT  *10, 0x00000000, SURF_UNITNAME  +i ) ) b_err = true;
				if( !g_dxdraw->tex_glyph_init( SURF_UNITNAME  + i, &prm, 128, false ) ){ mbox_c_ERR( NULL, "glyph:ms gothic" ); return false; }
			}
			for( int i = 0; i < 10; i++ )
			{
				if( !g_dxdraw->tex_create( WOICENAME_WIDTH, WOICENAME_HEIGHT *10, 0x00000000, SURF_WOICENAME +i ) ) b_err = true;
				if( !g_dxdraw->tex_glyph_init( SURF_WOICENAME + i, &prm, 128, false ) ){ mbox_c_ERR( NULL, "glyph:ms gothic" ); return false; }
			}

			_surf_palette->get_palette()->get_color( COLORINDEX_font_project, &prm.font_argb );
			{
				if( !g_dxdraw->tex_create( PROJECTNAME_WIDTH, PROJECTNAME_WIDTH, 0x00000000, SURF_PROJECTNAME ) ) b_err = true;
				if( !g_dxdraw->tex_glyph_init( SURF_PROJECTNAME  , &prm, 128, false ) ){ mbox_c_ERR( NULL, "glyph:ms gothic" ); return false; }
			}

			if( b_err ){ mbox_c_ERR( NULL, "load img." ); goto term; }

			if_gen_init( g_dxdraw, SURF_DIALOGS );
		}

		g_pxtn     = new pxtnService           ( _io_read, _io_write, _io_seek, _io_pos );
		if( g_pxtn->init_collage( pxtnMAX_EVENTNUM ) != pxtnOK ) goto term;

		g_freq     = new pxtnPulse_Frequency   ( _io_read, _io_write, _io_seek, _io_pos ); if( !g_freq    ->Init() ) goto term;
		g_ptn_bldr = new pxtnPulse_NoiseBuilder( _io_read, _io_write, _io_seek, _io_pos ); if( !g_ptn_bldr->Init() ) goto term;

		g_pxtn->clear();

		g_alte     = new pxwAlteration         (); g_alte->set_window( g_hWnd_Main );

		// config
		ptConfig cfg( _app_file_profile, ptcDEFAULT_SPS, ptcDEFAULT_CH_NUM, ptcDEFAULT_BUF_SEC );
		cfg.load();

		g_pxtn->set_sampled_callback( if_Player_Callback_Sampled, g_hWnd_Main );

		g_strm_xa2 = new pxtonewinXA2();
        if( !g_strm_xa2->init( g_pxtn, pxtnMAX_STREAMINGVOICE, pxtnMAX_STREAMINGVOICE ) )
        {
            Japanese_MessageBox( NULL, _T("Streaming Init"), _T("error"), MB_OK|MB_ICONEXCLAMATION );
            goto term;
        }
		g_strm_woi = new pxtonewinWoice();
		if( !g_strm_woi->init( g_strm_xa2 ) )
		{
			Japanese_MessageBox( NULL, _T("pxtone tool lib"), _T("error"), MB_OK|MB_ICONEXCLAMATION );
			goto term;
		}

        if( !g_strm_xa2->stream_start( cfg.strm->ch_num, cfg.strm->sps, cfg.strm->buf_sec ) )
        {
            Japanese_MessageBox( NULL, _T("Streaming Init"), _T("error"), MB_OK|MB_ICONEXCLAMATION );
            goto term;
        }

		{
			const TCHAR* title_save = NULL;
			const TCHAR* title_load = NULL;

			g_path_dlg_proj = new pxwPathDialog();
			if( Japanese_Is() ){ title_save = _title_proj_save_j; title_load = _title_proj_load_j; }
			else               { title_save = _title_proj_save_e; title_load = _title_proj_load_e; }
			if( !g_path_dlg_proj->init( _app_file_profile,
				_T("ptcop {*.ptcop}\0*.ptcop*\0All files {*.*}\0*.*\0\0"),
				_T("ptcop" ), _T("ptc-proj.path"),
				title_save, title_load, NULL ) ) goto term;

			g_path_dlg_tune = new pxwPathDialog();
			if( Japanese_Is() ) title_save = _title_tune_save_j;
			else                title_save = _title_tune_save_e;	
			if( !g_path_dlg_tune->init( _app_file_profile,
				_T("pttune {*.pttune}\0*.pttune*\0All files {*.*}\0*.*\0\0"),
				_T("pttune"), _T("ptc-tune.path"),
				title_save, title_load, NULL ) ) goto term;

			g_path_dlg_build = new pxwPathDialog();
			if( Japanese_Is() ) title_save = _title_build_j;
			else                title_save = _title_build_e;	
			if( !g_path_dlg_build->init( _app_file_profile,
				_T("wav {*.wav}\0*.wav*\0") _T("All files {*.*}\0*.*\0\0"),
				_T("wav"), _T("ptc-build.path"), title_save, title_load, NULL ) ) goto term;

			// materials.

			g_path_dlg_wav = new pxwPathDialog();
			if( Japanese_Is() ){ title_save = _title_wav_expt_j; title_load = NULL; }
			else               { title_save = _title_wav_expt_e; title_load = NULL; }
			if( !g_path_dlg_wav->init( _app_file_profile,
				_T("wav {*.wav}\0*.wav*\0All files {*.*}\0*.*\0\0"   ),
				_T("wav" ), _T("ptc-wav.path"), title_save, NULL, NULL ) ) goto term;

			g_path_dlg_ogg = new pxwPathDialog();
			if( Japanese_Is() ){ title_save = _title_ogg_expt_j; title_load = NULL; }
			else               { title_save = _title_ogg_expt_e; title_load = NULL; }
			if( !g_path_dlg_ogg->init( _app_file_profile,
				_T("ogg {*.ogg}\0*.ogg*\0All files {*.*}\0*.*\0\0"   ),
				_T("ogg" ), _T("ptc-ogg.path"), title_save, NULL, NULL ) ) goto term;

			g_path_dlg_ptv = new pxwPathDialog();
			if( Japanese_Is() ){ title_save = _title_ptv_expt_j; title_load = NULL; }
			else               { title_save = _title_ptv_expt_e; title_load = NULL; }
			if( !g_path_dlg_ptv->init( _app_file_profile,
				_T("ptvoice {*.ptvoice}\0*.ptvoice*\0All files {*.*}\0*.*\0\0"   ),
				_T("ptvoice" ), _T("ptc-ptv.path"), title_save, NULL, NULL ) ) goto term;

			g_path_dlg_ptn = new pxwPathDialog();
			if( Japanese_Is() ){ title_save = _title_ptn_expt_j; title_load = NULL; }
			else               { title_save = _title_ptn_expt_e; title_load = NULL; }
			if( !g_path_dlg_ptn->init( _app_file_profile,
				_T("ptnoise {*.ptnoise}\0*.ptnoise*\0All files {*.*}\0*.*\0\0"   ),
				_T("ptnoise" ), _T("ptc-ptn.path"), title_save, NULL, NULL ) ) goto term;

			// add sound resource.
			g_path_dlg_add = new pxwPathDialog();
			if( !g_path_dlg_add->init( _app_file_profile,
				_T("add {*.add}\0*.add*\0All files {*.*}\0*.*\0\0"   ),
				_T("add" ), _T("ptc-add.path"), NULL, NULL, NULL ) ) goto term;
		}

		g_strm_woi->set_sps( cfg.strm->sps );

		if( !pxtoneTool_HearSelect_Initialize( g_strm_woi, _app_file_profile ) ) goto term;

		// font
		if_Projector_RedrawName   ( cfg.font->name );
		if_UnitTray_RedrawAllName ( cfg.font->name );
		if_WoiceTray_RedrawAllName( cfg.font->name );

		// MIDI..
		MidiInput_Init ();
		MidiInput_Reset( cfg.midi->b_velo, cfg.midi->key_tuning );
		g_midi_in->Open( cfg.midi->name, g_hWnd_Main, NULL );
		g_midi_in->Input_Start();

		if( !UndoEvent_Initialize( pxtnMAX_TUNEUNITSTRUCT ) ) goto term;
		if( !Interface_init( g_hWnd_Main, _surf_palette->get_palette(), _app_file_profile ) ) goto term;
		ScopeEvent_Initialize( pxtnMAX_EVENTNUM );

		// ドロップファイル or 前回ファイル のロード
		pxtoneProject_load_and_init_tools( g_hWnd_Main, path_drop, NULL, NULL );

		while( GetTickCount() < count + (1000 * 0.5f) ){}
	}

	{
		RECT rc;
		GetClientRect ( g_hWnd_Main, &rc );
		InvalidateRect( g_hWnd_Main, &rc, false );
		UpdateWindow  ( g_hWnd_Main );
	}

	MSG msg;

	while( GetMessage( &msg, NULL, 0, 0 ) )
	{
		TranslateMessage( &msg );//キーボード使用可能
		DispatchMessage(  &msg );//制御をWindowsに戻す
	}

term:

	if( g_strm_xa2 ){ if( g_strm_xa2->stream_finalize( 0.1f, 30, 3 ) ) SAFE_DELETE( g_strm_xa2 ); }

	Interface_release    (); dlog_c( "released interface" );

	ScopeEvent_Release   ();

	SAFE_DELETE( g_path_dlg_build );
	SAFE_DELETE( g_path_dlg_proj  );
	SAFE_DELETE( g_path_dlg_tune  );
	SAFE_DELETE( g_strm_woi       );						         
	SAFE_DELETE( g_freq           );
	SAFE_DELETE( g_alte           );
	SAFE_DELETE( g_pxtn           );
	SAFE_DELETE( g_ptn_bldr       );
	SAFE_DELETE( g_midi_in        ); 

	UndoEvent_Release    (); dlog_c( "released undo event"     );

	SAFE_DELETE( g_dxdraw );

	Menu_HistoryW_Release(); dlog_c( "released menu history"   );
	JapaneseTable_Release(); dlog_c( "released japanese table" );

	dlog_c( "*OK*" );

	pxDebugLog_release   ();

	SAFE_DELETE( xa2_keep );

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR _lpCmdLine, int nCmdShow) {
    WCHAR *lpCmdLine = GetCommandLineW();
    if (__argc == 1) { // avoids GetCommandLineW bug that does not always quote the program name if no arguments
        do { ++lpCmdLine; } while (*lpCmdLine);
    } else {
        BOOL quoted = lpCmdLine[0] == L'"';
        ++lpCmdLine; // skips the " or the first letter (all paths are at least 1 letter)
        while (*lpCmdLine) {
            if (quoted && lpCmdLine[0] == L'"') { quoted = FALSE; } // found end quote
            else if (!quoted && lpCmdLine[0] == L' ') {
                // found an unquoted space, now skip all spaces
                do { ++lpCmdLine; } while (lpCmdLine[0] == L' ');
                break;
            }
            ++lpCmdLine;
        }
    }
    return wWinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}
