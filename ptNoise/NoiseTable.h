#ifndef NoiseTable_H
#define NoiseTable_H

#include <pxStdDef.h>

#include <pxtnPulse_Noise.h>

#define MAX_NOISETABLEUNIT     4
#define MAX_NOISETABLEENVELOPE 3

typedef struct
{
	int32_t ch;
	int32_t sps;
	int32_t bps;
}
SAMPLINGQUALITY;

void NoiseTable_SetDefaultQuality( SAMPLINGQUALITY *p_quality );
void NoiseTable_SetDefault( pxtnPulse_Noise *p_ptn );
void NoiseTable_CopyUnit  ( pxNOISEDESIGN_UNIT *p_dst, pxNOISEDESIGN_UNIT *p_src );

#endif
