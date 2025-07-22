// '11/04/20 pxStr.

#ifndef pxStr_H
#define pxStr_H

void pxStr_free( char **pp );

bool pxStr_sjis_is_2byte       ( char c    );
void pxStr_sjis_RemoveLastBlank( char *buf );
int  pxStr_sjis_CopyWithLength ( char *p_dst, const char *p_src, int len );

int  pxStr_csv_ReadAlloc( const char *p_src, char **pp_dst, int size_dst, unsigned char sep );
int  pxStr_csv_Read     ( const char *p_src, char  * p_dst, int size_dst, unsigned char sep );

bool pxStr_copy_allocate( char** pp_dst, const char *str );
bool pxStr_is_different ( const char* a, const char* b   );

bool pxStr_copy_without_ext( char* p_dst, const char* p_src, int buf_size );

#endif
