// '16/09/12 pxStrT.h
// '16/09/13 + pxStrT_size()

#include <pxStdDef.h>

bool    pxStrT_copy_allocate( TCHAR** pp_dst, const TCHAR *src                );
bool    pxStrT_copy_allocate( TCHAR** pp_dst, const TCHAR *src, int32_t extra );
bool    pxStrT_copy         ( TCHAR* dst, const TCHAR* src );
void    pxStrT_free         ( TCHAR **pp       );
int32_t pxStrT_size         ( const TCHAR* str );
bool    pxStrT_compare      ( const TCHAR *str1, const TCHAR *str2, int32_t num, int32_t* p_res );
bool    pxStrT_is_different ( const TCHAR* a, const TCHAR* b   );
