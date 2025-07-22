#include <pxStdDef.h>

int32_t  ActiveTone_set_unit ( int32_t u, float cur_x, float freq_rate, int32_t pan_vol, int32_t* velos, int32_t pan_time );
int32_t  ActiveTone_set_woice( int32_t w );
void ActiveTone_change_freq  ( int32_t id, float freq_rate );
void ActiveTone_stop         ( int32_t id );
void ActiveTone_AllStop      ();
