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

template< bool _cond, class _then, class _else >
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

template <int64_t N > struct wilsons_primality_test 
{
enum : bool { eval = (ifact< N - 1>::eval % N - N == -1) };
};

template <int64_t N > struct fermats_little_primality_test 
{
enum : bool { eval = (ipow< 2, N - 1 >::eval % N == 1) };
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
template< typename _T, int _I >
struct simd_cp
{
        static inline void eval(_T &d, _T &s)
        {
                d[_I] = s[_I]; simd_cp< _T, _I - 1 >::eval(d, s);
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

template< int S > struct SimpleLargerInteger{
        unsigned long long values[S/64];
};

template< int S > struct IntegerChooser
{
        typedef typename 
        IF< S <= sizeof(uint8_t), uint8_t,
                IF< S <= sizeof(uint16_t), uint16_t,
                IF< S <= sizeof(uint32_t), uint32_t,
                IF< S <= sizeof(uint64_t), uint64_t,
                IF< S <= sizeof(uint128_t), uint128_t,
                IF< S <= sizeof(uint256_t), uint256_t,
        SimpleLargerInteger< S > > > > > > >::RET IntegerType;
};

template< > struct IntegerChooser< 3 >
{
    enum { size = 3 };
    typedef uint32_t IntegerType;
};

template< > struct IntegerChooser< 4 >
{
        enum { size = 4};
        typedef uint32_t IntegerType;
};


template< > struct IntegerChooser< 6 >
{
        enum { size = 6};
    typedef __attribute__ ((aligned (8))) uint64_t IntegerType;
};

template< > struct IntegerChooser< 8 >
{
        enum { size = 8};
        typedef __attribute__ ((aligned (8))) uint64_t IntegerType;
};


template< > struct IntegerChooser< 16 >
{
        enum { size = 16};
        typedef __attribute__ ((aligned (16))) uint128_t IntegerType;
};


template< > struct IntegerChooser< 32 >
{
        enum { size = 32};
        typedef __attribute__ ((aligned (32))) uint256_t IntegerType;
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

template< int _Dim, LinkType _LType, AccessScheme _AScheme,
    template< class U , class V > class Containment , template< class U >
    class Allocator, class _Space > class AbstractHalfSimplicialComplex{};
template< typename _ASD > struct AbstractHalfSimplicialComplexTopologyTrait{};
template< typename _ASD > struct
AbstractHalfSimplicialComplexTopologicalOperations{};
template< typename _Iterator >
struct AbstractHalfSimplicialComplexIteratorFunctionTrait{};
template< typename _ASD > struct AbstractHalfSimplicialComplexIterator{};
template< int _Dim, LinkType _LType, AccessScheme _AScheme,
    template< class U, class V > class _Containment,
    template< class U > class _Allocator, class _Space >
    struct AbstractHalfSimplex: _Space {};

///why d + 1 you may ask. 'cause \f$ {d+1 \choose d} = d+1\f$ , u kno'. 
//thus we're terminating the recursion at dimension = -1

template< int _Dim,  template< class U, class V > class _Containment,
    template< class U > class _Allocator,  class _Space >
    struct AbstractHalfSimplex< _Dim, LinkType::Single, AccessScheme::Index,
    _Containment, _Allocator, _Space >: _Space
{
    enum {d = _Dim};
    ptrdiff_t upper, opponent,
              //opponext,
              next;
    //ptrdiff_t lower[_Dim + 1]; 
    ptrdiff_t lower;
    AbstractHalfSimplex()
    {
        upper = -1;
        opponent = -1;
        next = -1;
        lower = -1;
    };
    AbstractHalfSimplex(const AbstractHalfSimplex &s): _Space(s)
    {
        upper = s.upper;
        opponent = s.opponent;
        //opponext = s.opponext;
        next = s.next;
        lower = s.lower;
    }
};

///terminate the recursion in the empty simplex (simplicial set) with
//dimension -1
template< template< class U, class V > class _Containment,
    template< class U > class _Allocator,
    class _Space >
    struct AbstractHalfSimplex< -1, LinkType::Single,
    AccessScheme::Index, _Containment,
    _Allocator, _Space >: _Space
{
    enum { d = -1, };
    AbstractHalfSimplex(){};
    AbstractHalfSimplex(AbstractHalfSimplex &s){};
};

///why d + 1 you may ask. 'cause \f$ {d+1 \choose d} = d+1\f$ , u kno'. thus
//we're terminating the recursion at dimension = -1
template< int _Dim,  template< class U, class V > class _Containment,
    template< class U > class _Allocator >
    struct AbstractHalfSimplex< _Dim, LinkType::Single,
    AccessScheme::Index, _Containment, _Allocator, Set< _Dim > >: Set < _Dim >
{
    enum {d = _Dim};
    ptrdiff_t upper, opponent,
              //opponext,
              next;
    //ptrdiff_t lower[_Dim + 1];
    ptrdiff_t lower;
    AbstractHalfSimplex(){};
    AbstractHalfSimplex(AbstractHalfSimplex &s){};
};
///terminate the recursion in the empty simplex (simplicial set) with dimension -1
template< template< class U, class V > class _Containment,
    template< class U > class _Allocator >
struct AbstractHalfSimplex< -1, LinkType::Single, AccessScheme::Index, _Containment,
    _Allocator, Set< -1 > >: Set< -1 >
{
    enum { d = -1, };
    AbstractHalfSimplex(){};
    AbstractHalfSimplex(AbstractHalfSimplex &s){};
};

template< int D, class SC > struct makeHalfSimplex
{
    static inline void make(SC &s)
    {

    }

};

//default filling with complete simplex of dimension D
template< int D, class _SC > struct ContainerFiller
{
    static inline void fill(_SC& s)
    {
        /*
        typedef AbstractHalfSimplex< _D - 1, LinkType::Single, 
                AccessScheme::Index, _SC::template Containment,
                _SC::template Allocator,
                typename _SC::template Space< _D - 1 > > AbstractHalfSimplexT;
        typedef typename _SC::_Trait::template 
            HalfSimplexT< _D, AbstractHalfSimplexT > HalfSimplex;
        typedef typename _SC::template 
            _Containment< HalfSimplex, 
            _SC::template _Allocator< HalfSimplex > > Simplices;
        s.simplex_containers[_D - 1] = new Simplices;
        */
        /*typedef AbstractHalfSimplex< _D, LinkType::Single, 
                AccessScheme::Index, _SC::template Containment,
                _SC::template Allocator, typename _SC::template Space< _D > > HalfSimplex;*/
        s.simplex_containers[D] = new typename _SC::template Containment<
            typename _SC::template HalfSimplex< D >, typename _SC::template Allocator<
            typename _SC::template HalfSimplex< D > > >;
        ContainerFiller< D - 1, _SC >::fill(s);
    };
};

template< class _SC >
struct ContainerFiller< -1, _SC >{ static inline void fill(_SC&){}};
//template< class _SC > 
//struct ContainerFiller< 0, _SC >{ static inline void fill(_SC&){}};


template< int _D, class _IT, class  _SC > struct IterFiller
{
    static inline void fill(_IT* i)
    {
        typedef  AbstractHalfSimplex< _D, LinkType::Single,
                 AccessScheme::Index, _SC::template Containment,
                 _SC::template Allocator,
                 typename _SC::Space > HalfSimplex;
        i->iterdata[_D ] = new HalfSimplex;
        //void* foo = new HalfSimplex;
        IterFiller< _D - 1, _IT, _SC >::fill(i);
    }
};

template< class _IT, class _SC > struct IterFiller< -1, _IT, _SC >{
    static inline void fill(_IT* i){}
};

  

#endif
