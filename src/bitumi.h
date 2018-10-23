#ifndef BITUMI_H
#define BITUMI_H

/**
 * @file   bitumi.h
 * @author Tero Isannainen <tero.isannainen@gmail.com>
 * @date   Mon Jun  4 21:41:30 2018
 * 
 * @brief  Bit-pack storage.
 * 
 */


#include <sixten.h>


st_struct( bp );

/** Number of bits in Bit-pack atom. */
#define BP_ATOM_SIZE 64



#ifndef BITUMI_NO_ASSERT
#include <assert.h>
/** Default assert. */
#define bp_assert assert
#else
/** Disabled assertion. */
#define bp_assert( cond ) (void)( ( cond ) || bp_void_assert() )
#endif



/**
 * Allocate storage for bits.
 *
 * @param bits Number of bits to store.
 *
 * @return Bit-pack.
 */
bp_t bp_new( st_u64_t bits );


/**
 * Use existing memory for storing bits.
 *
 * NOTE: Memory size must be at least 16-bytes, i.e. 128-bits.
 *
 * @param bits      Number of bits to store.
 * @param mem       Memory for storage.
 * @param byte_size Memory storage size in bytes.
 *
 * @return Initalize Bit-pack
 */
bp_t bp_use( st_u64_t bits, st_t mem, st_u64_t byte_size );


/**
 * Delete Bit-pack.
 *
 * @param bp Bit-pack.
 *
 * @return NULL
 */
bp_t bp_del( bp_t bp );


/**
 * Set bit in Bit-pack.
 *
 * @param bp Bit-pack.
 * @param ri Bit index.
 *
 * @return NA
 */
void bp_set( bp_t bp, st_u64_t ri );


/**
 * Clear bit in Bit-pack.
 *
 * @param bp Bit-pack.
 * @param ri Bit index.
 *
 * @return NA
 */
void bp_clr( bp_t bp, st_u64_t ri );


/**
 * Put bit value to Bit-pack.
 *
 * @param bp  Bit-pack.
 * @param ri  Bit index.
 * @param val Bit value.
 *
 * @return NA
 */
void bp_put( bp_t bp, st_u64_t ri, st_u8_t val );


/**
 * Get bit value from Bit-pack.
 *
 * @param bp Bit-pack.
 * @param ri Bit index.
 *
 * @return True (1) if set, false (0) otherwise.
 */
st_u8_t bp_get( bp_t bp, st_u64_t ri );


/**
 * Return Bit-pack size.
 *
 * @param bp Bit-pack.
 *
 * @return Size.
 */
st_u64_t bp_size( bp_t bp );



/**
 * Disabled (void) assertion.
 */
void bp_void_assert( void );


#endif
