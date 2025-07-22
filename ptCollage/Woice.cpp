﻿
#include <pxtnPulse_Oggv.h>

#include <pxtnService.h>
extern pxtnService*    g_pxtn    ;

#include <pxtonewinXA2.h>
extern pxtonewinXA2*   g_strm_xa2;

#include <pxtonewinWoice.h>
extern pxtonewinWoice* g_strm_woi;

#include <pxwUTF8.h>
#include <pxwWindowRect.h>
#include <pxwFilePath.h>

#include <pxwPathDialog.h>
extern pxwPathDialog* g_path_dlg_wav;
extern pxwPathDialog* g_path_dlg_ogg;
extern pxwPathDialog* g_path_dlg_ptv;
extern pxwPathDialog* g_path_dlg_ptn;
extern pxwPathDialog* g_path_dlg_add;

#include <pxwAlteration.h>
extern pxwAlteration* g_alte;

#include <pxShiftJIS.h>
#include <pxStr.h>
#include <pxMem.h>
#include <pxDebugLog.h>

#include "resource.h"

#include "../Generic/Japanese.h"

#include "../pxtoneTool/pxtoneTool.h"
#include "../ptConfig/ptConfig.h"

#include "./ptCollage.h"

#include "interface/if_WoiceTray.h"
#include "interface/if_UnitTray.h"

#include "WoiceFocus.h"
#include "UndoEvent.h"

#define _BUFNUM_DELETE_WOICE (pxtnMAX_TUNEWOICENAME + 100)

static const TCHAR* _default_material_folder = _T("my_material");

extern HINSTANCE    g_hInst;
extern HWND         g_hWnd_Main;
extern TCHAR        g_dir_module[];

int32_t GetCompileVersion( int32_t *p1, int32_t *p2, int32_t *p3, int32_t *p4 );
bool    InquireOperation();

#ifdef px64BIT
INT_PTR
#else
BOOL CALLBACK
#endif
dlg_YesNo( HWND hWnd, UINT msg, WPARAM w, LPARAM l );

#ifdef px64BIT
INT_PTR
#else
BOOL CALLBACK
#endif
dlg_Woice( HWND hWnd, UINT msg, WPARAM w, LPARAM l );


static const pxFile2* _ref_file_profile = NULL;

void Woice_init( const pxFile2* file_profile )
{
	_ref_file_profile = file_profile;
}




// パス→ユニット名
static bool _MakeWoiceName( pxtnWoice *p_w, const TCHAR* path )
{
	TCHAR   name_t   [ MAX_PATH ] = {0};
	char*   sjis_name = NULL;
	int32_t sjis_size;

	_tcscpy            ( name_t, PathFindFileName( path ) );
	PathRemoveExtension( name_t );

#ifdef UNICODE
	if( !pxwUTF8_wide_to_sjis( name_t, &sjis_name, &sjis_size ) ) return false;
#else
	if( !( sjis_name = pxStr_copy_allocate( name_t ) ) ) return false;
	sjis_size = pxShiftJIS_check_size( sjis_name );
#endif

	int32_t  bytes = 0;
	uint32_t code  = 0;
	char*    p     = sjis_name;

	for( sjis_size = 0; sjis_size < pxtnMAX_TUNEWOICENAME; sjis_size += bytes, p += bytes )
	{
		if( *p == 0x00 ) break;
		if( !pxShiftJIS_get_top_code( &code, p, &bytes ) ) goto term;
		if( sjis_size + bytes > pxtnMAX_TUNEWOICENAME ) break;
	}
	*p = 0x00;

	p_w->set_name_buf( sjis_name, sjis_size );

term:

	if( sjis_name ) free( sjis_name );
	return true;
}

bool Woice_Replace( int32_t old_pos, int32_t new_pos )
{
	if( !InquireOperation() ) return false;

	if( old_pos != new_pos )
	{
		g_pxtn->Woice_Replace( old_pos, new_pos );
		if( g_pxtn->evels->Record_Value_Replace( EVENTKIND_VOICENO, old_pos, new_pos ) )
		{
			UndoEvent_Replace_VoiceNo( old_pos, new_pos );
		}
		if_WoiceTray_RedrawAllName( NULL );
		WoiceFocus_Set( new_pos );

		g_alte->set();
	}
	return true;
}

static const TCHAR *_PathFindExt( const TCHAR *path )
{
	int32_t l = (int32_t)_tcslen( path );
	for( int32_t i = l-1; i >= 0; i-- )
	{
		if( path[ i ] == '.' ) return &path[ i ];
	}
	return path;
}

static pxtnWOICETYPE _CheckFileType_byExt( const TCHAR* path )
{
	if( !_tcsicmp( _PathFindExt( path ), _T(".wav"    ) ) ) return pxtnWOICE_PCM ;
	if( !_tcsicmp( _PathFindExt( path ), _T(".ptvoice") ) ) return pxtnWOICE_PTV ;
	if( !_tcsicmp( _PathFindExt( path ), _T(".ptnoise") ) ) return pxtnWOICE_PTN ;
	if( !_tcsicmp( _PathFindExt( path ), _T(".ogg"    ) ) ) return pxtnWOICE_OGGV;
	return pxtnWOICE_None;
}

bool Woice_Add( HWND hWnd, const TCHAR* path )
{
	int32_t w = g_pxtn->Woice_Num();
	if( w >= g_pxtn->Woice_Max() ){ Japanese_MessageBox( hWnd, _T("full voice"), _T("error"), MB_OK|MB_ICONEXCLAMATION ); return false; }

	bool           b_ret    = false;
	pxtnERR        pxtn_err = pxtnERR_VOID;
	FILE*          fp       = _tfopen( path, _T("rb") );
	
	if( !fp )
	{
		Japanese_MessageBox( hWnd, _T("can't open"), _T("error"), MB_OK|MB_ICONEXCLAMATION ); return false;
	}

	if( g_pxtn->Woice_read( w, fp, _CheckFileType_byExt( path ) ) != pxtnOK )
	{
		Japanese_MessageBox( hWnd, _T("add voice"), _T("error"), MB_OK|MB_ICONEXCLAMATION ); goto term;
	}

	if( !_MakeWoiceName( g_pxtn->Woice_Get_variable( w ), path ) ){ Japanese_MessageBox( hWnd, _T("make voice-name" ), _T("error"), MB_OK|MB_ICONEXCLAMATION ); goto term; }

	pxtn_err = g_pxtn->Woice_ReadyTone( w );
	if( pxtn_err != pxtnOK )
	{
		Japanese_MessageBox( hWnd, _T("ready voice-work"), _T("error"), MB_OK|MB_ICONEXCLAMATION ); goto term;
	}

	if_WoiceTray_RedrawName( w );

	b_ret = true;
term:
	if( fp ) fclose( fp );

	return b_ret;
}


int32_t Woice_Dialog_Add()
{
	if( !InquireOperation() ) return -1;

	static HEARSELECTDIALOGSTRUCT hear = {0};

	int w  = g_pxtn->Woice_Num();
	if( w >= g_pxtn->Woice_Max() )
	{
		Japanese_MessageBox( g_hWnd_Main, _T("full voice"), _T("error"), MB_OK|MB_ICONEXCLAMATION );
		return -1;
	}

	// ファイル選択 =============================================
	hear.visible_flags  =
		HEARSELECTVISIBLE_PCM  |
		HEARSELECTVISIBLE_PTV  |
		HEARSELECTVISIBLE_PTN  |
		HEARSELECTVISIBLE_OGGV |
		HEARSELECTVISIBLE_ADDUNIT;

	hear.b_japanese = Japanese_Is();

	if( !g_path_dlg_add->get_last_path( hear.path_selected, MAX_PATH ) )
	{
		_stprintf_s( hear.dir_default, MAX_PATH, _T("%s\\%s"), g_dir_module, _default_material_folder );
	}

	{ ptConfig cfg( _ref_file_profile, ptcDEFAULT_SPS, ptcDEFAULT_CH_NUM, ptcDEFAULT_BUF_SEC ); cfg.load(); g_strm_woi->set_sps( cfg.strm->sps ); }

	if( !pxtoneTool_HearSelect_Dialog( g_hWnd_Main, &hear ) ) return -1;

	g_path_dlg_add->set_loaded_path( hear.path_selected );

	if( !Woice_Add( g_hWnd_Main, hear.path_selected )       ) return -1;

	if_WoiceTray_RedrawName( w );

	pxtnWoice *p_w = g_pxtn->Woice_Get_variable( w );
	switch( p_w->get_type() )
	{
	case pxtnWOICE_PCM :
	case pxtnWOICE_OGGV:
	case pxtnWOICE_PTN : if( hear.b_loop ) p_w->get_voice_variable( 0 )->voice_flags |= PTV_VOICEFLAG_WAVELOOP;
	}

	if_WoiceTray_JustScroll();

	// ユニットを追加
	if( hear.b_add_unit )
	{ 
		if( g_pxtn->Unit_AddNew() )
		{
			int32_t     u            = g_pxtn->Unit_Num() - 1;
			pxtnUnit*   p_unit       = g_pxtn->Unit_Get_variable( u );

			char        unit_name[ pxtnMAX_TUNEUNITNAME + 1 ] = {0};
			char*       pd           = unit_name;
			const char* p_woice_name = p_w->get_name_buf( NULL );
			const char* ps           = p_woice_name;

			int32_t     bytes        = 0;
			int32_t     name_size    = 0;
			uint32_t    code         = 0;

			strcpy( unit_name, "u-" ); pd += 2;
			for( name_size = 2; name_size < pxtnMAX_TUNEUNITNAME; name_size += bytes, ps += bytes, pd += bytes )
			{
				pxShiftJIS_get_top_code( &code, ps, &bytes );
				memcpy( pd, ps, bytes );
				if( name_size + bytes > pxtnMAX_TUNEUNITNAME ) break;
			}

			p_unit->set_name_buf( unit_name, name_size );

			if_UnitTray_RedrawAllName( NULL );

			g_pxtn->evels->Record_Add_i( 0, (unsigned char)u, EVENTKIND_VOICENO, (int32_t)w );
		}
		else
		{
			Japanese_MessageBox( g_hWnd_Main, _T("can't add unit"), _T("error"), MB_OK|MB_ICONEXCLAMATION );
		}
	}

	g_alte->set();

	return w;
}

void Woice_Dialog_Edit( int32_t w )
{
	if( !InquireOperation() ) return;

	if( DialogBoxParam( g_hInst, _T("DLG_WOICE"), g_hWnd_Main, dlg_Woice, (LPARAM)w ) )
	{
		if_WoiceTray_RedrawAllName( NULL );
		g_alte->set();
	}
}



void Woice_Dialog_Change( int32_t w )
{
	bool b_ret = false;

	InquireOperation();

	pxtnWoice* p_w      = g_pxtn->Woice_Get_variable( w );
	bool       bBeatFit = false;

	static HEARSELECTDIALOGSTRUCT hear = {0};

	hear.visible_flags  =
		HEARSELECTVISIBLE_PCM |
		HEARSELECTVISIBLE_PTV |
		HEARSELECTVISIBLE_PTN |
		HEARSELECTVISIBLE_OGGV;

	switch( p_w->get_type() )
	{
	case pxtnWOICE_PCM :
	case pxtnWOICE_OGGV: if( p_w->get_voice( 0 )->voice_flags & PTV_VOICEFLAG_BEATFIT  ) bBeatFit    = true;
	case pxtnWOICE_PTN : if( p_w->get_voice( 0 )->voice_flags & PTV_VOICEFLAG_WAVELOOP ) hear.b_loop = true;
		break;
	}

	// ファイル選択 =============================================
	_stprintf_s( hear.dir_default, MAX_PATH, _T("%s\\%s"), g_dir_module, _default_material_folder );

	{ ptConfig cfg( _ref_file_profile, ptcDEFAULT_SPS, ptcDEFAULT_CH_NUM, ptcDEFAULT_BUF_SEC ); cfg.load(); g_strm_woi->set_sps( cfg.strm->sps ); }

	if( !pxtoneTool_HearSelect_Dialog( g_hWnd_Main, &hear ) ) return;

	{
		FILE* fp = _tfopen( hear.path_selected, _T("rb") ); if( !fp ) goto End;
		if( p_w->read( fp, _CheckFileType_byExt( hear.path_selected ) ) != pxtnOK )
		{
			fclose( fp ); goto End;
		}
		fclose( fp );
	}

	switch( p_w->get_type() )
	{
	case pxtnWOICE_PCM :
	case pxtnWOICE_OGGV: if( bBeatFit    ) p_w->get_voice_variable( 0 )->voice_flags |= PTV_VOICEFLAG_BEATFIT ;
	case pxtnWOICE_PTN : if( hear.b_loop ) p_w->get_voice_variable( 0 )->voice_flags |= PTV_VOICEFLAG_WAVELOOP;
		break;
	}

	_MakeWoiceName( p_w, hear.path_selected );
	if_WoiceTray_RedrawAllName( NULL );

	g_alte->set();

	b_ret = true;
End:

	if( !b_ret )
	{
		WoiceFocus_Set( 0 );
		Japanese_MessageBox( g_hWnd_Main, _T("reload voice"), _T("error"), MB_OK|MB_ICONEXCLAMATION );
		g_alte->set();
	}
	else if( g_pxtn->Woice_ReadyTone( w ) != pxtnOK )
	{
		Japanese_MessageBox( g_hWnd_Main, _T("ready voice"), _T("error"), MB_OK|MB_ICONEXCLAMATION );
	}
}

bool Woice_Dialog_Export( int32_t w )
{
	if( !InquireOperation() ) return false;

	bool     b_ret                    = false;
	wchar_t* p_wide                   = NULL ;
	TCHAR    path_dst    [ MAX_PATH ] = { 0 };
	TCHAR    path_def_dir[ MAX_PATH ] = { 0 };
	char     woice_name  [ pxtnMAX_TUNEWOICENAME + 1 ] = {0};

	const pxtnWoice* p_w = g_pxtn->Woice_Get( w ); if( !p_w ) return false;

	dlog_c( "expt woice" );

	// ファイル選択 =============================================

	{
		TCHAR*         p_name_t = NULL  ;	
		pxwPathDialog* path_dlg = NULL  ;

		switch( p_w->get_type() )
		{
		case pxtnWOICE_PCM : path_dlg = g_path_dlg_wav; dlog_c( "expt pcm" ); break;
		case pxtnWOICE_PTV : path_dlg = g_path_dlg_ptv; dlog_c( "expt ptv" ); break;
		case pxtnWOICE_PTN : path_dlg = g_path_dlg_ptn; dlog_c( "expt ptn" ); break;
		case pxtnWOICE_OGGV: path_dlg = g_path_dlg_ogg; dlog_c( "expt ogg" ); break;
		default            :                            dlog_c( "expt unk" ); return false;
		}

		int32_t name_size = 0;
		strcpy( woice_name, p_w->get_name_buf( &name_size ) );
		pxwFilePath_ncomp_x_sjis( woice_name );
#ifdef UNICODE
		if( !pxwUTF8_sjis_to_wide( woice_name, &p_wide, NULL ) ) goto term;
		p_name_t = p_wide;
#else
		p_name_t = woice_name;
#endif
		// set woice name.
		if( path_dlg->get_last_path( path_dst, MAX_PATH ) )
		{
			PathRemoveFileSpec( path_dst );
			if( _tcslen( path_dst ) != 3 )
				_tcscat( path_dst, _T("\\") );
			_tcscat( path_dst, p_name_t );
		}

		dlog_c( "expt w call(get save path)" );
		if( !path_dlg->dialog_save( g_hWnd_Main, path_dst, p_name_t ) ){ b_ret = true; goto term; }
		dlog_c( "expt w called(get save path)" );
	}


	dlog_c( "expt w exporting" );
	{
		FILE* fp = _tfopen( path_dst, _T("wb") ); if( !fp ) goto term;

		switch( p_w->get_type() )
		{
		case pxtnWOICE_PCM : if( !p_w->get_voice( 0 )->p_pcm ->write     ( fp, NULL ) ){ fclose( fp ); goto term; } break;
		case pxtnWOICE_PTV : if( !p_w->                        PTV_Write ( fp, NULL ) ){ fclose( fp ); goto term; } break;
		case pxtnWOICE_PTN : if( !p_w->get_voice( 0 )->p_ptn ->write     ( fp, NULL ) ){ fclose( fp ); goto term; } break;
		case pxtnWOICE_OGGV:
#ifdef pxINCLUDE_OGGVORBIS
			if( !p_w->get_voice ( 0 )->p_oggv->ogg_write( fp ) ){ fclose( fp ); goto term; }
#else
			fclose( fp ); goto term;
#endif
			break;
		}
		fclose( fp );
	}
	dlog_c( "expt w exported" );

	b_ret = true;
term:
	pxMem_free( (void**)&p_wide );

	if( !b_ret ) Japanese_MessageBox( g_hWnd_Main, _T("export"), _T("error"), MB_OK|MB_ICONEXCLAMATION );
	return b_ret;
}

bool Woice_Dialog_Remove( int32_t w )
{
	if( !InquireOperation() ) return false;

	bool b_ret = false;

	const pxtnWoice *p_w = g_pxtn->Woice_Get( w );
	if( !p_w )
	{
		Japanese_MessageBox( g_hWnd_Main, _T("no voice"), _T("error"), MB_OK|MB_ICONEXCLAMATION );
		return false;
	}

	int32_t     num      = g_pxtn->evels->get_Count( EVENTKIND_VOICENO, (int32_t)w );
	TCHAR*      p_name_t = NULL ;
	wchar_t*    p_wide   = NULL ;
	int32_t     buf_size =     0;
	const char* p_c      = p_w->get_name_buf( &buf_size );
	TCHAR       str[ _BUFNUM_DELETE_WOICE ] = {0};

#ifdef UNICODE
	if( !pxwUTF8_sjis_to_wide( p_c, &p_wide, NULL ) ) goto term;
	p_name_t = p_wide;
#else
	p_name_t = p_c;
#endif

	if( Japanese_Is() ) _stprintf_s( str, _BUFNUM_DELETE_WOICE, _T("音源 \'%s\' を削除します\r\n\r\n%d 個の該当音源イベントを削除します"), p_name_t, num );
	else                _stprintf_s( str, _BUFNUM_DELETE_WOICE, _T("Remove : '%s\'\r\n\r\nand I delete %d voice-no events."             ), p_name_t, num );
	if( !DialogBoxParam( g_hInst, _T("DLG_YESNO"), g_hWnd_Main, dlg_YesNo, (LPARAM)str ) ) goto term;

	g_strm_xa2->Voice_order_stop_all();

	g_pxtn->Woice_Remove( w );
	if( g_pxtn->evels->Record_Value_Omit( EVENTKIND_VOICENO, w ) ) UndoEvent_ReleaseUndoRedo();
	if_WoiceTray_RedrawAllName( NULL );
	WoiceFocus_Set( 0 );
	g_alte->set();

	b_ret = true;
term:
	pxMem_free( (void**)&p_wide );
	return b_ret;
}

