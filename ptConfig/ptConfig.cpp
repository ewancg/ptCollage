﻿
#include "ptConfig.h"

static const TCHAR* _dir_name          = _T("pxtone-config");
static const TCHAR* _name_strm_operate = _T("strm_operate.conf");
static const TCHAR* _name_font         = _T("font.conf"        );
static const TCHAR* _name_midi         = _T("midi.conf"        );

ptConfig:: ptConfig( const pxFile2* app_file_profile, int32_t sps, int32_t ch_num, float buf_sec )
{
	_ref_app_file_profile = app_file_profile;

	strm = new ptConfig_Stream( sps, ch_num, buf_sec );
	font = new ptConfig_Font  ();
	midi = new ptConfig_MIDI  ();
}

ptConfig::~ptConfig()
{
	if( strm ) delete strm;
	if( font ) delete font;
	if( midi ) delete midi;
}

void ptConfig::set_default()
{
	strm->set_default();
	font->set_default();
	midi->set_default();
}

bool ptConfig::save() const
{
	bool          b_ret = false;
	pxDescriptor* desc  = NULL ;

	if( !_ref_app_file_profile->open_w( &desc, _dir_name, _name_strm_operate, NULL ) ) goto term;
	if( !strm->write( desc ) ) goto term;
	SAFE_DELETE( desc ); 

	if( !_ref_app_file_profile->open_w( &desc, _dir_name, _name_font        , NULL ) ) goto term;
	if( !!font->write( desc ) ) return false;
	SAFE_DELETE( desc ); 
								           
	if( !_ref_app_file_profile->open_w( &desc, _dir_name, _name_midi        , NULL ) ) goto term;
	if( !midi->write( desc ) ) return false;
	SAFE_DELETE( desc );

	b_ret = true;
term:
	SAFE_DELETE( desc );

	return b_ret;
}

bool ptConfig::load()
{
	bool          b_ret = false;
	pxDescriptor* desc  = NULL ;

	if( !_ref_app_file_profile->open_r( &desc, _dir_name, _name_strm_operate, NULL ) ) goto term;
	if( !strm->read( desc ) ) goto term;
	SAFE_DELETE( desc );

	if( !_ref_app_file_profile->open_r( &desc, _dir_name, _name_font        , NULL ) ) goto term;
	if( !font->read( desc ) ) goto term;
	SAFE_DELETE( desc );

	if( !_ref_app_file_profile->open_r( &desc, _dir_name, _name_midi        , NULL ) ) goto term;
	if( !midi->read( desc ) ) goto term;
	SAFE_DELETE( desc );

	b_ret = true;
term:
	SAFE_DELETE( desc );

	return b_ret;
}
