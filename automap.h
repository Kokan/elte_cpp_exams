/**************************************************************************
 *
 * Author: Kókai Péter
 * E-mail: kokaipeter[a]gmail[d]com
 *
 * Test:   
 *
 **************************************************************************/
#ifndef _AUTO_MAP_
#define _AUTO_MAP_

#include <map>
#include <type_traits>

template< typename T,
          typename bool_type >
struct wr
{
	wr( T val = T() ) : value( val ) {}
	
	T value;
};

template< typename T >
struct wr< T, std::false_type >
{
	wr( T val = T(0) ) : value( val ) {}
	
	T value;
};


template< typename T,
          bool hasDefaultConstructor >
bool operator<( const wr< T, hasDefaultConstructor >& a, const wr< T, hasDefaultConstructor >& b )
{
  return a.value < b.value;
}

template< typename T,
          bool hasDefaultConstructor >
bool operator==( const wr< T, hasDefaultConstructor >& a, const wr< T, hasDefaultConstructor >& b )
{
  return !( a < b ) && !( b < a );
}

template< typename T,
          bool hasDefaultConstructor >
bool operator!=( const wr< T, hasDefaultConstructor >& a, const wr< T, hasDefaultConstructor >& b )
{
  return !( a == b );
}


template< typename Key,
          typename Value >
class auto_map
{
public:
	typedef typename wr< Key,   typename std::is_default_constructible< Key >::value >   KeyT;
	typedef typename wr< Value, typename std::is_default_constructible< Value >::value > ValueT;

	void insert( Key *key, Value *value ) { _data[ KeyT(*key) ] = ValueT(*value); delete key; delete value; }
	
	typename std::map< KeyT, ValueT >::size_type size() const { return _data.size(); }

private:
	
	std::map< KeyT, ValueT > _data;
};




#endif // _AUTO_MAP_