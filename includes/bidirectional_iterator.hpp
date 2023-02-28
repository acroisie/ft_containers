#pragma		once
#include	"iterator.hpp"

namespace	ft
{
	template	<class I>
	class		bidirectional_iterator:
	public		ft::iterator<std::bidirectional_iterator_tag, I>
	{
	public:
		typedef typename ft::iterator<std::bidirectional_iterator_tag, I>
		::difference_type	difference_type;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, I>
		::value_type		value_type;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, I>
		::pointer			pointer;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, I>
		::reference			reference;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, I>
		::iterator_category	iterator_category;
	};

}