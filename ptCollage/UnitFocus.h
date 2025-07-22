#include <pxStdDef.h>

void UnitFocus_Set( int32_t index, bool bOperated );
int32_t  UnitFocus_Get();
bool UnitFocus_Shift( bool bNext );
int32_t  UnitFocus_CountFocusedOrOperated();
bool UnitFocus_IsFocusedOrOperated( int32_t u );
bool UnitFocus_IsFocusOnly();

