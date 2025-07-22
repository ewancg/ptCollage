
#include <pxtnPulse_Frequency.h>
extern pxtnPulse_Frequency *g_freq;

#include <pxtnEvelist.h>
#include <pxtnWoice.h>

#include "../Generic/pxMidiIn.h"

#include "./ActiveTone.h"

typedef struct
{
	bool b_on;
	int32_t  id  ;
}
_MIDIINPUT;

static _MIDIINPUT _midi_inputs[ pxMidiIn_KEY_NUM ];
static bool  _b_init     = false;
static bool  _b_velo     = true ;
static float _key_tuning =  1.0f;

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
	ActiveTone_AllStop ();

	_MIDIINPUT *p = _midi_inputs;
	for( int i = 0; i < pxMidiIn_KEY_NUM; i++, p++ )
	{
		if( p->b_on )
		{
			ActiveTone_stop( p->id );
			p->b_on = false;
		}
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
				ActiveTone_stop( p->id );
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

				int32_t velos[ pxtnMAX_UNITCONTROLVOICE ] = {0};

				for( int i = 0; i < pxtnMAX_UNITCONTROLVOICE; i++ ) velos[ i ] = _b_velo ? velo : -1;

				p->id = ActiveTone_set_unit( -1, -1, freq_rate, -1, velos, -1 );
				if( p->id != -1 ) p->b_on = true;
			}
		}
	}
}

