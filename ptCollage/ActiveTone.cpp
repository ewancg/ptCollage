
#include <pxtnPulse_Frequency.h>
extern pxtnPulse_Frequency* g_freq    ;

#include <pxtnService.h>
extern pxtnService*         g_pxtn    ;

#include <pxtonewinXA2.h>
extern pxtonewinXA2*        g_strm_xa2;

#include "./interface/if_BaseField.h"

#include "./UnitFocus.h"


int ActiveTone_set_unit( int32_t u, float cur_x, float freq_rate, int32_t pan_vol, int32_t* velos, int32_t pan_time )
{

	if( u < 0 ) u = UnitFocus_Get();
	if( !g_pxtn->Unit_Get( u ) ) return -1;

	int32_t woice_idx = if_BaseField_Event_get_Value( cur_x, u, EVENTKIND_VOICENO );

	if( freq_rate == -1 )
	{
		int32_t val = if_BaseField_Event_get_Value( cur_x, u, EVENTKIND_KEY );
		if( val ) freq_rate = g_freq->Get( val - 0x6000 );
		else      freq_rate = 1;
	}

	int32_t val = if_BaseField_Event_get_Value( cur_x, u, EVENTKIND_TUNING );
	if( val ) freq_rate *= *( (float*)( &val ) );

	const pxtnWoice     *p_w   = g_pxtn->Woice_Get( woice_idx ); if( !p_w  ) return -1;
	const pxtnVOICEUNIT *p_vc  = p_w->get_voice( 0 );            if( !p_vc ) return -1;
	bool                b_loop = false;
	if( p_vc->voice_flags & PTV_VOICEFLAG_WAVELOOP ) b_loop = true ;

	pxtnxaVOICE_ORDER odr; memset( &odr, 0, sizeof(odr) );
	odr.p_woice   = p_w      ;
	odr.b_loop    = b_loop   ;
	odr.freq_rate = freq_rate;
	odr.vol_pan   = pan_vol  ;
	odr.time_pan  = pan_time ;
	for( int i = 0; i < pxtnMAX_UNITCONTROLVOICE; i++ ) odr.velos[ i ] = velos[ i ];

	return g_strm_xa2->Voice_order_new( &odr );
}

int ActiveTone_set_woice( int32_t woice_idx )
{
	const pxtnWoice     *p_w   = g_pxtn->Woice_Get( woice_idx ); if( !p_w  ) return -1;
	const pxtnVOICEUNIT *p_vc  = p_w->get_voice   (         0 ); if( !p_vc ) return -1;
	bool                b_loop = false;

	if( p_vc->voice_flags & PTV_VOICEFLAG_WAVELOOP ) b_loop = true ;

	float freq_rate = 1;

	pxtnxaVOICE_ORDER odr; memset( &odr, 0, sizeof(odr) );
	odr.p_woice   = p_w   ;
	odr.b_loop    = b_loop;
	odr.freq_rate =      1;
	odr.vol_pan   =     -1;
	odr.time_pan  =     -1;
	for( int i = 0; i < pxtnMAX_UNITCONTROLVOICE; i++ ) odr.velos[ i ] = -1;

	return g_strm_xa2->Voice_order_new( &odr );
}

void ActiveTone_change_freq( int32_t id, float freq_rate ){ g_strm_xa2->Voice_order_freq( id, freq_rate ); }
void ActiveTone_stop       ( int32_t id                  ){ g_strm_xa2->Voice_order_stop( id, false );     }
void ActiveTone_AllStop    (                             ){ g_strm_xa2->Voice_order_stop_all();            }
