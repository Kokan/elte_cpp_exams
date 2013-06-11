#ifndef _AUTO_LIST_
#define _AUTO_LIST_

#include <list>
#include <memory>




template< typename T >
class auto_list
{
public:
	class auto_list_iterator : public std::list< T* >::iterator
	{

		
	};
	typedef auto_list_iterator iterator;

	auto_list() {}
	auto_list( auto_list< T > &al )
	{
		if ( this != &al )
		{
			_data.clear();
			for ( iterator iter = al._data.begin();
			      iter != al._data.end();
				  ++iter )
			{
				push_front( new T( **iter ) );
			}
		}
	}

	~auto_list()
	{
		while ( !_data.empty() )
		{
			delete _data.front();
			_data.erase( _data.begin() );
		}
	}
	
	iterator begin() { return _data.begin(); }
	iterator end()   { return _data.end();   }
	
	void insert( T* item ) { _data.insert( begin(), item ); }
	
	template< typename Iterator >
	void insert( iterator position, Iterator first, Iterator last ) { _data.insert( position, first, last ); }
	
	void push_back( T* item )  { _data.push_back( item );  }
	void push_front( T* item ) { _data.push_front( item ); }
	
	T front() const { return *_data.front(); }
	T back()  const { return *_data.back(); }
	
	T& front() { return *_data.front(); }
	T& back()  { return *_data.back(); }
	
	void pop_front() { delete _data.front(); _data.pop_front(); }
	void pop_back()  { delete _data.back();  _data.pop_back();  }
	
	typename std::list< T* >::size_type size() const { return _data.size(); }
private:
	std::list< T* > _data;
};


#endif // _AUTO_LIST_