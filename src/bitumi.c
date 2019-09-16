/**
 * @file   bitumi.c
 * @author Tero Isannainen <tero.isannainen@gmail.com>
 * @date   Sun May 27 20:07:33 2018
 *
 * @brief  Bit-pack storage.
 *
 * Pack bits (bit info) into 64-bit unsigned integer. The storage is
 * more cache friendly since storage is smaller that without bit
 * packing, e.g. 8 times smaller than char based storage.
 *
 */


#include "bitumi.h"



/**
 * Bp storage.
 */
st_struct( bp )
{
    st_u64_t size;      /**< Number of bits in storage. */
    st_u64_t bits[ 0 ]; /**< Atom array. */
};


#define BP_BIT_CNT BP_ATOM_SIZE
#define BP_ATM_IDX( bits ) ( ( bits ) / ( BP_BIT_CNT ) )
#define BP_BIT_IDX( bits ) ( ( bits ) % ( BP_BIT_CNT ) )
#define BP_SET_MSK( bi ) ( UINT64_C( 1 ) << ( bi ) )
#define BP_CLR_MSK( bi ) ( ( UINT64_C( 1 ) << ( bi ) ) ^ ( UINT64_MAX ) )



bp_t bp_new( st_u64_t bits )
{
    bp_t bp;
    bp = st_alloc( sizeof( bp_s ) + sizeof( BP_ATM_IDX( bits - 1 ) + 1 ) );
    bp->size = bits;
    return bp;
}


bp_t bp_use( st_u64_t bits, st_t mem, st_u64_t byte_size )
{
    bp_t ret;

    bp_assert( ( ( byte_size * 8 ) % BP_BIT_CNT ) == 0 );
    bp_assert( byte_size >= ( BP_BIT_CNT / 8 + sizeof( bp_s ) ) );
    bp_assert( ( bits / 8 ) <= byte_size );

    ret = mem;
    ret->size = bits;

    st_memclr( ret->bits, byte_size );

    return ret;
}


bp_t bp_del( bp_t bp )
{
    st_del( bp );
    return NULL;
}


void bp_set( bp_t bp, st_u64_t ri )
{
    bp_assert( ri <= ( bp->size - 1 ) );
    st_u64_p ai = &bp->bits[ BP_ATM_IDX( ri ) ];
    st_u64_t bi = BP_BIT_IDX( ri );
    *ai = ( *ai ) | BP_SET_MSK( bi );
}


void bp_clr( bp_t bp, st_u64_t ri )
{
    bp_assert( ri <= ( bp->size - 1 ) );
    st_u64_p ai = &bp->bits[ BP_ATM_IDX( ri ) ];
    st_u64_t bi = BP_BIT_IDX( ri );
    *ai = ( *ai ) & BP_CLR_MSK( bi );
}


void bp_put( bp_t bp, st_u64_t ri, st_u8_t val )
{
    bp_assert( ri <= ( bp->size - 1 ) );
    st_u64_p ai = &bp->bits[ BP_ATM_IDX( ri ) ];
    st_u64_t bi = BP_BIT_IDX( ri );
    if ( val == 0 )
        *ai = ( *ai ) & BP_CLR_MSK( bi );
    else
        *ai = ( *ai ) | BP_SET_MSK( bi );
}


st_u8_t bp_get( bp_t bp, st_u64_t ri )
{
    bp_assert( ri <= ( bp->size - 1 ) );
    st_u64_p ai = &bp->bits[ BP_ATM_IDX( ri ) ];
    st_u64_t bi = BP_BIT_IDX( ri );
    return ( st_u8_t )( ( ( *ai ) & BP_SET_MSK( bi ) ) >> bi );
}


st_u64_t bp_size( bp_t bp )
{
    return bp->size;
}


void bp_void_assert( void ) // GCOV_EXCL_LINE
{}
