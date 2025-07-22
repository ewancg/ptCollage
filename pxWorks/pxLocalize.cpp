﻿
#ifdef _WIN32
#else
#include <stdio.h>
#endif

#include <pxwrAppEtc.h>

#include "./pxStrT.h"
#include "./pxMem.h"

#include "./pxLocalize.h"

typedef struct
{
	const char*  _region_name;
	const TCHAR* _dir_sub    ;
}
_REGION_LANGUAGE;

#define _DIR_REGION_SIZE 64

static const _REGION_LANGUAGE _region_tbl[ pxLOCALREGION_num ] =
{
	{"ENGLISH"  , _T("en"     )}, // pxLOCALREGION_en
	{"JAPANESE" , _T("ja"     )}, // pxLOCALREGION_ja
	{"CHINESE"  , _T("zh-Hans")}, // pxLOCALREGION_cn
	{"FRENCH"   , _T("fr"     )}, // pxLOCALREGION_fr
	{"ITALIAN"  , _T("it"     )}, // pxLOCALREGION_it
	{"GERMAN"   , _T("de"     )}, // pxLOCALREGION_de
	{"SPANISH"  , _T("es"     )}, // pxLOCALREGION_es
	{"PORTUGUES", _T("pt"     )}, // pxLOCALREGION_po
	{"RUSSIAN"  , _T("ru"     )}, // pxLOCALREGION_ru
};


void pxLocalize::_release()
{
	_b_init = false;
	pxStrT_free( &_dir_localize );
	pxStrT_free( &_dir_region   );
}

void pxLocalize::_update_dir_region()
{
	if( !_b_init ) return;
	TCHAR dir[ pxBUFSIZE_PATH ] = {};
#ifdef UNICODE
	_stprintf_s( dir, _T("%s/%s.lproj"), _dir_localize, _region_tbl[ _region ]._dir_sub );
#else
	sprintf    ( dir     "%s/%s.lproj" , _dir_localize, _region_tbl[ _region ]._dir_sub );
#endif
	pxStrT_free         ( &_dir_region      );
	pxStrT_copy_allocate( &_dir_region, dir );
}

pxLocalize::pxLocalize()
{
	_b_init       = false            ;
	_region       = pxLOCALREGION_num;
	_dir_localize = NULL             ;
	_dir_region   = NULL             ;
}

pxLocalize::~pxLocalize()
{
	_release();
}

bool pxLocalize::init( const TCHAR* dir_localize )
{
	if( _b_init || !dir_localize ) return false;

	if( !pxStrT_copy_allocate( &_dir_localize    , dir_localize     ) ) goto term;

//	if( !pxMem_zero_alloc( (void**)&_dir_region, _DIR_REGION_SIZE * sizeof(TCHAR) ) ) goto term;

	switch( pxwrAppEtc_Local() )
	{
	case  0: _region = pxLOCALREGION_en ; break;
	case  1: _region = pxLOCALREGION_ja ; break;
	case  2: _region = pxLOCALREGION_cn ; break;
	case  3: _region = pxLOCALREGION_fr ; break;
	case  4: _region = pxLOCALREGION_it ; break;
	case  5: _region = pxLOCALREGION_de ; break;
	case  6: _region = pxLOCALREGION_es ; break;
	case  7: _region = pxLOCALREGION_pt ; break;
	case  8: _region = pxLOCALREGION_ru ; break;
	default: _region = pxLOCALREGION_num; break;
	}
	_b_init = true;
	_update_dir_region();
term:
	if( !_b_init ) _release();
	return _b_init;
}

bool pxLocalize::read( pxDescriptor* desc )
{
	if( !desc ) return false;

	bool                    b_ret             = false;
	const _REGION_LANGUAGE* p_rgn             = NULL ;
	char                    region_name[ 32 ] = {   };

	int32_t len = 0;
	if( !desc->r( &len       , sizeof(len),   1 ) ) goto term;
	if( !desc->r( region_name,           1, len ) ) goto term;

	for( int i = 0; i < pxLOCALREGION_num; i++ )
	{
		if( !strcmp( _region_tbl[ i ]._region_name, region_name ) )
		{
			_region = (pxLOCALREGION)i  ;
			p_rgn   = &_region_tbl[  i ];
			break;
		}
	}
	if( !p_rgn ) goto term;

	_update_dir_region();

	b_ret = true;
term:

	return b_ret;
}

bool pxLocalize::set( pxLOCALREGION region )
{
	if( !_b_init ) return false;
	if( region < 0 || region >= pxLOCALREGION_num ) return false;

	bool   b_ret = false;
	_region = region;
	_update_dir_region();

	return true;
}

bool pxLocalize::set_and_write( pxLOCALREGION region, pxDescriptor* desc )
{
	if( !_b_init || !desc ) return false;
	if( !set( region )    ) return false; 

	bool  b_ret = false;
	const _REGION_LANGUAGE* p_rgn = &_region_tbl[ _region ];

	int32_t len = strlen( p_rgn->_region_name );
	if( !desc->w_asfile( &len               , sizeof(len),   1 ) ) goto term;
	if( !desc->w_asfile( p_rgn->_region_name,           1, len ) ) goto term;

	b_ret = true;
term:
	return b_ret;
}

pxLOCALREGION pxLocalize::get() const{ return _region; }

const TCHAR* pxLocalize::get_region_dir() const
{
	if( !_b_init ) return NULL;
	return _dir_region;
}


