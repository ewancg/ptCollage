
#include "ptConfig_Stream.h"

                           //0123456789abcdef0123456789abcdef
static char*   _code      = "ptConfig_Stream_20160818        "; // xaudio2, bps
static int32_t _code_size = 32;


ptConfig_Stream:: ptConfig_Stream( int32_t def_sps, int32_t def_ch_num, float def_buf_sec )
{
	sps     = _def_sps     = def_sps    ;
	ch_num  = _def_ch_num  = def_ch_num ;
	buf_sec = _def_buf_sec = def_buf_sec;
}

bool ptConfig_Stream::write( pxDescriptor *desc ) const
{
	bool b_ret = false;

	if( !desc->w_asfile( _code   , sizeof(char    ), _code_size ) ) goto End;
	if( !desc->w_asfile( &sps    , sizeof(sps    ),          1 ) ) goto End;
	if( !desc->w_asfile( &ch_num , sizeof(ch_num ),          1 ) ) goto End;
	if( !desc->w_asfile( &buf_sec, sizeof(buf_sec),          1 ) ) goto End;

	b_ret = true;
End:

	return b_ret;
}

void ptConfig_Stream::set_default()
{
	sps     = _def_sps    ;
	ch_num  = _def_ch_num ;
	buf_sec = _def_buf_sec;
}

bool ptConfig_Stream::read( pxDescriptor *desc )
{
	char code[ 64 ] = {0};
	bool b_ret = false;

	if( !desc->r( code     , sizeof(char), _code_size ) ) goto End;
	if( memcmp( code, _code, _code_size )               ) goto End;
	if( !desc->r( &sps    , sizeof(sps    ), 1 )        ) goto End;
	if( !desc->r( &ch_num , sizeof(ch_num ), 1 )        ) goto End;
	if( !desc->r( &buf_sec, sizeof(buf_sec), 1 )        ) goto End;

	b_ret = true;
End:

	if( !b_ret ) set_default();

	return b_ret;
}
