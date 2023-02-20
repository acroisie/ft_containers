#pragma		once

#include	"iterator.hpp"

namespace	ft
{
	template	<class T>
	class		random_access_iterator:
	public		ft::iterator<std::random_access_iterator_tag, T>
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
		operator random_access_iterator<const T> () const
		{return (random_access_iterator<const T>(_ptr));}

	private:
		pointer	_ptr;

	public:
//Member function ------------------------------------------------------------//
	//Constructor/Destructor/Assign content ----------------------------------//
		random_access_iterator(): _ptr(NULL) {}
		random_access_iterator(pointer ptr): _ptr(ptr) {}
		random_access_iterator(const random_access_iterator& cpy)
		: _ptr(cpy._ptr) {}
		~random_access_iterator() {}

		random_access_iterator&	operator=(const random_access_iterator& obj)
		{
			_ptr = obj._ptr;
			return (*this);
		}
		
//Property -------------------------------------------------------------------//
	//Equality/Inequality ----------------------------------------------------//
		friend bool	operator==(const random_access_iterator &lhs,
		const random_access_iterator &rhs) {return (lhs._ptr == rhs._ptr);}
		friend bool	operator!=(const random_access_iterator &lhs,
		const random_access_iterator &rhs) {return (lhs._ptr != rhs._ptr);}

	//Dereference ------------------------------------------------------------//
		reference	operator*() const {return (*_ptr);}
		pointer		operator->() const {return (_ptr);}
		reference	operator[](difference_type n) const {return (*(_ptr + n));}

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
		random_access_iterator&	operator+=(difference_type n)
		{
			_ptr += n;
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
		random_access_iterator&	operator-=(difference_type n)
		{
			_ptr -= n;
			return (*this);
		}

	//Arithmetic operators ---------------------------------------------------//
		friend random_access_iterator
		operator+(const random_access_iterator lhs, difference_type n)
		{
			random_access_iterator	cpy(lhs);
			cpy += n;
			return (cpy);
		}
		friend random_access_iterator
		operator+(difference_type n, const random_access_iterator rhs)
		{
			random_access_iterator	cpy(rhs);
			cpy += n;
			return (cpy);
		}
		friend random_access_iterator
		operator-(const random_access_iterator lhs, difference_type n)
		{
			random_access_iterator	cpy(lhs);
			cpy -= n;
			return (cpy);
		}
		friend random_access_iterator
		operator-(difference_type n, const random_access_iterator rhs)
		{
			random_access_iterator	cpy(rhs);
			cpy -= n;
			return (cpy);
		}

	//Inequality relational operators ----------------------------------------//
		friend bool	operator<(const random_access_iterator &lhs,
		const random_access_iterator &rhs) {return (lhs._ptr < rhs._ptr);}
		friend bool	operator>(const random_access_iterator &lhs,
		const random_access_iterator &rhs) {return (lhs._ptr > rhs._ptr);}
		friend bool	operator<=(const random_access_iterator &lhs,
		const random_access_iterator &rhs) {return (lhs._ptr <= rhs._ptr);}
		friend bool	operator>=(const random_access_iterator &lhs,
		const random_access_iterator &rhs) {return (lhs._ptr >= rhs._ptr);}

	//Assignment operations --------------------------------------------------//
		random_access_iterator	operator+(int n) {return (_ptr + n);}
		random_access_iterator	operator-(int n) {return (_ptr - n);}
		difference_type 		operator-(const random_access_iterator& lhs) const
		{
			return (_ptr - lhs._ptr);
		}

	};
}