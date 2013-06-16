/**************************************************************************
 *
 * Author: Kókai Péter
 * E-mail: kokaipeter[a]gmail[d]com
 *
 * Test:   
 *
 **************************************************************************/
#ifndef _ARRAY_
#define _ARRAY_

#include <vector>

template< typename T,
          int Size  >
class Array
{
public:
	Array( const T &value = T() )
	: _data( Size, value )
	{ }
	
	template< typename Iterator >
	Array( Iterator first, Iterator last )
	: _data( first, last )
	{ _data.resize(Size); }
	
	typename std::vector< T >::size_type size() const { return Size; }
	
	T& operator[]( typename std::vector< T >::size_type index )       { return _data[ index ]; }
	T  operator[]( typename std::vector< T >::size_type index ) const { return _data[ index ]; }
	
	T& at( typename std::vector< T >::size_type index )       { return _data.at( index ); }
	T  at( typename std::vector< T >::size_type index ) const { return _data.at( index ); }
	
	typename std::vector< T >::iterator begin() { return _data.begin(); }
	typename std::vector< T >::iterator end()   { return _data.end();   }
	
	typename std::vector< T >::const_iterator begin() const { return _data.begin(); }
	typename std::vector< T >::const_iterator end()   const { return _data.end();   }
	
private:
	std::vector< T > _data;
};

template< typename Iterator,
          typename Condition,
		  typename Functor >
Functor for_each_if( Iterator first, Iterator last, Condition cond, Functor func )
{
	while ( first != last )
	{
		if ( cond(*first) )
		{
			func(*first);
		}
		++first;	
	}
	return func;
}

#endif //_ARRAY_