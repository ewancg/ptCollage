// '17/01/10 ptVoice.h

#ifndef ptVoice_H
#define ptVoice_H

#include <pxtn.h>
#include <pxtnMax.h>

#define ptvDEFAULT_SPS       44100
#define ptvDEFAULT_CH_NUM        2
#define ptvDEFAULT_BUF_SEC   0.03f

#define ptvCOODINATERESOLUTION  256//400//200
#define ptvDEFAULT_ENVESPS_old  100
#define ptvDEFAULT_ENVESPS_new 1000
#define ptvMAX_ENVELOPEPOINT     31

#define ptvMAX_WORKTEMP           6

#define ptvORGANKEY_KEYNUM       88

#define ptvFIXNUM_WAVE_POINT     31 // 倍音ゼロを追加した時を考慮し、１減らしてある
#define ptvFIXNUM_ENVE_POINT (ptvMAX_ENVELOPEPOINT + pxtnMAX_RELEASEPOINT)

#define ptvTUNING_ACCURACY   10000 //max is 10000000

enum SURFACES
{
	SURF_LOADING     = 1,
	SURF_PARTS          ,
	SURF_WAVE_SCREEN    ,
	SURF_ENVE_SCREEN    ,
	SURF_WAVE_mini_0    ,
	SURF_WAVE_mini_1    ,
	SURF_ENVE_mini_0    ,
	SURF_ENVE_mini_1    ,
};

void ptv_put_value  ( float x, float y, int32_t value, const fRECT* rc_clip );
void ptv_put_value  ( float x, float y, int32_t value );
void ptv_put_envesec( float x, float y, int32_t value, const fRECT* rc_clip );

#endif
