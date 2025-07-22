#include <pxStdDef.h>

bool ScopeEvent_Initialize(   int32_t max_event_num );
void ScopeEvent_Release();

int32_t ScopeEvent_Copy(         int32_t clock1, int32_t clock2, bool* p_bEventKinds );
int32_t ScopeEvent_Clear(        int32_t clock1, int32_t clock2 );
int32_t ScopeEvent_ChangeVolume( int32_t clock1, int32_t clock2, int32_t e, int32_t value  );
int32_t ScopeEvent_Delete(       int32_t clock1, int32_t clock2 );
int32_t ScopeEvent_Paste(        int32_t clock,  int32_t time  , bool* p_bEventKinds );
int32_t ScopeEvent_Insert(       int32_t clock,  int32_t time   );
int32_t ScopeEvent_Cut(          int32_t clock1, int32_t clock2 );

