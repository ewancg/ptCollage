
#include "./ptConfig_Build.h"

                           //0123456789abcdef0123456789abcdef
static char*   _code      = "ptConfig_Build_20120321         ";
static int32_t _code_size = 32;

void ptConfig_Build::set_default()
{
	strm->set_default();

	b_mute        = false;
	scope_mode    = BUILDSCOPEMODE_TOPLAST;
	sec_playtime  = 0;
	sec_extrafade = 0;
	volume        = 1.0f;
}

ptConfig_Build::ptConfig_Build( int32_t def_sps, int32_t def_ch_num )
{
	strm = new ptConfig_Stream( def_sps, def_ch_num, 0.1f );
	ptConfig_Build::set_default();
}

ptConfig_Build::~ptConfig_Build()
{
	if( strm ) delete strm;
}

bool ptConfig_Build::write( pxDescriptor* desc ) const
{
	bool b_ret = false;

	if( !desc->w_asfile( _code, sizeof(char), _code_size ) ) goto End;

	if( !strm->write( desc ) ) goto End;

	if( !desc->w_asfile( &b_mute       , sizeof(b_mute       ), 1 ) ) goto End;
	if( !desc->w_asfile( &scope_mode   , sizeof(scope_mode   ), 1 ) ) goto End;
	if( !desc->w_asfile( &sec_playtime , sizeof(sec_playtime ), 1 ) ) goto End;
	if( !desc->w_asfile( &sec_extrafade, sizeof(sec_extrafade), 1 ) ) goto End;
	if( !desc->w_asfile( &volume       , sizeof(volume       ), 1 ) ) goto End;

	b_ret = true;
End:
	return b_ret;
}

bool ptConfig_Build::read( pxDescriptor* desc )
{
	char code[ 64 ] = {};
	bool b_ret      = false;

	if( !desc->r( code,     sizeof(char), _code_size ) ) goto End;
	if( memcmp( code, _code,               _code_size ) ) goto End;

	if( !strm->read( desc ) ) goto End;

	if( !desc->r( &b_mute       , sizeof(b_mute       ), 1 ) ) goto End;
	if( !desc->r( &scope_mode   , sizeof(scope_mode   ), 1 ) ) goto End;
	if( !desc->r( &sec_playtime , sizeof(sec_playtime ), 1 ) ) goto End;
	if( !desc->r( &sec_extrafade, sizeof(sec_extrafade), 1 ) ) goto End;
	if( !desc->r( &volume       , sizeof(volume       ), 1 ) ) goto End;

	b_ret = true;
End:
	if( !b_ret ) set_default();

	return b_ret;
}
