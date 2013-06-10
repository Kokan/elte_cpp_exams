#ifndef _STACK_QUEUE_
#define _STACK_QUEUE_

#include <stack>
#include <queue>

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
          bool Stack = false,
		  typename Container = std::deque< T > >
class StackQueue
{
public:
	typedef typename Container::size_type size_type;
	typedef T 							  value_type;

	struct queue_ {};
	struct stack_ {};
	
	template< typename Iterator >
	StackQueue ( Iterator first, Iterator last )
	{
		for ( ; first != last; ++first )
		{
			push( *first );
		}
	}
	
	StackQueue( ) {}

	void push( const T& value, queue_ ) {
		_data.push_front( value );
	}
	
	void push( const T& value, stack_ ) {
		_data.push_front( value );
	}
	
	void push( const T& value )
	{
		push( value, typename IF_<Stack,stack_,queue_>::type() );
	}

	T get( queue_ ) const {
		return _data.back( );
	}
	
	T get( stack_ ) const {
		return _data.front( );
	}
	
	T get( ) const
	{
		return get( typename IF_<Stack,stack_,queue_>::type() );
	}

	T& get( queue_ ) {
		return _data.back( );
	}
	
	T& get( stack_ ) {
		return _data.front( );
	}
	
	T& get( )
	{
		return get( typename IF_<Stack,stack_,queue_>::type() );
	}

	void pop( queue_ ) {
		_data.pop_back();
	}
	
	void pop( stack_ ) {
		_data.pop_front();
	}
	
	void pop( )
	{
		pop( typename IF_<Stack,stack_,queue_>::type() );
	}
	
	size_type size() const { return _data.size(); }
	bool empty() const { return _data.empty(); }
	
	
	std::stack< T, typename std::deque< T > > get_stack() const
	{
		return std::stack< T, typename std::deque< T > >( std::deque<T>( _data.begin(), _data.end() ) );
	}
	
	std::queue< T > get_queue() const
	{
		return std::queue< T, typename std::deque< T > >( std::deque<T>( _data.begin(), _data.end() ) );
	}

private:
	Container _data;
};





#endif // _STACK_QUEUE_