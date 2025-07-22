#include "./CursorKeyCtrl.h"

CursorKeyCtrl::CursorKeyCtrl()
{
	_mode  = CursorKey_none;
	_idx   =              0;
	_p_tgt = NULL          ;
}

void CursorKeyCtrl::clear()
{
	_mode  = CursorKey_none;
	_idx   =              0;
	_p_tgt = NULL          ;
}

void CursorKeyCtrl::set  ( CursorKeyMode mode, int32_t idx, const void* p_tgt )
{
	_mode  = mode ;
	_idx   = idx  ;
	_p_tgt = p_tgt;
}

CursorKeyMode CursorKeyCtrl::get( int32_t* p_idx ) const
{
	if( p_idx ) *p_idx = _idx;
	return _mode;
}

const void* CursorKeyCtrl::get_tgt() const
{
	return _p_tgt;
}
