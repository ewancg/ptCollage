
#include <pxtnService.h>
extern pxtnService *g_pxtn;

static int32_t _focus   = 0;

////////////////////
// focus
////////////////////
void WoiceFocus_Set( int32_t index )
{
	if( index >= 0 && index < g_pxtn->Woice_Num() ) _focus = index;
}

int32_t WoiceFocus_Get()
{
	if( !g_pxtn->Woice_Num() ) return -1;
	return _focus;
}

bool WoiceFocus_Shift( bool bNext )
{
	if( bNext )
	{
		if( _focus < g_pxtn->Woice_Num() -1 ) _focus++;
		else                                  return false;
	}
	else
	{
		if( _focus > 0                      ) _focus--;
		else                                  return false;
	}

	return true;
}
