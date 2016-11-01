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

//todo generalize from uint64_t
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

template< uint64_t N >
struct ild
{
enum : uint64_t { eval = 1 + ild< N/2 >::eval};

};
template < >
struct ild< 2 >{ enum : uint64_t { eval = 1 }; };

template< int64_t _X, int64_t _N >
struct inroot
{
    template< bool _c, int64_t _d, int64_t _x, int64_t _e >
        struct _do { enum : int64_t {  N = _N, X = _X,
                                       d = (N - 1) * _x + ((X / ( ipow< _x, N - 1>::eval))) / N, x = _x + d,
                                       eval = _do< (x > _x), d, x, _e >::eval};};
    template< int64_t _d, int64_t _x, int64_t _e >
        struct _do< false, _d, _x, _e >
        {
                enum : int64_t { d = _d, x = _x, eval = _x };
        };
enum : uint64_t { eval = (_do< true, 0, 1, 1>::x)};
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

template < int K, int D, class S>
struct ExteriorPower;
template < int D, class S >
struct ExteriorAlgebra;
template< int N > struct Algebra {};
template< int N > struct GradedAlgebra {};
template< int K, int N > struct QuotientSpace {};

template< int _Dim >
struct Set { enum { d = _Dim }; };
template< int _Dim >
struct TopologicalSpace: Set< _Dim > {};
template< int _Dim >
struct UniformSpace: TopologicalSpace< _Dim > {};
template< int _Dim, template < int __D > class _M  >
struct MetricSpace: UniformSpace < _Dim > {};

template< int64_t N > class QuotientRing {};



#endif
