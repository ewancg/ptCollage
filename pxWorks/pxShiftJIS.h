// '16/08/30 pxShiftJIS. from pxUTF8.

#ifndef pxShiftJIS_H
#define pxShiftJIS_H

#include <pxStdDef.h>

bool pxShiftJIS_check_code_byte(                      uint32_t code,    int32_t* p_byte );
bool pxShiftJIS_append_code    ( char*       str_dst, uint32_t code                     );

bool pxShiftJIS_get_top_code   ( uint32_t* p_code, const char* str_src, int32_t* p_byte );
bool pxShiftJIS_check_size     ( const char* str_src, int32_t* p_size, bool b_permit_illegal );

bool pxShiftJIS_free           ( char** pp );
bool pxShiftJIS_copy_allocate  ( char** pp, const char* str_src );

#endif
