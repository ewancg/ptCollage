
#include <pxtnPulse_Frequency.h>
extern pxtnPulse_Frequency *g_freq;

#include <pxtnEvelist.h>

#include "../Generic/pxMidiIn.h"

#include "./WoiceUnit.h"
extern WoiceUnit* g_vunit;

typedef struct
{
	bool    b_on;
	int32_t id  ;
}
_MIDIINPUT;

static _MIDIINPUT _midi_inputs[ pxMidiIn_KEY_NUM ] = {0};
static bool       _b_init     = false;
static bool       _b_velo     = true ;
static float      _key_tuning = 1.0f ;

void MidiInput_Init()
{
	_b_init = true;
	memset( _midi_inputs, 0, sizeof(_midi_inputs) );
	pxMidiIn_ClearVelos();
}

void MidiInput_Reset( bool b_velo, float key_tuning )
{
	if( !_b_init ) return;

	_b_velo     = b_velo    ;
	_key_tuning = key_tuning;

	pxMidiIn_ClearVelos();
	g_vunit->strm_Off_All();

	_MIDIINPUT *p = _midi_inputs;
	for( int i = 0; i < pxMidiIn_KEY_NUM; i++, p++ )
	{
		if( p->b_on ){ g_vunit->strm_OFF( p->id, false ); p->b_on = false; }
	}
}

void MidiInput_Procedure()
{
	_MIDIINPUT *p = _midi_inputs;

	for( int i = 0; i < pxMidiIn_KEY_NUM; i++, p++ )
	{
		if( p->b_on )
		{
			if( !pxMidiIn_get_velo( i ) )
			{
				g_vunit->strm_OFF( p->id, false );
				p->b_on = false;
			}
		}
		else
		{
			unsigned char velo = pxMidiIn_get_velo( i );
			if( velo )
			{
				float freq_rate = g_freq->Get(  i * 0x100  - EVENTDEFAULT_BASICKEY );

				freq_rate *= _key_tuning;
				if( _b_velo ) p->id = g_vunit->strm_ON( freq_rate, velo );
				else          p->id = g_vunit->strm_ON( freq_rate       );
				if( p->id != -1 ) p->b_on = true;
			}
		}
	}
}
