#include <pxStdDef.h>

// ボリュームモード
enum VOLUMEMODE
{
	VOLUMEMODE_Velocity = 0,
	VOLUMEMODE_Pan_Volume  ,
	VOLUMEMODE_Pan_Time    ,
	VOLUMEMODE_Volume      ,
	VOLUMEMODE_Portament   ,
	VOLUMEMODE_VoiceNo     ,
	VOLUMEMODE_GroupNo     ,
	VOLUMEMODE_Tuning      ,
};

enum VOLUMEBUTTON
{
	VOLUMEBUTTON_Switch = 0,
	VOLUMEBUTTON_Velocity  ,
	VOLUMEBUTTON_Pan_Volume,
	VOLUMEBUTTON_Pan_Time  ,
	VOLUMEBUTTON_Volume    ,
	VOLUMEBUTTON_KeyPorta  ,
	VOLUMEBUTTON_VoiceNo   ,
	VOLUMEBUTTON_GroupNo   ,
	VOLUMEBUTTON_Tuning    ,
	VOLUMEBUTTON_unknown   ,
};

void              if_VolumePanel_SetRect( const fRECT *rc_view );
VOLUMEBUTTON if_VolumePanel_GetHitButton( float cur_x, float cur_y );
bool              if_VolumePanel_SetHitButton( VOLUMEBUTTON button );

void if_InitVolumePanel();
void if_SetVolumeMode( VOLUMEMODE volume_mode );
VOLUMEMODE if_GetVolumeMode();

void if_PutVolumePanel(  void );


void if_VolumeSwitch_SetRect( const fRECT *rc_view );
bool if_VolumePanel_IsUse(  void );
void if_SetUseVolume( bool bUse );
void if_PutVolumeSwitch();
