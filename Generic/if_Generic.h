#include <pxStdDef.h>

#include "../pxWindows/pxwDx09Draw.h"

void  if_gen_init       ( pxwDx09Draw *dxdraw, int32_t surf_tenkey );
void  if_gen_num6       ( float x, float y, int32_t value, uint32_t flag );
void  if_gen_num6_clip  ( float x, float y, int32_t value, uint32_t flag, const fRECT *p_rc_clip );
void  if_gen_float6_clip( float x, float y, float f,                      const fRECT *p_rc_clip );
float if_gen_float_n    ( float x, float y, float f,                    int32_t under_zero );
float if_gen_float_n    ( float x, float y, float f, int32_t over_zero, int32_t under_zero );

void  if_gen_tile_h     ( const fRECT *p_rc_fld, const fRECT *p_rc_img, int32_t rect_num, int32_t offset, int32_t surf );
void  if_gen_tile_v     ( const fRECT *p_rc_fld, const fRECT *p_rc_img, int32_t rect_num, int32_t offset, int32_t surf );

bool  if_gen_splash     ( HWND hwnd, pxwDx09Draw *dxdraw, int32_t surf, float mag );
