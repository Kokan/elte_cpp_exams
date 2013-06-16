/**************************************************************************
 *
 * Author: Kókai Péter
 * E-mail: kokaipeter[a]gmail[d]com
 *
 * Test:   
 *
 **************************************************************************/
#ifndef _PALINDROME_STR_
#define _PALINDROME_STR_

#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

#include <iostream>

template< typename T >
class basic_palindrom_string
{
public:
	typedef typename std::basic_string< T >::size_type size_type;
	typedef typename std::basic_string< T >::const_iterator const_iterator;
	typedef typename std::basic_string< T >::iterator iterator;

	void push_front_back( const T &value ) { front.insert( front.begin(), value ); recallc(); }
	void push_middle( const T &value ) { front.push_back( value ); recallc(); }
	
	size_type size() const { return 1.5*front.size(); }
	
	size_type find( const T* what, size_type pos = 0 ) const
	{
		if ( !_tmp_hole_valid ) callc();
		
		return _temp_hole.find( what, pos );
	}
	
	T&  operator[]( size_type pos )
	{
		recallc();
		return front[ pos % front.size() ];
	}
	
	T  operator[]( size_type pos ) const
	{
		return front[ pos % front.size() ];
	}
	
	template< typename T2 >
	int compare( const T2 &othr ) const
	{
		callc();
		return _temp_hole.compare( othr );
	}
	
	iterator begin() { callc(); return _temp_hole.begin(); }
	iterator end()   { callc(); return _temp_hole.end(); }
	
	const_iterator begin() const { callc(); return _temp_hole.begin(); }
	const_iterator end()   const { callc(); return _temp_hole.end(); }
	
private:
	void recallc( ) { _tmp_hole_valid = false; }
	void callc() const
	{
		_temp_hole.clear();
		
		for ( typename std::vector< T >::const_iterator i = front.begin(); front.end() != i; ++i )
		{
			_temp_hole.push_back( *i );
		}
		
		size_type start = ( 0 == front.size() % 2 ? 1 : 0 );
		for ( typename std::vector< T >::const_reverse_iterator i = front.rbegin()+start; front.rend() != i; ++i )
		{
			_temp_hole.push_back( *i );
		}
		//std::for_each( front.begin(), front.end(), std::back_inserter( _temp_hole ) );
		//std::for_each(  back.begin(),  back.end(), std::back_inserter( _temp_hole ) );
	
		_tmp_hole_valid = true;
	}
	
	std::vector< T > front;
	
	mutable std::basic_string< T > _temp_hole;
	mutable bool _tmp_hole_valid;
};


#endif // _PALINDROME_STR_