#ifndef TEMPLATE_IF__H
#define TEMPLATE_IF__H

template< bool Cond,
          typename True,
          typename False>
struct IF_
{
	typedef True type;
};

template< typename True,
          typename False>
struct IF_< false,
            True,
			False >
{
	typedef False type;
};

#endif
