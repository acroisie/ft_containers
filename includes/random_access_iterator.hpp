#pragma		once

#include	"iterator.hpp"

namespace	ft
{
	template<class T>
	class	ra_iterator:
	public ft::iterator<std::random_access_iterator_tag, T>
	{
	public:
		typedef typename ft::iterator<std::random_access_iterator_tag, T>
		::difference_type	difference_type;
		typedef typename ft::iterator<std::random_access_iterator_tag, T>
		::value_type		value_type;
		typedef typename ft::iterator<std::random_access_iterator_tag, T>
		::pointer			pointer;
		typedef typename ft::iterator<std::random_access_iterator_tag, T>
		::reference			reference;
		typedef typename ft::iterator<std::random_access_iterator_tag, T>
		::iterator_category	iterator_category;

	private:
		pointer	_ptr;

	public:
//Property -------------------------------------------------------------------//
	//Constructor/Destructor -------------------------------------------------//
		ra_iterator(): _ptr(NULL) {}
		ra_iterator(pointer ptr): _ptr(ptr) {}
		ra_iterator(const ra_iterator& cpy) {*this = cpy;}
		~ra_iterator() {}
		ra_iterator&	operator=(const ra_iterator obj)
		{
			_ptr = obj._ptr;
			return (*this);
		}

	//Equality/Inequality ----------------------------------------------------//
	bool	operator==(ra_iterator const &obj) const {return (_ptr == obj._ptr);}
	bool	operator!=(ra_iterator const &obj) const {return (_ptr != obj._ptr);}
	};
}