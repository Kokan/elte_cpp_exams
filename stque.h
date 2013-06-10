#ifndef _STACK_QUEUE_
#define _STACK_QUEUE_

#include <vector>

template< bool Cond,
          typename True,
          typename False>
struct IF_
{
	typedef True type;
};

template< typename True,
          typename False>
struct IF_<false,True,False>
{
	typedef False type;
};



template< typename T,
          bool Stack >
class StackQueue
{
public:
	struct false_;
	struct true_;

	void push( const T& value, false_ ) {
		_data.push_front( value );
	}
	
	void push( const T& value, true_ ) {
		_data.push_back( value );
	}
	
	void push( const T& value )
	{
		push( value, IF_<Stack,true_,false_>::type );
	}

	T get( const T& value, false_ ) const {
		_data.front( value );
	}
	
	T get( const T& value, true_ ) const {
		_data.back( value );
	}
	
	T get( ) const
	{
		get( IF_<Stack,true_,false_>::type );
	}

private:
	std::vector< T > _data;
};





#endif // _STACK_QUEUE_