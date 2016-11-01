/**
 * sn00n@77k.eu-
 */
//just a few naive sketches 
#ifndef TREE_H
#define TREE_H

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <bitset>
#include <array>
#include <cmath>
#include <memory>

#ifdef EMSCRIPTEN
#include <boost/multiprecision/integer.hpp>
typedef boost::multiprecision::uint128_t uint128_t;
typedef boost::multiprecision::uint256_t uint256_t;
#else
#include <boost/multiprecision/integer.hpp>
typedef unsigned __int128 uint128_t;
typedef __m256 uint256_t;
#endif

enum class ArchType: short
{
    GENERIC,
    AMD64,
    AARCH64,
};

enum class LinkType: bool
{
    Single,
    Double,
};

enum class AccessScheme: bool
{
    Pointer,
    Index,
};


struct IF
{
        typedef _then RET;
};

template< class _then, class _else >
struct IF< false, _then, _else >
{
        typedef _else RET;
};

template< int N > struct ifact{ enum { eval = N * ifact< N - 1>::eval }; };
template <> struct ifact< 0 > { enum { eval = 1 }; };
template< int N, int K >
struct nchoosek{ 
    enum { 
        eval = ifact< N >::eval / ( ifact< K >::eval *  ifact< N - K >::eval)
    };
};
template< uint64_t N, uint64_t M >
struct ipow
{
        enum : uint64_t { eval = N * ipow< N , M - 1 >::eval};
};

template < uint64_t N >
struct ipow< N, 0 >
{
        enum : uint64_t { eval = 1 };
};


template< typename _T, int _I >
struct simd_sum
{
        static inline _T eval(_T &a)
        {
                return a[_I] + simd_sum< _T, _I - 1 >::eval(a);
        }
};

template< typename _T >
struct simd_sum< _T, 0 >
{
        static inline _T eval(_T &a)
        {
                return a[0];
        }
};
template< typename _T >
struct simd_cp< _T, 0 >
{
        static inline void eval(_T &d, _T &s)
        {
                return d[0] = s[0];
        }
};



#endif
