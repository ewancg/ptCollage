// '16/01/30 pxPath.

#ifndef pxPath_H
#define pxPath_H

enum pxPathMode
{
	pxPathMode_unknown = 0,
	pxPathMode_UTF8    ,
	pxPathMode_ShiftJIS,
	pxPathMode_UTF16LE ,
	pxPathMode_auto    ,
};

void  pxPath_setMode               ( pxPathMode mode   );

const TCHAR *pxPath_find_ext       ( const TCHAR *path );
const TCHAR *pxPath_find_filename  ( const TCHAR *path );
const TCHAR *pxPath_remove_filename(       TCHAR *path );

#endif
