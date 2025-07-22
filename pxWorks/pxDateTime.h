// '14/01/08 pxDateTime.h
#ifndef pxDateTime_H
#define pxDateTime_H


#include <pxStdDef.h>

typedef struct
{
	uint16_t Y;
	uint8_t  M;
	uint8_t  D;
	uint8_t  h;
	uint8_t  m;
	uint8_t  s;
}
pxDATETIME;

double pxDateTime_compare_seconds( const pxDATETIME *p1, const pxDATETIME *p2 );
double pxDateTime_compare_days   ( const pxDATETIME *p1, const pxDATETIME *p2 );
bool   pxDateTime_get_now        ( pxDATETIME *p_datetime );

#endif
