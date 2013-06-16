/**************************************************************************
 *
 * Author: Kókai Péter
 * E-mail: kokaipeter[a]gmail[d]com
 *
 * Test:   bdmain.cpp
 *         bidirmap.cpp
 *
 **************************************************************************/
#ifndef _BIMAP_
#define _BIMAP_

#include <map>
#include <stdexcept>

template< typename T1 >
class BidirectionalMap
{
public:
	typedef typename std::map< T1, T1 >::size_type size_type;
	typedef typename std::map< T1, T1 >::iterator  iterator;
	typedef typename std::map< T1, T1 >::const_iterator  const_iterator;

	void insert( const T1 &key, const T1 &value )
	{
		key_value[ key ]   = value;
		value_key[ value ] = key;
	}
	
	T1  at( const T1 &key ) const
	{
		if ( key_value.count( key ) > 0 ) return key_value.at( key );
		if ( value_key.count( key ) > 0 ) return value_key.at( key );
		
		throw std::out_of_range(  "BidirectionalMap::At" );
	}
	
	T1& at( const T1 &key )
	{
		if ( key_value.count( key ) > 0 ) return key_value.at( key );
		if ( value_key.count( key ) > 0 ) return value_key.at( key );
		
		throw std::out_of_range(  "BidirectionalMap::At" );
	}
	
	T1  operator[]( const T1 &value ) const { return at( value ); }
	T1& operator[]( const T1 &value )       { return at( value ); }
	
	size_type count( const T1 &key ) const { return key_value.count( key ) + value_key.count( key ); }
	
	void erase( const T1 &key )
	{
		T1 pair;
		try {
			pair = at( key );
		}
		
		catch ( std::out_of_range &e )//cannot find simply do nothing
		{ return; }
		
		catch (...)//every other exception re-throw here
		{ throw; }
		
		value_key.erase( key );
		key_value.erase( pair );
		
		key_value.erase( key );
		value_key.erase( pair );
	}
	
	size_type size() const { return key_value.size(); }
	
	iterator begin() { return key_value.begin(); }
	iterator end()   { return key_value.end();   }
	
	const_iterator begin() const { return key_value.begin(); }
	const_iterator end()   const { return key_value.end();   }
	
	BidirectionalMap( ) {}
	
	template< typename Iterator >
	BidirectionalMap( Iterator first, Iterator last )
	{
		for ( ; first != last; ++first  )
		{
			insert( first->first, first->second );
		}
	}

private:
	std::map< T1, T1 > key_value;
	std::map< T1, T1 > value_key;
};

#endif // _BIMAP_