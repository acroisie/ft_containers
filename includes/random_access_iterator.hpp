#pragma		once

#include	"iterator.hpp"

namespace	ft
{
	template<class T>
	class	random_access_iterator:
	public	ft::iterator<std::random_access_iterator_tag, T>
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
		random_access_iterator(): _ptr(NULL) {}
		random_access_iterator(pointer ptr): _ptr(ptr) {}
		random_access_iterator(const random_access_iterator& cpy) {*this = cpy;}
		~random_access_iterator() {}
		random_access_iterator&	operator=(const random_access_iterator obj)
		{
			_ptr = obj._ptr;
			return (*this);
		}

	//Equality/Inequality ----------------------------------------------------//
		// bool	operator==(const random_access_iterator &lhs, const random_access_iterator &rhs) const
		// {return (lhs._ptr == rhs._ptr);}
		// bool	operator!=(const random_access_iterator &lhs, const random_access_iterator &rhs) const 
		// {return (lhs._ptr != rhs._ptr);}

	//Dereferenced -----------------------------------------------------------//
		reference	operator*() const {return (*_ptr);}
		pointer		operator->() const {return (_ptr);}

		random_access_iterator	operator++(int)
		{
			_ptr++;
			return (random_access_iterator cpy(*this));
		}
		random_access_iterator& operator++()
		{
			_ptr++;
			return (*this);
		}
	};
}