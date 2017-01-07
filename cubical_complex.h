#ifndef CUBICAL_COMPLEX
#define CUBICAL_COMPLEX

#include "cw_complex.h"
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


template< int _Dim,
    template< class U , class V > class _Containment,
    template< class U > class _Allocator, class _Space>
class AbstractOrientedCubicalComplexTopologyTrait<
AbstractOrientedCWComplex< _Dim, LinkType::Single,
    AccessScheme::Index, _Containment, _Allocator, _Space > >
{
	public:
	
	
	
};
#endif
