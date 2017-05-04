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
/*
template< int D, template< int _D > class M > using MortonHalfCube =
AbstractOrientedCWCell< D, LinkType::Single, AccessScheme::Index,
    std::vector, std::allocator, MortonSpace< 1, M > >;
template< int D, template< int _D > class M > using MortonHalfCubeComplex =
AbstractOrientedCWComplex< D, LinkType::Single, AccessScheme::Index,
    std::vector, std::allocator, MortonSpace< 1, M > >;
template< int D, template< int _D > class M > using
MortonHalfCubeComplexTopologyTrait = AbstractOrientedCWComplexTopologyTrait<
MortonHalfCubeComplex< D, M > >;
template< int D, template< int _D > class M > using
MortonHalfCubeComplexTopologicalOperations = AbstractOrientedCWComplexTopologicalOperations<
MortonHalfCubeComplex< D, M > >;
template< int D, template< int _D > class M  > using
MortonHalfCubeComplexIterator = AbstractOrientedCWComplexIterator<
MortonHalfCubeComplex< D, M > >;
*/


template< int D, template< int _D > class M > using MortonHalfCube =
AbstractOrientedCWCell< D, LinkType::Single, AccessScheme::Index,
    std::vector, std::allocator, MortonSpace< D, 1, M > >;
template< int D, template< int _D > class M > using MortonHalfCubeComplex =
AbstractOrientedCWComplex< D, LinkType::Single, AccessScheme::Index,
    std::vector, std::allocator, MortonSpace< D, 1, M > >;
template< int D, template< int _D > class M > using
MortonHalfCubeComplexTopologyTrait = AbstractOrientedCWComplexTopologyTrait<
MortonHalfCubeComplex< D, M > >;
template< int D, template< int _D > class M > using
MortonHalfCubeComplexTopologicalOperations = AbstractOrientedCWComplexTopologicalOperations<
MortonHalfCubeComplex< D, M > >;
template< int D, template< int _D > class M  > using
MortonHalfCubeComplexIterator = AbstractOrientedCWComplexIterator<
MortonHalfCubeComplex< D, M > >;

template< int D, template< int _D > class M > 
class AbstractOrientedCWComplexTopologyTrait<MortonHalfCubeComplex< D, M > >
{
	public:

			
		typedef MortonHalfCubeComplex< D, M > ACWCC;
		typedef AbstractOrientedCWComplexIterator< ACWCC > Iter;
		template< int D__ >
			using HalfCube = typename ACWCC::template OrientedCWCell< D >;
		typedef typename ACWCC::Space Space;
		typename ACWCC::Allocator Allocator;
//		typedef typename ACWCC::Container Container;
		template< int _D >
			using Container = typename ACWCC::template Container< _D >;
		

		typedef typename Space::ValueType ValueType;
		typedef typename Space::KeyType KeyType;
		enum {  d = D,
			numofsubkeys = (sizeof(ValueType) * 8),
			numoflevels = (sizeof(KeyType) * 8 / D),
			numofchilds = ipow<2, d >::eval,
			numofneighbours = ipow<3, D>::eval - 1,
		};

		inline void
		getNeighbourhood(int r, Iter &iter)
		{
			//generate r-neighbourhood -- see surroundings
			return;
		}
		template< int _D, class _It >
			struct cellFlip
			{
				static inline bool doit(Iter & iter)
				{
					bool succ;
					ptrdiff_t opponent, parent, upper, max_dim;

					return false;
					
				}
			};

		template< int _D, class _It >
			struct insert
			{
				static inline bool doit(Iter &iter, typename ACWCC::template OrientedCWCell< _D > &c)
				{
					
					//c.v = 0;						
					typename Space::PointT p;								            	
					(static_cast< Container< _D > * >(
									  iter.m_sd
									  ->
									  cell_containers[_D]
									 ))
						->push_back(c);
					iter.cellsindices[ _D ] =
						(static_cast< Container< _D > * >(
										  iter.m_sd
										  ->
										  cell_containers[_D]
										 ))
						->size() - 1;


					return false;
				}
			};
		template< int _D, class _It >
			struct cellAlign
			{
				static inline bool doit(Iter &iter)
				{
					return false;
				}
			};

		template< class _It >
			struct insert< 0, _It >
			{
				static inline bool doit(Iter &iter, typename ACWCC::template OrientedCWCell< 0 > c)
				{
					return false;
				}
			};
};


template< int D, template< int _D > class _M >
struct CubicalSpaceCompressed: public CAT< 0, D, _M>
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

	typedef MortonHalfCubeComplex < D, _M > MHCC;

	template < int _D >
		using HalfCube = MortonHalfCube< _D, _M >;
	typedef MortonHalfCubeComplexIterator< d, _M > Iterator;
	template < int _D > 
	using Container = typename MHCC::template Container< _D >;

	
	//std::map< KeyType, std::tuple< int, std::tuple< HalfCube<0>, HalfCube<1>, HalfCube<2>, HalfCube<3>> > > l_map; 
	std::map< KeyType, std::vector< std::vector< typename HalfCube< D >::Space > > > q_map; 
	MHCC m_mhcc;

	template < int __D >
	void insert(HalfCube< D > &hc)
	{
					
	}	

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
