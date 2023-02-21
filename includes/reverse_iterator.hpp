#pragma			once

#include		<memory>
#include		"iterator_traits.hpp"

namespace		ft
{
	template	<class Iter>
	class		reverse_iterator
	{
	public:
		typedef Iter			 										iterator_type;
		typedef typename ft::iterator_traits<Iter>::difference_type		difference_type;
		typedef typename ft::iterator_traits<Iter>::value_type			value_type;
		typedef typename ft::iterator_traits<Iter>::pointer				pointer;
		typedef typename ft::iterator_traits<Iter>::reference			reference;
		typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;

	protected:
		iterator_type	_it;

	public:
//Member functions -----------------------------------------------------------//
	// //Constructor/Destructor/Assign content ----------------------------------//
		reverse_iterator(): _it() {}
		explicit reverse_iterator(iterator_type it):_it(it) {}
		template <class Ite>
		reverse_iterator(const reverse_iterator<Ite>& rev_it): _it(rev_it.base()) {}
		~reverse_iterator() {}

		template <class U>
		reverse_iterator&	operator=(const reverse_iterator<U>& other)
		{
			_it = other._it;
			return (*this);
		}

	//Access -----------------------------------------------------------------//
		iterator_type		base() const {return (_it);}

	//Dereference ------------------------------------------------------------//
		template<class U>
		reference 			operator*() const {Iter tmp = _it; return (*--tmp);}
		pointer 			operator->() const {return &(operator*());}
		reference 			operator[](difference_type n) const {return (base()[-n - 1]);}

	//Increment --------------------------------------------------------------//
		reverse_iterator&	operator++() {return (_it--);}
		reverse_iterator	operator++(int)
		{
			reverse_iterator cpy(*this);
			_it--;
			return (cpy);
		}
		reverse_iterator&	operator+=(difference_type n)
		{
			_it -= n;
			return (*this);
		}
		reverse_iterator	operator+(difference_type n) const {return (_it - n);}

	//Decrement --------------------------------------------------------------//
		reverse_iterator&	operator--() {return (_it++);}
		reverse_iterator	operator--(int)
		{
			reverse_iterator cpy(*this);
			_it++;
			return (cpy);
		}
		reverse_iterator&	operator-=(difference_type n)
		{
			_it -= n;
			return (*this);
		}
		reverse_iterator	operator-(difference_type n) const {return (_it + n);}

	};
}

//Non-ember functions --------------------------------------------------------//
	//Relational operators ---------------------------------------------------//
	template<class Iterator1, class Iterator2>
	bool operator==(const ft::reverse_iterator<Iterator1>& lhs,
					const ft::reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template<class Iterator1, class Iterator2>
	bool operator!=(const ft::reverse_iterator<Iterator1>& lhs,
					const ft::reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() != rhs.base());
	}
	template<class Iterator1, class Iterator2>
	bool operator<(const ft::reverse_iterator<Iterator1>& lhs,
					const ft::reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() < rhs.base());
	}
	template<class Iterator1, class Iterator2>
	bool operator<=(const ft::reverse_iterator<Iterator1>& lhs,
					const ft::reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}
	template<class Iterator1, class Iterator2>
	bool operator>(const ft::reverse_iterator<Iterator1>& lhs,
					const ft::reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() > rhs.base());
	}
	template<class Iterator1, class Iterator2>
	bool operator>=(const ft::reverse_iterator<Iterator1>& lhs,
					const ft::reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	//Arithmetic operators ---------------------------------------------------//
	template<class Iter>
	typename ft::reverse_iterator<Iter>::difference_type
	operator+(typename ft::reverse_iterator<Iter>::difference_type n,
				const ft::reverse_iterator<Iter>& it)
	{
		return (ft::reverse_iterator<Iter>(it.base() - n));
	}
	template< class Iterator1, class Iterator2 >
	typename ft::reverse_iterator<Iterator1>::difference_type 
	operator-(const ft::reverse_iterator<Iterator1>& lhs,
				const ft::reverse_iterator<Iterator2>& rhs)
	{
		return (rhs.base() - lhs.base());
	}