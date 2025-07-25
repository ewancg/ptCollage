﻿
#include "./pxtn.h"

#ifdef pxINCLUDE_OGGVORBIS

#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>

#include "./pxtnPulse_Oggv.h"

typedef struct
{
    char*   p_buf; // ogg vorbis-data on memory.s
    int32_t size ; //
    int32_t pos  ; // reading position.
}
OVMEM;


// 4 callbacks below:

static size_t _mread( void *p, size_t size, size_t nmemb, void* p_void )
{
	OVMEM *pom = (OVMEM*)p_void;

	if( !pom                  ) return -1;
	if( pom->pos >= pom->size ) return  0;
	if( pom->pos == -1        ) return  0;

	int32_t left = pom->size - pom->pos;

	if( (int32_t)(size * nmemb) >= left )
	{
		memcpy( p, &pom->p_buf[ pom->pos ], pom->size - pom->pos );
		pom->pos = pom->size;
		return left / size;
	}

	memcpy( p, &pom->p_buf[ pom->pos ], nmemb * size );
	pom->pos += (int32_t)( nmemb * size );

	return nmemb;
}

static int _mseek( void* p_void, ogg_int64_t offset, int32_t mode )
{
	int32_t newpos;
	OVMEM *pom = (OVMEM*)p_void;

	if( !pom || pom->pos < 0 )       return -1;
	if( offset < 0 ){ pom->pos = -1; return -1; }

	switch( mode )
	{
	case SEEK_SET: newpos =             (int32_t)offset; break;
	case SEEK_CUR: newpos = pom->pos  + (int32_t)offset; break;
	case SEEK_END: newpos = pom->size + (int32_t)offset; break;
	default: return -1;
	}
	if( newpos < 0 ) return -1;

	pom->pos = newpos;

	return 0;
}

static long _mtell( void* p_void )
{
	OVMEM* pom = (OVMEM*)p_void;
	if( !pom ) return -1;
	return pom->pos;
}

static int _mclose_dummy( void* p_void )
{
	OVMEM* pom = (OVMEM*)p_void;
	if( !pom ) return -1;
	return 0;
}


bool pxtnPulse_Oggv::_SetInformation()
{
	bool b_ret = false;

	OVMEM ovmem;
	ovmem.p_buf = _p_data;
	ovmem.pos   =       0;
	ovmem.size  = _size  ;

	// set callback func.
	ov_callbacks   oc; 
    oc.read_func  = _mread       ;
    oc.seek_func  = _mseek       ;
    oc.close_func = _mclose_dummy;
    oc.tell_func  = _mtell       ;
  
	OggVorbis_File vf;
	
	vorbis_info*  vi;

	switch( ov_open_callbacks( &ovmem, &vf, NULL, 0, oc ) )
	{
	case OV_EREAD     : goto End; //{printf("A read from media returned an error.\n");exit(1);} 
	case OV_ENOTVORBIS: goto End; //{printf("Bitstream is not Vorbis data. \n");exit(1);}
	case OV_EVERSION  : goto End; //{printf("Vorbis version mismatch. \n");exit(1);}
	case OV_EBADHEADER: goto End; //{printf("Invalid Vorbis bitstream header. \n");exit(1);}
	case OV_EFAULT    : goto End; //{printf("Internal logic fault; indicates a bug or heap/stack corruption. \n");exit(1);}
	default:
		break;
    }

    vi = ov_info( &vf,-1 );

	_ch      = vi->channels;
	_sps2    = vi->rate    ;
	_smp_num = (int32_t)ov_pcm_total( &vf, -1 );
    
    // end.
    ov_clear( &vf );

	b_ret = true;

End:
    return b_ret;

}


/////////////////
// global
/////////////////


pxtnPulse_Oggv::pxtnPulse_Oggv( pxtnIO_r io_read, pxtnIO_w io_write, pxtnIO_seek io_seek, pxtnIO_pos io_pos )
{
	_set_io_funcs( io_read, io_write, io_seek, io_pos );

	_p_data  = NULL;
	_ch      = 0;
	_sps2    = 0;
	_smp_num = 0;
	_size    = 0;
}

pxtnPulse_Oggv::~pxtnPulse_Oggv()
{
	Release();
}

void pxtnPulse_Oggv::Release()
{
	if( _p_data ) free( _p_data ); _p_data = NULL;
	_ch      = 0;
	_sps2    = 0;
	_smp_num = 0;
	_size    = 0;
}

pxtnERR pxtnPulse_Oggv::ogg_read( void* desc )
{
	pxtnERR res = pxtnERR_VOID;

	if( !_data_get_size( desc, &_size ) || !_size ){ res = pxtnERR_desc_r; goto term; }
	if( !( _p_data = (char*)malloc( _size ) )     ){ res = pxtnERR_memory; goto term; }
	if( !_io_read( desc, _p_data, 1, _size )      ){ res = pxtnERR_desc_r; goto term; }
	if( !_SetInformation()                        ) goto term;

	res = pxtnOK;
term:

	if( res != pxtnOK )
	{
		if( _p_data ) free( _p_data ); _p_data = NULL; _size = 0;
	}
	return res;
}

pxtnERR pxtnPulse_Oggv::Decode( pxtnPulse_PCM * p_pcm ) const
{
	pxtnERR res = pxtnERR_VOID;

	OggVorbis_File vf;
	vorbis_info*   vi;
	ov_callbacks   oc; 

	OVMEM ovmem;

	ovmem.p_buf = _p_data;
	ovmem.pos   =       0;
	ovmem.size  = _size  ;

    // set callback func.
    oc.read_func  = _mread       ;
    oc.seek_func  = _mseek       ;
    oc.close_func = _mclose_dummy;
    oc.tell_func  = _mtell       ;
  
    switch( ov_open_callbacks( &ovmem, &vf, NULL, 0, oc ) )
	{
	case OV_EREAD     : res = pxtnERR_ogg; goto term; //{printf("A read from media returned an error.\n");exit(1);} 
	case OV_ENOTVORBIS: res = pxtnERR_ogg; goto term; //{printf("Bitstream is not Vorbis data. \n");exit(1);}
	case OV_EVERSION  : res = pxtnERR_ogg; goto term; //{printf("Vorbis version mismatch. \n");exit(1);}
	case OV_EBADHEADER: res = pxtnERR_ogg; goto term; //{printf("Invalid Vorbis bitstream header. \n");exit(1);}
	case OV_EFAULT    : res = pxtnERR_ogg; goto term; //{printf("Internal logic fault; indicates a bug or heap/stack corruption. \n");exit(1);}
	default: break;
    }

    vi    = ov_info( &vf,-1 );
	
    static int32_t current_section;
    current_section = {};
    static char pcmout[ 4096 ];
    memset(&pcmout, 0x00, sizeof(pcmout)); //take 4k out of the data segment, not the stack
	{
        static int32_t smp_num;
        smp_num = (int32_t)ov_pcm_total( &vf, -1 );
        static uint32_t bytes;
        bytes = {};

		bytes = vi->channels * 2 * smp_num;

		res = p_pcm->Create( vi->channels, vi->rate, 16, smp_num );
		if( res != pxtnOK ) goto term;
	}
    // decode..
	{
		int32_t ret = 0;
		uint8_t  *p  = (uint8_t*)p_pcm->get_p_buf_variable();
		do
		{
			ret = ov_read( &vf, pcmout, 4096, 0, 2, 1, &current_section );
			if( ret > 0 ) memcpy( p, pcmout, ret ); //fwrite( pcmout, 1, ret, of );
			p += ret;
		}
		while( ret );
	}
    
    // end.
    ov_clear( &vf );

	res = pxtnOK;

term:
    return res;
}

bool pxtnPulse_Oggv::GetInfo( int* p_ch, int* p_sps, int* p_smp_num )
{
	if( !_p_data ) return false;

	if( p_ch      ) *p_ch      = _ch     ;
	if( p_sps     ) *p_sps     = _sps2   ;
	if( p_smp_num ) *p_smp_num = _smp_num;

	return true;
}

int32_t  pxtnPulse_Oggv::GetSize() const
{
	if( !_p_data ) return 0;
	return sizeof(int32_t)*4 + _size;
}



bool pxtnPulse_Oggv::ogg_write( void* desc ) const
{
	bool    b_ret  = false;

	if( !_io_write( desc, _p_data, 1,_size ) ) goto End;

	b_ret = true;
End:
	return b_ret;
}

bool pxtnPulse_Oggv::pxtn_write( void* desc ) const
{
	if( !_p_data ) return false;

	if( !_io_write( desc, &_ch     , sizeof(int32_t),    1 ) ) return false;
	if( !_io_write( desc, &_sps2   , sizeof(int32_t),    1 ) ) return false;
	if( !_io_write( desc, &_smp_num, sizeof(int32_t),    1 ) ) return false;
	if( !_io_write( desc, &_size   , sizeof(int32_t),    1 ) ) return false;
	if( !_io_write( desc,  _p_data , sizeof(char   ),_size ) ) return false;

	return true;
}

bool pxtnPulse_Oggv::pxtn_read( void* desc )
{
	bool  b_ret  = false;

	if( !_io_read( desc, &_ch     , sizeof(int32_t), 1 ) ) goto End;
	if( !_io_read( desc, &_sps2   , sizeof(int32_t), 1 ) ) goto End;
	if( !_io_read( desc, &_smp_num, sizeof(int32_t), 1 ) ) goto End;
	if( !_io_read( desc, &_size   , sizeof(int32_t), 1 ) ) goto End;

	if( !_size ) goto End;

	if( !( _p_data = (char*)malloc( _size ) ) ) goto End;
	if( !_io_read( desc, _p_data, 1,      _size )   ) goto End;

	b_ret = true;
End:

	if( !b_ret )
	{
		if( _p_data ) free( _p_data ); _p_data = NULL; _size = 0;
	}

	return b_ret;
}

bool pxtnPulse_Oggv::copy_from ( const pxtnPulse_Oggv* src )
{
	pxtnData::copy_from( src );

	Release();
	if( !src->_p_data ) return true;

	if( !( _p_data = (char*)malloc( src->_size ) ) ) return false;
	memcpy( _p_data, src->_p_data, src->_size );

	_ch      = src->_ch     ;
	_sps2    = src->_sps2   ;
	_size    = src->_size   ;
	_smp_num = src->_smp_num;

	return true;
}

#endif
