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

template< int _Dim,
    template< class U , class V > class _Containment,
    template< class U > class _Allocator,  class _Space>
    class AbstractOrientedCWComplex< _Dim,
    LinkType::Single, AccessScheme::Index,
    _Containment, _Allocator, _Space >
{
    public:
        enum { d = _Dim,};
        template< class U, class V >
            using Containment = _Containment< U, V >;
        template< class U >
            using Allocator = _Allocator< U >;
        //template< int D >
        using Space = _Space;
        template< int D >
          using OrientedCWComplex = AbstractOrientedCWComplex< D, LinkType::Single,
                 AccessScheme::Index, _Containment,
                 _Allocator, Space >;
        template< int D >
            using Container = Containment< OrientedCWCell< D >,
                  Allocator< OrientedCWCell< D > > >;
    

        AbstractOrientedCWComplex()
        {
            ContainerFiller< _Dim, AbstractOrientedCWComplex >::fill(*this);
        }
        ~AbstractOrientedCWComplex()
        {
            //for(int i = 0; i < _Dim; i++) delete cell_containers[i];

        }

        inline void* foo(ptrdiff_t i)
        {
            return cell_containers[i];
        }


        template < int D >
        inline AbstractOrientedCWComplexIterator < AbstractOrientedCWComplex >
        insert( OrientedCWComplex< D > &s )
        {

            AbstractOrientedCWComplexIterator<AbstractOrientedCWComplex>
                iter(this);
            iter.insert(s);
            return iter;

        }

        inline void* operator [] (const int i)
        {
            //Container< i > C;
            return cell_containers[i];
            //return *((Container< i > *) cell_containers[D]);
            //return new F;
        }

        void* cell_containers[_Dim + 1];
};

template< int _Dim, LinkType _LType, AccessScheme _AScheme,
    template< class U , class V > class _Containment,
    template< class U > class _Allocator, class _Space>
class AbstractOrientedCWComplexIterator<
AbstractOrientedCWComplex< _Dim, _LType,
    _AScheme, _Containment, _Allocator, _Space > >
{
    public:
	    typedef AbstractOrientedCWComplex< _Dim, _LType,
		    _AScheme, _Containment, _Allocator, _Space > ACWCT;
	    typedef AbstractOrientedCWComplexTopologyTrait< ACWCT > ACWCTopoT;
	    typedef AbstractOrientedCWComplexTopologicalOperations < ACWCT >
		    ACWCTopoOp;
	    typedef AbstractOrientedCWComplexIteratorFunctionTrait<
		    AbstractOrientedCWComplexIterator > IterFuncT;
	    template< int D >
		    using OrientedCWCell = AbstractOrientedCWCell< D, LinkType::Single,
			  AccessScheme::Index, _Containment,
			  _Allocator, _Space >;
	    template< int D >
		    using Container = _Containment< OrientedCWCell< D >,
			  _Allocator< OrientedCWCell < D > > >;


	    AbstractOrientedCWComplexIterator(ACWCT* cwc)
	    {
		    m_sd = cwc;
		    IterFiller< _Dim, AbstractOrientedCWComplexIterator,
			    ACWCT >::fill(this);
	    }
	    AbstractOrientedCWComplexIterator()
	    {
		    IterFiller< _Dim, AbstractOrientedCWComplexIterator,
			    ACWCT >::fill(this);
	    }
	    AbstractOrientedCWComplexIterator(const
			    AbstractOrientedCWComplexIterator &iter)
	    {
		    for(int i = 0; i < _Dim + 1; i++)
		    {
			    iterdata[i] = iter.iterdata[i];
			    cellsindices[i] = iter.cellsindices[i];
			    m_sd = iter.m_sd;
		    }

	    }

	    ~AbstractOrientedCWComplexIterator()
	    {
		    //for(int i = 0; i < _Dim; i++) delete iterdata[i];
	    }

	    inline bool isvalid()
	    {
		    return IterFuncT::isvalid(*this);
	    }
	    inline AbstractOrientedCWComplexIterator&
		    make(OrientedCWCell< 0 > s[ _Dim + 1])
		    {
			    return ACWCTopoOp::template makeAbstractSimplex<
				    AbstractOrientedCWComplexIterator, _Dim >
				    ::doit(*this, s);
		    }
	    template < int D >
		    inline AbstractOrientedCWComplexIterator&
		    insert(OrientedCWCell< D > &s)
		    {
			    ACWCTopoT::template insert<D,
				    AbstractOrientedCWComplexIterator >::doit(*this, s);
			    return *this;
		    }
	    template < int _D >
		    inline AbstractOrientedCWComplexIterator& simplexCCW()
		    {
			    ACWCTopoT::template simplexCCV<_D,
				    AbstractOrientedCWComplexIterator >::doit(*this);
			    return *this;
		    }
	    template < int D >
		    inline Container< D > &
		    getSimplices(OrientedCWCell< D > &hs)
		    {
			    return *(static_cast< Container< D > * >
					    (m_sd->cell_containers[D]));

		    }
	    template < int D >
		    inline OrientedCWCell< D > &
		    get(OrientedCWCell< D > &hs)
		    {

			    return
				    (*(static_cast< Container< D > * >
				       (m_sd->cell_containers[D])))
				    [cellsindices[ D ]];


		    }
	    inline ptrdiff_t getID(ptrdiff_t i)
	    {
		    return cellsindices[i];
	    }

	    inline ptrdiff_t& operator [] (ptrdiff_t i)
	    {
		    return cellsindices[i];
	    }

	    template < int D >
		    inline OrientedCWCell < D > &
		    makeOrientedCWCell()
		    {
		    }
	    void*       iterdata[_Dim + 1];
	    ptrdiff_t       cellsindices[_Dim + 1];
	    ACWCT    *m_sd;
};



#endif
