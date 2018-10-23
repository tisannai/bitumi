#include "unity.h"
#include "bitumi.h"

void test_basic( void )
{
    bp_t bp;

    bp = bp_new( 3 );
    TEST_ASSERT_TRUE( bp_size( bp ) == 3 );

    bp = bp_del( bp );
    TEST_ASSERT_TRUE( bp == NULL );

    bp = bp_new( 65 );
    TEST_ASSERT_TRUE( bp_size( bp ) == 65 );
    TEST_ASSERT_TRUE( bp_get( bp, 0 ) == 0 );
    TEST_ASSERT_TRUE( bp_get( bp, 64 ) == 0 );
    
    bp_set( bp, 0 );
    bp_set( bp, 32 );
    bp_set( bp, 64 );
    TEST_ASSERT_TRUE( bp_get( bp, 0 ) == 1 );
    TEST_ASSERT_TRUE( bp_get( bp, 32 ) == 1 );
    TEST_ASSERT_TRUE( bp_get( bp, 64 ) == 1 );
    
    bp_clr( bp, 0 );
    bp_clr( bp, 32 );
    bp_clr( bp, 64 );
    TEST_ASSERT_TRUE( bp_get( bp, 0 ) == 0 );
    TEST_ASSERT_TRUE( bp_get( bp, 32 ) == 0 );
    TEST_ASSERT_TRUE( bp_get( bp, 64 ) == 0 );

    bp_put( bp, 31, 1 );
    bp_put( bp, 63, 1 );
    bp_put( bp, 64, 1 );
    TEST_ASSERT_TRUE( bp_get( bp, 31 ) == 1 );
    TEST_ASSERT_TRUE( bp_get( bp, 63 ) == 1 );
    TEST_ASSERT_TRUE( bp_get( bp, 64 ) == 1 );

    bp_put( bp, 31, 0 );
    bp_put( bp, 63, 0 );
    bp_put( bp, 64, 0 );
    TEST_ASSERT_TRUE( bp_get( bp, 31 ) == 0 );
    TEST_ASSERT_TRUE( bp_get( bp, 63 ) == 0 );
    TEST_ASSERT_TRUE( bp_get( bp, 64 ) == 0 );

}


void test_use( void )
{
    st_u64_t mem[ 2 ];
    bp_t bp;

    bp = bp_use( 64, mem, 16 );
    TEST_ASSERT_TRUE( bp_size( bp ) == 64 );

    bp_set( bp, 0 );
    bp_set( bp, 32 );
    TEST_ASSERT_TRUE( bp_get( bp, 0 ) == 1 );
    TEST_ASSERT_TRUE( bp_get( bp, 32 ) == 1 );

    bp_clr( bp, 0 );
    bp_clr( bp, 32 );
    TEST_ASSERT_TRUE( bp_get( bp, 0 ) == 0 );
    TEST_ASSERT_TRUE( bp_get( bp, 32 ) == 0 );
}
