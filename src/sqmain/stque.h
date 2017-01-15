/**************************************************************************
 *
 * Author: Kókai Péter
 * E-mail: kokaipeter[a]gmail[d]com
 *
 * Test:   sqmain.cpp
 *
 **************************************************************************/
#ifndef _STACK_QUEUE_
#define _STACK_QUEUE_

#include <stack>
#include <queue>

#include "if.h"


template< typename T,
          bool Stack = false,
		  typename Container = std::deque< T > >
class StackQueue
{
public:
	struct queue_ {};
	struct stack_ {};
	
	typedef typename Container::size_type size_type;
	typedef T                             value_type;
	typedef typename IF_< Stack,
	                      stack_,
	                      queue_ >::type  container_type;
	
	StackQueue( ) {}
	
	template< typename Iterator >
	StackQueue ( Iterator first, Iterator last )
	{
		for ( ; first != last; ++first )
		{
			push( *first );
		}
	}
	
	void push( const T& value ) { push( value, container_type() ); }
	
	T  get( ) const { return get( container_type() ); }
	T& get( )       { return get( container_type() ); }
	
	void pop( )     { pop( container_type() ); }
	
	size_type size()  const { return _data.size();  }
	bool      empty() const { return _data.empty(); }
	
	std::stack< T, typename std::deque< T > > get_stack() const
	{
		return std::stack< T, typename std::deque< T > >( std::deque<T>( _data.begin(), _data.end() ) );
	}
	
	std::queue< T > get_queue() const
	{
		return std::queue< T, typename std::deque< T > >( std::deque<T>( _data.begin(), _data.end() ) );
	}
protected:
	void push( const T& value, queue_ ) { _data.push_front( value ); }
	void push( const T& value, stack_ ) { _data.push_front( value ); }
	

	inline T  get( queue_ ) const { return _data.back( );  }
	inline T  get( stack_ ) const { return _data.front( ); }
	inline T& get( queue_ )       { return _data.back( );  }
	inline T& get( stack_ )       { return _data.front( ); }
	
	inline void pop( queue_ ) { _data.pop_back();  }
	inline void pop( stack_ ) { _data.pop_front(); }
	
private:
	Container _data;
};

#endif // _STACK_QUEUE_