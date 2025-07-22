//
//  pxwFile.h
//  Created by Daisuke Amaya on 11/08/11.
//  Copyright 2011 Pixel. All rights reserved.
//

#ifndef pxwFile_H
#define pxwFile_H

bool  pxwFile_set_master_base_dir( const TCHAR* dir_base );
bool  pxwFile_set_master_cmmn_dir( const TCHAR* dir_cmmn );
bool  pxwFile_set_trns_dir       ( const TCHAR* dir_trns );

bool  pxwFile_cerate_trns_sub_dir ( const TCHAR* dir_name );

const TCHAR *pxwFile_get_master_base_dir();
const TCHAR *pxwFile_get_master_cmmn_dir();
const TCHAR *pxwFile_get_trns_dir       ();

void  pxwFile_release    ();
bool  pxwFile_delete     ( const TCHAR *path );
bool  pxwFile_trns_delete( const TCHAR *dir_name, const TCHAR *file_name );

bool pxwFile_make_real_path_master_base( TCHAR** p_real_path, const TCHAR *dir_name, const TCHAR *file_name );
bool pxwFile_make_real_path_master_cmmn( TCHAR** p_real_path, const TCHAR *dir_name, const TCHAR *file_name );
bool pxwFile_make_real_path_trns       ( TCHAR** p_real_path, const TCHAR *dir_name, const TCHAR *file_name );

#endif
