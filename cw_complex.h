/**
 * sn00n@77k.eu
 */
#ifndef CW_COMPLEX_H
#define CW_COMPLEX_H

#include "algebra.h"

template< int _Dim, LinkType _LType, AccessScheme _AScheme,
    template< class U , class V > class Containment , template< class U >
    class Allocator, class _Space > class AbstractOrientedCWComplex{};
template< typename _ASD > struct AbstractOrientedCWComplexTopologyTrait{};
template< typename _ASD > struct
AbstractOrientedCWComplexTopologicalOperations{};
template< typename _Iterator >
struct AbstractOrientedCWComplexIteratorFunctionTrait{};
template< typename _ASD > struct AbstractOrientedCWComplexIterator{};
template< int _Dim, LinkType _LType, AccessScheme _AScheme,
    template< class U, class V > class _Containment,
    template< class U > class _Allocator, class _Space >
    struct AbstractOrientedCWCell: _Space {};


#endif
