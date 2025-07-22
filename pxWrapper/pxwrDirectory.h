// '16/01/29 pxwrDirectory.
// '16/09/07 + pxwrDirectory_copy_folders()

#ifndef pxwrDirectory_H
#define pxwrDirectory_H

#include <pxStdDef.h>

bool pxwrDirectory_find        ( const TCHAR *path_dir, const TCHAR *ext, bool b_sub_dir, pxfunc_find_path func, void *user );
bool pxwrDirectory_copy_folders( const TCHAR *path_dst, const TCHAR* path_src );
bool pxwrDirectory_create      ( const TCHAR *path_dir );

#endif
