#include <windows.h>
#include <stdio.h>

#include <shlwapi.h>
#pragma comment(lib, "shlwapi")


// #include "../SampleTune/TuneUnit.h"
// #include "../SampleTune/TuneDelay.h"
// #include "../SampleTune/TuneMaster.h"
// #include "../SampleTune/TuneText.h"
// #include "../SampleTune/cls_EventList.h"

#include "Project.h"

// #include "interface/if_ProjectPanel.h"


// 初期値
/*
#define _DUMMY_BPS              16
#define _DUMMY_SPS           44100
#define _DUMMY_CHANNELNUM        2

// プロジェクトの初期化
void Project_Initialize( void )
{

	TuneText_Set_Name( "no name" );
	TuneText_Set_Comment( "" );
	TuneUnit_RemoveAll();
	TuneDelay_Reset();
	TuneMaster_Reset();
}
*/

///////////////////////////
// file io
///////////////////////////
/*

// プロジェクト情報(36byte) ================
typedef struct{
	char           xx_name[MAX_PROJECTNAME];

	float          xx_beat_tempo;
	unsigned short xx_quarter_clock;
	unsigned short xx_beat_num;
	unsigned short xx_beat_note;
	unsigned short xx_meas_num;

	unsigned short xx_channel_num;
	unsigned short xx_bps;
	unsigned long  xx_sps;

}_PROJECTSTRUCT;

// 書き込み(プロジェクト)
BOOL Project_WriteFile( FILE *fp )
{
	_PROJECTSTRUCT	     prjc;
	long                 size;
	long                 beat_note, beat_num, quarter_clock, meas_num;
	float                beat_tempo;

	if( !fp ) return FALSE;

	TuneMaster_Get( &beat_note, &beat_num, &beat_tempo, &quarter_clock, &meas_num );
	memset( &prjc, 0,  sizeof(_PROJECTSTRUCT) );
	memcpy( prjc.xx_name, TuneText_Get_Name(), MAX_PROJECTNAME );

	prjc.xx_meas_num      = (unsigned short)meas_num;
	prjc.xx_quarter_clock = (unsigned short)quarter_clock;
	prjc.xx_beat_num      = (unsigned short)beat_num;
	prjc.xx_beat_note     = (unsigned short)beat_note;
	prjc.xx_beat_tempo    =                 beat_tempo;
	prjc.xx_bps           = (unsigned short)_DUMMY_BPS;
	prjc.xx_sps           = (unsigned long )_DUMMY_SPS;
	prjc.xx_channel_num   = (unsigned short)_DUMMY_CHANNELNUM;

	// prjc ----------
	size = sizeof( _PROJECTSTRUCT );
	fwrite( &size, sizeof(unsigned long),  1, fp );
	fwrite( &prjc, size,                   1, fp );

	return TRUE;
}

// 読み込み(プロジェクト)
BOOL Project_ReadFile( FILE *fp )
{
	_PROJECTSTRUCT prjc;
	char name[MAX_PROJECTNAME];
	long beat_note, beat_num, quarter_clock, meas_num;
	long size;
	float beat_tempo;

	if( !fp ) return FALSE;

	memset( &prjc,   0, sizeof( _PROJECTSTRUCT ) );
	if( fread( &size, 4,                        1, fp ) != 1 ) return FALSE;
	if( fread( &prjc, sizeof( _PROJECTSTRUCT ), 1, fp ) != 1 ) return FALSE;

	memset( name, 0, MAX_PROJECTNAME );
	memcpy( name, prjc.xx_name, MAX_PROJECTNAME );
	meas_num      = prjc.xx_meas_num;
	beat_note     = prjc.xx_beat_note;
	beat_num      = prjc.xx_beat_num;
	beat_tempo    = prjc.xx_beat_tempo;
	quarter_clock = prjc.xx_quarter_clock;

	TuneText_Set_Name( name );
	TuneMaster_Set( beat_note, beat_num, beat_tempo, quarter_clock, meas_num );

	return TRUE;
}

*/

// 「編集されています保存しますか？」
/*
フラグを倒す時

・セーブした
・初期化した

フラグを立てる時

・イベントを追加/削除
・ペースト/消去/削除
・プロジェクトを変更
・ユニットを追加/削除

*/
