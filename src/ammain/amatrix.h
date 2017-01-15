/**************************************************************************
 *
 * Author: Kókai Péter
 * E-mail: kokaipeter[a]gmail[d]com
 *
 * Test:   
 *
 **************************************************************************/
#ifndef _ASSOC_MATRIX_
#define _ASSOC_MATRIX_

#include <map>
#include <vector>
#include <set>



template< typename T1 >
struct not_bool
{
	typedef T1 type;
};



class Bool
{
public:
    Bool(): m_value(){}
    Bool( bool value ) : m_value(value){}

    operator bool() const { return m_value;}
    bool* operator& () { return &m_value; }
	const bool * const operator& () const { return &m_value; }

private:
    bool m_value;
};


template< >
struct not_bool<bool>
{
	typedef Bool type;
};




	
	
template< typename T1,
		  typename T2 >
class assoc_matrix
{
public:
	
	void add_row_column( const T1 &item )
	{
		if ( row.count( item ) > 0 ) return;
		
		const unsigned int size = 1+_data.size();
		std::vector< std::vector< typename not_bool< T2 >::type > > data_tmp = _data;
		std::map< typename not_bool<T1>::type, unsigned int > row_tmp = row;
		//--
		row_tmp[ item ] = size-1;
		data_tmp.resize( size );
		for ( unsigned int i = 0; i<size;++i ) data_tmp[i].resize( size );
		//--
		_data.swap( data_tmp );
		row.swap( row_tmp );
	}
	
	void set( const T1 &ind0, const T1 &ind1, const typename not_bool< T2 >::type &val )
	{
		std::vector< std::vector< typename not_bool< T2 >::type > > tmp_data = _data;
		//--
		tmp_data[ row[ind0] ][ row[ind1] ] = val;
		//--
		_data.swap( tmp_data );
	}
	
	unsigned int size() const { return _data.size()*_data.size(); }
	
	typename not_bool< T2 >::type& at( const T1 &ind0, const T1 &ind1 )
	{
		if (trans)
		{
			return _data.at(row.at(ind1)).at(row.at(ind0));
		}
		else
		{
			return _data.at(row.at(ind0)).at(row.at(ind1));
		}
	}
	
	typename not_bool< T2 >::type at( const T1 &ind0, const T1 &ind1 ) const
	{
		if (trans)
		{
			return _data.at(row.at(ind1)).at(row.at(ind0));
		}
		else
		{
			return _data.at(row.at(ind0)).at(row.at(ind1));
		}
	}
	
	typename not_bool< T2 >::type& operator()( const T1 &ind0, const T1 &ind1 ) 	  { return this->at( ind0, ind1 ); }
	typename not_bool< T2 >::type operator()( const T1 &ind0, const T1 &ind1 ) const { return this->at( ind0, ind1 ); }
	
	void transpose() { if (trans) trans=false; else trans=true; }//trans=!trans nem mukodott 
	
	void erase( const T1 &item )
	{
		unsigned int x = row[item];		
		unsigned int y = cul[item];
		
		std::vector< std::vector< typename not_bool< T2 >::type > > data_tmp = _data;
		std::map< typename not_bool<T1>::type, unsigned int > row_tmp = row;
		//--
					
		data_tmp.erase( data_tmp.begin() + x );
		row_tmp.erase( row_tmp.find( item ) );
		//--
		
		_data.swap( data_tmp );
		row.swap( row_tmp );
	}
	
	assoc_matrix<T1,typename not_bool< T2 >::type> operator+( assoc_matrix<T1,typename not_bool< T2 >::type> &o )
	{
		assoc_matrix<T1,typename not_bool< T2 >::type> ret = o;
		
		std::set< T1 > uniq;
		
		for ( typename std::map< T1, unsigned int >::iterator i = this->row.begin(); i != this->row.end(); ++i )
		{
			uniq.insert( i->first );
		}
		
		for ( typename std::map< T1, unsigned int >::iterator i = o.row.begin(); i != o.row.end(); ++i )
		{
			uniq.insert( i->first );
		}
		
		for ( typename std::set< T1 >::iterator i = uniq.begin(); i != uniq.end(); ++i )
		{
			ret.add_row_column( *i );
		}
		
		for ( typename std::set< T1 >::iterator i = uniq.begin(); i != uniq.end(); ++i )
		{
			for ( typename std::set< T1 >::iterator j = uniq.begin(); j != uniq.end(); ++j )
			{
				ret( *i, *j ) = exist( *i, *j ) + o.exist( *i, *j );
			}
		}
		
		return ret;
	}
	
protected:
	typename not_bool< T2 >::type exist( const T1 &ind0, const T1 &ind1 )
	{
		if ( row.count( ind0 ) > 0 && row.count( ind1 ) > 0 )
		{
			return at( ind0, ind1 );
		}
		
		return typename not_bool< T2 >::type(0);
	}
private:
	std::vector< std::vector< typename not_bool< T2 >::type > > _data;
	std::map< T1, unsigned int > row;//_data[ row[ind1] ][ cul[ ind2 ] ]
	std::map< T1, unsigned int > cul;
	bool trans;
};



template< typename T1,
          typename T2 >
class AssocMatrix
{
public:
	T2& get( const T1 &ind0, const T1 &ind1 )       { return _data.at( ind0, ind1 ); }
	T2  get( const T1 &ind0, const T1 &ind1 ) const { return _data.at( ind0, ind1 ); }
	
	void set( const T1 &ind0, const T1 &ind1, const T2 &value )
	{
		_data.add_row_column( ind0 );
		_data.add_row_column( ind1 );
		
		_data.set( ind0, ind1, value );
		std::cout << _data( ind0, ind1 ) << "," << value << std::endl;
	}
private:
	assoc_matrix< T1, T2 > _data;
};




#endif //_ASSOC_MATRIX_