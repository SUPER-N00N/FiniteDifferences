#ifndef CUBICAL_COMPLEX
#define CUBICAL_COMPLEX

#include "cw_complex.h"
#include "algebra.h"
//specialize for cubical
//specialise the cells for proper spaces
//specialize for CAT(0) space ... hadamard spaces for cubicalComplex
/* 
template< int D > using OrientedCWCell = AbstractOrientedCWCell< D, LinkType::Single,
    AccessScheme::Index, std::vector, std::allocator, TopologicalSpace< D + 1 > >;
template< int D > using OrientedCWComplex = AbstractOrientedCWComplex< D,
    LinkType::Single, AccessScheme::Index, std::vector, std::allocator,
    TopologicalSpace< D + 1 > >;
template< int D > using OrientedCWComplexTopologyTrait =
AbstractOrientedCWComplexTopologyTrait < OrientedCWComplex< D + 1 > >;
template< int D > using OrientedCWComplexIterator = AbstractOrientedCWComplexIterator< OrientedCWComplex< D > >;
*/

template < int D >
using EuclidianSpaceCompressedFuint16 = MetricSpaceCompressed< D,
      SimpleEuklidianMetricFuint16 >;
template< int D >
using EuclidianSpaceCompressedFuint32 = MetricSpaceCompressed< D,
      SimpleEuklidianMetricFuint32 >;
template< int D >
using EuclidianSpaceCompressedFuint64 = MetricSpaceCompressed< D,
      SimpleEuklidianMetricFuint64 >;

template< int D, template< int _D > class M > using MortonHalfSimplex =
AbstractHalfSimplex< D, LinkType::Single, AccessScheme::Index,
    std::vector, std::allocator, MortonSpace< 1, M > >;
template< int D, template< int _D > class M > using MortonHalfSimplicialComplex =
AbstractHalfSimplicialComplex< D, LinkType::Single, AccessScheme::Index,
    std::vector, std::allocator, MortonSpace< 1, M > >;
template< int D, template< int _D > class M > using
MortonHalfSimplicialComplexTopologyTrait = AbstractHalfSimplicialComplexTopologyTrait<
MortonHalfSimplicialComplex< D, M > >;
template< int D, template< int _D > class M > using
MortonHalfSimplicialComplexTopologicalOperations = AbstractHalfSimplicialComplexTopologicalOperations<
MortonHalfSimplicialComplex< D, M > >;
template< int D, template< int _D > class M  > using
MortonHalfSimplicialComplexIterator = AbstractHalfSimplicialComplexIterator<
MortonHalfSimplicialComplex< D, M > >;


template< int D, template< int _D > class _M >
struct CubicalSpace: public CAT< 0, _M< D >>
{
	enum { d = D};
	typedef _M< D > Metric;
	typedef HyperCubeTree< D, 0, _M, std::vector, std::allocator > Tree;
	typedef typename Metric::KeyType KeyType;
	typedef typename Metric::ValueType ValueType;
	typedef typename Metric::PValueType PValueType;
	typedef typename Metric::template ElementT< d > PointT;
	typedef typename ExteriorPower< 1, d, CubicalSpaceCompressed >::Vector
		Vector;
	typedef typename ExteriorPower< 0, 0, CubicalSpaceCompressed>::Vector
		Scalar;

	typedef std::vector< std::pair< KeyType, KeyType > > Edges;
	typedef std::vector< std::array< KeyType, 5 > > Cubes;


};
//template<int D, class M>
//using CAT0MetricSpace = CAT<0, MetricSpaceCompressed< D, M >>;
//template<int D>
//using CubicalSpaceCompressedFuint64 = CAT<0, EuclidianSpaceCompressedFuint64< D >>;
//template< int D, template < int ___D > class Metric,
//    template< class U , class V > class _Containment,
//    template< class U > class _Allocator, template< int _D, template < int __D > class M > class CAT0 >
//using OrientedCubicalComplex = AbstractOrientedCWComplex < D, LinkType::Single, AccessScheme::Index, _Containment, _Allocator,
//							   CAT<0, MetricSpaceCompressed< D + 1, Metric > > >; 



//template< int D, template < int ___D > class Metric,
//    template< class U , class V > class _Containment,
//    template< class U > class _Allocator>
//class AbstractOrientedCWComplex < D, LinkType::Single, AccessScheme::Index, _Containment, _Allocator,
//			    CAT<0, MetricSpaceCompressed< D + 1, Metric > > >
//{
//};
/*
template<int D>
using CubicalSpaceCompressedFuint64 = CAT<0, EuclidianSpaceCompressedFuint64< D >>;
template< int D, template < int ___D > class Metric,
    template< class U , class V > class _Containment,
    template< class U > class _Allocator, template< int _D > class CAT0 >
using OrientedCubicalComplex = AbstractOrientedCWComplex < D, LinkType::Single, AccessScheme::Index, _Containment, _Allocator,
							   CAT<0, TopologicalSpace< D + 1> > >; 



template< int D, template < int ___D > class Metric,
    template< class U , class V > class _Containment,
    template< class U > class _Allocator>
class AbstractOrientedCWComplex < D, LinkType::Single, AccessScheme::Index, _Containment, _Allocator,
			    CAT<0, TopologicalSpace< D > > >
{
};

*/





/*
template< int _Dim,
    template< class U , class V > class _Containment,
    template< class U > class _Allocator >
using OrientedCubicalComplexTopologyTrait = AbstractOrientedCWComplexTopologyTrait < AbstractOrientedCWComplex < 
						_Dim, LinkType::Single, AccessScheme::Index, _Containment, _Allocator,
						CubicalSpace<_Dim> >;
 */
//template< typename _ACWC > struct AbstractOrientedCubicalComplexTopologyTrait{};
/*
template< int _Dim,
    template< class U , class V > class _Containment,
    template< class U > class _Allocator, class _Space>
class AbstractOrientedCubicalComplexTopologyTrait<
AbstractOrientedCWComplex< _Dim, LinkType::Single,
    AccessScheme::Index, _Containment, _Allocator, _Space > >
{
	public:
	
	
	
};
*/

/*
template< typename _ACWC > struct CubicalComplexTopologyTrait{};

template< int _Dim,
    template< class U , class V > class _Containment,
    template< class U > class _Allocator, class _Space>
class OrientedCubicalComplexTopologyTrait<
AbstractOrientedCWComplex< _Dim, LinkType::Single,
    AccessScheme::Index, _Containment, _Allocator, CubicalSpace > >
{
	public:
	
	
	
};
*/
#endif
