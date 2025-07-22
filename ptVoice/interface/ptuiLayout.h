// '17/92/26 ptuiLayout.

#define scroll_button_size 16

#define ORGANKEY_ofs_x   scroll_button_size
#define ORGANKEY_Y          0
#define ORGANKEY_W         80
#define ORGANKEY_min_H    272

#define WORKTEMP_W        232
#define WORKTEMP_H         48
#define WORKTEMP_x2_ofs  (ORGANKEY_W + scroll_button_size)
#define WORKTEMP_Y          0

#define HEADER_H           48
#define HEADER_X            0
#define HEADER_x2_ofs    (WORKTEMP_W + WORKTEMP_x2_ofs)
#define HEADER_Y            0

#define RACK_X              0
#define RACK_Y           (HEADER_Y + HEADER_H + 0)
#define RACK_W            576
#define RACK_H            144
#define RACKHALF_H         56

#define SCREEN_WAVEMINI_W  64
#define SCREEN_WAVEMINI_H  64

#define SCREEN_ENVEMINI_W 148
#define SCREEN_ENVEMINI_H  64

// wave..
#define WAVEFRAME_X   8
#define WAVEFRAME_Y   (HEADER_H + 56)
#define WAVEFRAME_W    528// 280
#define WAVEFRAME_H    296// 168

#define WAVEHEAD_X       8
#define WAVEHEAD_Y       (HEADER_H + 56)
#define WAVEHEAD_W       544
#define WAVEHEAD_H        24

#define SINEVOLUME_X     8
#define SINEVOLUME_Y     (WAVEFRAME_Y + WAVEFRAME_H)
#define SINEVOLUME_W     344 //216//232

#define WAVEPRESET_X     (SINEVOLUME_X+SINEVOLUME_W+SCROLLBUTTONSIZE)
#define WAVEPRESET_Y     (WAVEFRAME_Y + WAVEFRAME_H)
#define WAVEPRESET_W     184
#define WAVEPRESET_H      32


// envelopes..
#define ENVEFRAME_X   8
#define ENVEFRAME_Y   (HEADER_H + 56)
#define ENVEFRAME_W    528//280
#define ENVEFRAME_H    296//168

#define ENVEHEAD_X       8
#define ENVEHEAD_Y       (HEADER_H + 56)
#define ENVEHEAD_W       544
#define ENVEHEAD_H        24

#define RELEASETIME_X     ENVEFRAME_X
#define RELEASETIME_Y    (ENVEFRAME_Y + ENVEFRAME_H)
#define RELEASETIME_W    232
#define RELEASETIME_H     24

#define LOGOPANEL_Y      (TUNING_Y+TUNING_H)
#define LOGOPANEL_H      32

#define VELOCITYVOLUME_x2_ofs 0
#define VELOCITYVOLUME_y2_ofs 0
#define VELOCITYVOLUME_W  96
#define VELOCITYVOLUME_H  48

#define PTVOICE_WORK_W    560

#define PTVOICE_W         (PTVOICE_WORK_W + VELOCITYVOLUME_W)
#define PTVOICE_H         (WAVEPRESET_Y + WAVEPRESET_H*2)

#define ORGANKEY_KEYHEIGHT  8

#define SCREEN_WAVE_EXTRA 256
#define SCREEN_WAVE_MAIN  256
#define SCREEN_WAVE_W     (SCREEN_WAVE_MAIN+SCREEN_WAVE_EXTRA)
#define SCREEN_WAVE_H     256

#define SCREEN_ENVE_W     512
#define SCREEN_ENVE_H     256
