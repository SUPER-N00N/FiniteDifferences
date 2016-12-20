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
//kolmogorov classes -> separation -> stratification

//why d + 1 -> -\f$ {d+1 \choose d} = d+1\f$  
//cartan filtration ends at d = -1

template< int _Dim,  template< class U, class V > class _Containment,
    template< class U > class _Allocator,  class _Space >
    struct AbstractOrientedCWCell< _Dim, LinkType::Single, AccessScheme::Index,
    _Containment, _Allocator, _Space >: _Space
{
    enum {d = _Dim};
    ptrdiff_t upper, opponent,
              next;
    //ptrdiff_t lower[_Dim + 1]; 
    ptrdiff_t lower;
    AbstractOrientedCWCell()
    {
        upper = -1;
        opponent = -1;
        next = -1;
        lower = -1;
    };
    AbstractOrientedCWCell(const AbstractOrientedCWCell &s): _Space(s)
    {
        upper = s.upper;
        opponent = s.opponent;
        //opponext = s.opponext;
        next = s.next;
        lower = s.lower;
    }
};

///terminate the recursion of the filtration in the empty Abstract CW Cell with
//dimension -1
template< template< class U, class V > class _Containment,
    template< class U > class _Allocator,
    class _Space >
    struct AbstractOrientedCWCell< -1, LinkType::Single,
    AccessScheme::Index, _Containment,
    _Allocator, _Space >: _Space
{
    enum { d = -1, };
    AbstractOrientedCWCell(){};
    AbstractOrientedCWCell(AbstractOrientedCWCell &s){};
};


template< int _Dim,  template< class U, class V > class _Containment, 
    template< class U > class _Allocator > 
    struct AbstractOrientedCWCell< _Dim, LinkType::Single, 
    AccessScheme::Index, _Containment, _Allocator, Set< _Dim > >: Set < _Dim > 
{
    enum {d = _Dim};
    ptrdiff_t upper, opponent,
              //opponext,
              next;
    //ptrdiff_t lower[_Dim + 1];
    ptrdiff_t lower;
    AbstractOrientedCWCell(){};
    AbstractOrientedCWCellAbstractOrientedCWCell &s){};
};

template< template< class U, class V > class _Containment,
    template< class U > class _Allocator >
struct AbstractOrientedCWCell< -1, LinkType::Single, AccessScheme::Index, _Containment,
    _Allocator, Set< -1 > >: Set< -1 >
{
    enum { d = -1, };
    AbstractOrientedCWCell(){};
    AbstractOrientedCWCell(AbstractOrientedCWCell &s){};
};

template< int D, class CWC > struct makeCWCell
{
    static inline void make(CWC &c)
    {

    }

};

template< int D, class _CWC > struct ContainerFiller
{
    static inline void fill(_CWC& c)
    {   
        s.cell_containers[D] = new typename _SC::template Containment<
            typename _CWC::template CWCell< D >, typename _SC::template Allocator<
            typename _CWC::template CWCell< D > > >;
        ContainerFiller< D - 1, _SC >::fill(s);
    };
};

template< class _CWC >
struct ContainerFiller< -1, _CWC >{ static inline void fill(_CWC&){}};


template< int _D, class _IT, class  _CWC > struct IterFiller
{
    static inline void fill(_IT* i)
    {
        typedef  AbstractOrientedCWCell< _D, LinkType::Single,
                 AccessScheme::Index, _SC::template Containment,
                 _SC::template Allocator,
                 typename _CWC::Space > CWCell;
        i->iterdata[_D ] = new CWCell;
        //void* foo = new CWCell;
        IterFiller< _D - 1, _IT, _CWC >::fill(i);
    
};

template< class _IT, class _CWC > struct IterFiller< -1, _IT, _CWC >{
    static inline void fill(_IT* i){}
};

#endif
