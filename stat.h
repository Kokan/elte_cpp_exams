#ifndef _STAT_
#define _STAT_

#include <map>
#include <set>
#include <algorithm>
#include <functional>

template< typename Container,
          typename Type = typename Container::value_type >
class Statistics
{
public:
	Statistics()
	{ }
	
	Statistics( const Container &from )
	: _data( from )
	{ }
	
	void insert( const Type &value ) { _data.insert( _data.begin(), value ); unvalidate(); }
	
	typename Container::size_type size() const { return _data.size(); }
	
	template< typename Compare >
	Type max( Compare comp ) const
	{
		typename Container::const_iterator iter = _data.begin();
		_max.second = *iter;
		for ( ++iter; iter != _data.end(); ++iter )
		{
			if ( !comp( *iter, _max.second ) )
			{
				_max.second = *iter;
			}
		}
		
		return _max.second;
	}
	
	Type max() const
	{
		if ( _max.first )
		{
			return _max.second;
		}
		
		_max.first = true;
		return max( typename std::less< Type >() );
	}
	
	template< typename Compare >
	Type min( Compare comp ) const
	{		
		typename Container::const_iterator iter = _data.begin();
		_min.second = *iter;
		for ( ++iter; iter != _data.end(); ++iter )
		{
			if ( comp( *iter, _max.second ) )
			{
				_min.second = *iter;
			}
		}
		
		_min.first = true;
		return _min.second;
	}
	
	Type min() const
	{
		if ( _min.first )
		{
			return _min.second;
		}
		
		_min.first = true;
		return min( typename std::less< Type >() );
	}
	
	Type average() const
	{
		if ( _average.first )
		{
			return _average.second;
		}
		
		typename Container::const_iterator iter = _data.begin();
		Type counter = Type(0);
		
		_average.second = *iter;
		counter = counter + 1;
		for ( ++iter; iter != _data.end(); ++iter )
		{
			_average.second += *iter;
			counter = counter + 1;
		}
		
		_average.first = true;
		return _average.second = _average.second/counter;
	}
	
	typename Container::size_type numberOfDifferentElements() const
	{
		if ( _nODE.first )
		{
			return _nODE.second;
		}
		
		std::set< Type > counter;
		
		for ( typename Container::const_iterator iter = _data.begin(); iter != _data.end(); ++iter )
		{
			counter.insert( counter.begin(), *iter );
		}
		
		_nODE.first = true;
		return _nODE.second = counter.size();
	}
	
	Type mostFrequentElement() const
	{
		std::map< Type, int > freq;
		
		Type max_item = *_data.begin();
		for ( typename Container::const_iterator iter = _data.begin(); iter != _data.end(); ++iter )
		{
			if ( ++freq[ *iter ] > freq[ max_item ] )
			{
				max_item = *iter;
			}
		}
		
		_mFE.first = true;
		return _mFE.second = max_item;
	}
	
	typename Container::size_type count( const Type &value ) const
	{
		return std::count( _data.begin(), _data.end(), value );
	}
	
private:
	void unvalidate()
	{
		_mFE.first = _nODE.first = _min.first = _max.first = _average.first = false;
	}
	
	Container _data;
	
	mutable std::pair< bool, Type > _max;
	mutable std::pair< bool, Type > _min;
	mutable std::pair< bool, Type > _average;
	mutable std::pair< bool, Type > _nODE;
	mutable std::pair< bool, Type > _mFE;
};

#endif // _STAT_