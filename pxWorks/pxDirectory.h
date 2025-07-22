// '16/01/29 pxDirectory.

#ifndef pxDirectory_H
#define pxDirectory_H

#include <pxStdDef.h>

bool pxDirectory_file_find   ( const TCHAR* path_dir, const TCHAR *ext, bool b_sub_dir, pxfunc_find_path func, void *user );
bool pxDirectory_copy_folders( const TCHAR* path_dst, const TCHAR* path_src );

#endif
