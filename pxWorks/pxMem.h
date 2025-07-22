// '16/05/17 pxMem.

#ifndef pxMem_H
#define pxMem_H

#include <pxStdDef.h>

bool pxMem_zero_alloc( void** pp, uint32_t byte_size );
bool pxMem_free      ( void** pp );
bool pxMem_zero      ( void*  p , uint32_t byte_size );

#endif
