
#include <stdio.h>
#include <tchar.h>

#include "./pxtonewinXA2.h"

bool pxtonewinXA2::tune_order_start    ( const pxtnVOMITPREPARATION *p_prep )
{
	if( !_b_init ) return false;
	if( !p_prep  ) return false;

	_tn_mtx->lock();
	_tn_odr.flags &= ~pxtnxaTUNE_ORDERFLAG_stop;
	_tn_odr.flags |=  pxtnxaTUNE_ORDERFLAG_prep|pxtnxaTUNE_ORDERFLAG_loop|pxtnxaTUNE_ORDERFLAG_unit_mute|pxtnxaTUNE_ORDERFLAG_volume;
	_tn_odr.prep   = *p_prep;
	_tn_odr.volume = p_prep->master_volume;

	if( p_prep->flags & pxtnVOMITPREPFLAG_loop      ) _tn_odr.b_loop      = true ;
	else                                              _tn_odr.b_loop      = false;
	if( p_prep->flags & pxtnVOMITPREPFLAG_unit_mute ) _tn_odr.b_unit_mute = true ;
	else                                              _tn_odr.b_unit_mute = false;

	_tn_b_sampling = true;
	_tn_mtx->unlock();
	return true;
}

bool pxtonewinXA2::tune_order_volume   ( float volume )
{
	if( !_b_init ) return false;
	_tn_mtx->lock();
	_tn_odr.flags |= pxtnxaTUNE_ORDERFLAG_volume;
	_tn_odr.volume = volume;
	_tn_mtx->unlock();
	return true;
}


bool pxtonewinXA2::tune_order_stop     ( float fadeout_sec )
{
	if( !_b_init ) return false;
	_tn_mtx->lock();
	_tn_odr.flags       |= pxtnxaTUNE_ORDERFLAG_stop;
	_tn_odr.fadeout_sec  = fadeout_sec;
	_tn_mtx->unlock();
	return true;
}

bool pxtonewinXA2::tune_order_loop     ( bool  b   )
{
	if( !_b_init ) return false;
	_tn_mtx->lock();
	_tn_odr.flags  |= pxtnxaTUNE_ORDERFLAG_loop;
	_tn_odr.b_loop  = b;
	_tn_mtx->unlock();
	return true;
}

bool pxtonewinXA2::tune_order_unit_mute( bool  b   )
{
	if( !_b_init ) return false;
	_tn_mtx->lock();
	_tn_odr.flags  |= pxtnxaTUNE_ORDERFLAG_unit_mute;
	_tn_odr.b_unit_mute  = b;
	_tn_mtx->unlock();
	return true;
}

int32_t pxtonewinXA2::tune_get_sampling_count_safe() const
{
	int32_t ret = 0;
	_tn_mtx->lock  ();
	ret = _safe_smp_count;
	_tn_mtx->unlock  ();
	return ret;
}

bool pxtonewinXA2::tune_is_sampling     (           )
{
	if( !_tn_mtx->trylock() ) return false;
	bool b_ret = _tn_b_sampling;
	_tn_mtx->unlock();
	return b_ret;
}

void pxtonewinXA2::_tune_sampling ( LPVOID p1, int32_t size1 )
{
	if( !_b_init ) return;
	bool b_vmt    = false;
	bool b_cancel = false;

	_tn_mtx->lock  ();
	{
		if( _tn_odr.flags & pxtnxaTUNE_ORDERFLAG_prep      )
		{
			_tn_odr.flags &= ~pxtnxaTUNE_ORDERFLAG_prep;
			_pxtn->set_destination_quality( _dst_ch_num, _dst_sps );
			if( !_pxtn->moo_preparation( &_tn_odr.prep ) ){ _tn_b_sampling = false; b_cancel = true; }
		}
		if( _tn_odr.flags & pxtnxaTUNE_ORDERFLAG_volume    )
		{
			_tn_odr.flags &= ~pxtnxaTUNE_ORDERFLAG_volume;
			_pxtn->moo_set_master_volume( _tn_odr.volume );
		}
		if( _tn_odr.flags & pxtnxaTUNE_ORDERFLAG_stop      )
		{
			_tn_odr.flags &= ~pxtnxaTUNE_ORDERFLAG_stop;
			if( _tn_odr.fadeout_sec ){ _pxtn->moo_set_fade( -1, _tn_odr.fadeout_sec ); }
			else                     { _tn_b_sampling = false; b_cancel = true;        }
		}
		if( _tn_odr.flags & pxtnxaTUNE_ORDERFLAG_loop      )
		{
			_tn_odr.flags &= ~pxtnxaTUNE_ORDERFLAG_loop;
			_pxtn->moo_set_loop( _tn_odr.b_loop );
		}
		if( _tn_odr.flags & pxtnxaTUNE_ORDERFLAG_unit_mute )
		{
			_tn_odr.flags &= ~pxtnxaTUNE_ORDERFLAG_unit_mute;
			_pxtn->moo_set_mute_by_unit( _tn_odr.b_unit_mute );
		}
		if( !_tn_b_sampling ) b_cancel = true;
	}
	_tn_mtx->unlock();

	if( !b_cancel ) b_vmt = _pxtn->Moo( p1, size1 );

	_tn_mtx->lock  ();
	{
		if( !b_vmt                    ) _tn_b_sampling = false;
		if( _pxtn->moo_is_end_vomit() ) _tn_b_sampling = false;
		_safe_smp_count = _pxtn->moo_get_sampling_offset();
	}
	_tn_mtx->unlock();
}
