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
		random_access_iterator(const random_access_iterator& cpy): _ptr(cpy._ptr) {}
		~random_access_iterator() {}
		random_access_iterator&	operator=(const random_access_iterator& obj)
		{
			_ptr = obj._ptr;
			return (*this);
		}

	//Equality/Inequality ----------------------------------------------------//
		friend bool	operator==(const random_access_iterator &lhs,
		random_access_iterator &rhs) {return (lhs._ptr == rhs._ptr);}
		friend bool	operator!=(const random_access_iterator &lhs,
		random_access_iterator &rhs) {return (lhs._ptr != rhs._ptr);}

	//Dereference ------------------------------------------------------------//
		reference	operator*() const {return (*_ptr);}
		pointer		operator->() const {return (_ptr);}

	//Increment --------------------------------------------------------------//
		random_access_iterator	operator++(int)
		{
			random_access_iterator cpy(*this);
			_ptr++;
			return (cpy);
		}
		random_access_iterator&	operator++()
		{
			_ptr++;
			return (*this);
		}

	//Decrement --------------------------------------------------------------//
		random_access_iterator	operator--(int)
		{
			random_access_iterator cpy = *this;
			_ptr--;
			return (cpy);
		}
		random_access_iterator&	operator--()
		{
			_ptr--;
			return (*this);
		}

	//Arithmetic operators ---------------------------------------------------//
		friend random_access_iterator	
		operator+(random_access_iterator rhs, int n)
		{
			rhs._ptr += n;
			return (rhs);
		}
		friend random_access_iterator	
		operator+(int n, random_access_iterator rhs)
		{
			rhs._ptr += n;
			return (rhs);
		}
		friend random_access_iterator	
		operator-(random_access_iterator rhs, int n)
		{
			rhs._ptr -= n;
			return (rhs);
		}
		friend random_access_iterator	
		operator-(int n, random_access_iterator rhs)
		{
			rhs._ptr += n;
			return (rhs);
		}

	//Inequality relational operators ----------------------------------------//
		friend bool	operator<(const random_access_iterator &lhs,
		random_access_iterator &rhs) {return (lhs._ptr < rhs._ptr);}
		friend bool	operator>(const random_access_iterator &lhs,
		random_access_iterator &rhs) {return (lhs._ptr > rhs._ptr);}
		friend bool	operator<=(const random_access_iterator &lhs,
		random_access_iterator &rhs) {return (lhs._ptr <= rhs._ptr);}
		friend bool	operator>=(const random_access_iterator &lhs,
		random_access_iterator &rhs) {return (lhs._ptr >= rhs._ptr);}

	};
}