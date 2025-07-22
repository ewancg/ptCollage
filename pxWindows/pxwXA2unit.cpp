
#include "./pxwXA2unit.h"

static void _set_pcm_format_16bps( WAVEFORMATEX* p_fmt, int32_t ch_num, int32_t sps )
{
	p_fmt->cbSize          =               0;
	p_fmt->wFormatTag      = WAVE_FORMAT_PCM;
	p_fmt->nChannels       = (WORD )ch_num;
	p_fmt->nSamplesPerSec  = (DWORD)sps   ;
	p_fmt->wBitsPerSample  = (WORD )pxBITPERSAMPLE16;
	p_fmt->nBlockAlign     = p_fmt->nChannels   * p_fmt->wBitsPerSample / 8;
	p_fmt->nAvgBytesPerSec = p_fmt->nBlockAlign * p_fmt->nSamplesPerSec;
}

void pxwXA2unit::release()
{
	if( _xa2_src ) _xa2_src->DestroyVoice(); _xa2_src = NULL;
	SAFE_DELETE( _pcm );
}

pxwXA2unit::pxwXA2unit()
{
	_xa2_src = NULL;
	memset( &_fmt    , 0, sizeof(_fmt    ) );
	memset( &_xa2_buf, 0, sizeof(_xa2_buf) );
	_pcm     = NULL;
}

pxwXA2unit::~pxwXA2unit()
{
	release();
}

bool pxwXA2unit::create_16bps( IXAudio2 *p_xa2, int32_t ch_num, int32_t sps, const void* p_buf, int32_t smp_num )
{
	bool b_ret = false;
	if( !p_xa2 ) return false;
	if( _pcm   ) return false;

	if( !( _pcm = new pxPlayPCM() ) || !_pcm->init() ) goto term;

	if( !( _pcm->set_sample_16bps( ch_num, sps, p_buf, smp_num ) ) ) goto term;

	_set_pcm_format_16bps( &_fmt, ch_num, sps );

	if( FAILED( p_xa2->CreateSourceVoice( &_xa2_src, &_fmt, 0, XAUDIO2_DEFAULT_FREQ_RATIO, NULL, NULL, NULL ) ) ) goto term;

	b_ret = true;
term:
	if( !b_ret ) release();

	return b_ret;
}

bool pxwXA2unit::test_make( IXAudio2 *p_xa2, int32_t ch_num, int32_t sps, float sec )
{
	bool b_ret = false ;

	if( !p_xa2 ) return false;
	if( _pcm   ) return false;

	if( !( _pcm = new pxPlayPCM() ) || !_pcm->init() ) goto term;
	if( !_pcm->make_test_sample_16bps( ch_num, sps, sec ) ) goto term;

	_set_pcm_format_16bps( &_fmt, ch_num, sps );

	if( FAILED( p_xa2->CreateSourceVoice( &_xa2_src, &_fmt, 0, XAUDIO2_DEFAULT_FREQ_RATIO, NULL, NULL, NULL ) ) ) goto term;

	b_ret = true;
term:
	if( !b_ret ) release();

	return b_ret;
}

bool pxwXA2unit::play( bool b_loop )
{
	if( !_xa2_src ) return false;

	_xa2_src->Stop();
	_xa2_src->FlushSourceBuffers();

	_xa2_buf.AudioBytes =              _pcm->get_data_bytes  ();
	_xa2_buf.pAudioData = (const BYTE*)_pcm->get_data_pointer();
	_xa2_buf.Flags      = XAUDIO2_END_OF_STREAM;
	_xa2_buf.LoopCount  = b_loop ? XAUDIO2_LOOP_INFINITE : 0;

	if( FAILED( _xa2_src->SubmitSourceBuffer( &_xa2_buf ) ) ) return false;
	if( FAILED( _xa2_src->Start( 0, XAUDIO2_COMMIT_NOW  ) ) ) return false;

	return true;
}

bool pxwXA2unit::stop( bool b_force )
{
	if( !_xa2_src ) return false;

	if( b_force )
	{
		_xa2_src->Stop();
		_xa2_src->FlushSourceBuffers();
	}
	else
	{
		_xa2_src->ExitLoop();
	}

	return true;
}


bool pxwXA2unit::volume    ( float v )
{
	if( !_xa2_src ) return false;
	_xa2_src->SetVolume( v, XAUDIO2_COMMIT_NOW );
	return true;
}
