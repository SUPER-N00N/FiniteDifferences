/**
 * sn00n@77k.eu-
 */
// 
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



#endif
