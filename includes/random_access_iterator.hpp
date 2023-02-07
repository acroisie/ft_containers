#pragma		once

#include	"iterator.hpp"

namespace	ft
{
	template<class T>
	class	random_access_iterator: public ft::iterator<std::random_access_iterator_tag, T>
	{
		public:
			// typedef typename ft::iterator<std::random_access_iterator_tag, T>::difference_type		difference_type;
			// typedef typename ft::iterator<std::random_access_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::pointer				pointer;
			// typedef typename ft::iterator<std::random_access_iterator_tag, T>::reference			reference;
			// typedef typename ft::iterator<std::random_access_iterator_tag, T>::iterator_category	iterator_category;
		private:
			pointer	_ptr;
		public:
			random_access_iterator(void): _ptr(0) {}
			random_access_iterator(pointer ptr): _ptr(ptr) {}
			~random_access_iterator() {}
	};
}