#include <pxStdDef.h>
bool pxwUTF8_sjis_to_utf8( const char*    p_src, char**    pp_dst, int32_t* p_dst_size );
bool pxwUTF8_sjis_to_wide( const char*    p_src, wchar_t** pp_dst, int32_t* p_dst_num  );
bool pxwUTF8_utf8_to_wide( const char*    p_src, wchar_t** pp_dst, int32_t* p_dst_num  );
bool pxwUTF8_utf8_to_sjis( const char*    p_src, char**    pp_dst, int32_t* p_dst_size );
bool pxwUTF8_wide_to_utf8( const wchar_t* p_src, char**    pp_dst, int32_t* p_dst_size );
bool pxwUTF8_wide_to_sjis( const wchar_t* p_src, char**    pp_dst, int32_t* p_dst_size );

bool pxwUTF8_code_utf8_to_wide( uint32_t code_src, wchar_t* p_code_dst );


