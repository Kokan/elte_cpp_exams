#ifndef _AUTO_LIST_
#define _AUTO_LIST_

#include <list>
#include <memory>

template< typename T >
class auto_list
{
public:

	~auto_list()
	{
		while ( !_data.empty() )
		{
			delete _data.front();
			_data.erase( _data.begin() );
		}
	}
	
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