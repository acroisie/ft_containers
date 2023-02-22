#pragma			once

#include		<memory>
#include		"iterator_traits.hpp"

namespace		ft
{
	template	<class Iter>
	class		reverse_iterator
	{
	public:
		typedef Iter iterator_type;	
		typedef typename iterator_traits<Iter>::difference_type		difference_type;
		typedef typename iterator_traits<Iter>::value_type			value_type;
		typedef typename iterator_traits<Iter>::pointer				pointer;
		typedef typename iterator_traits<Iter>::reference			reference;
		typedef typename iterator_traits<Iter>::iterator_category	iterator_category;

	protected:
		Iter _it;

	public:
//Member functions -----------------------------------------------------------//
	//Constructor/Destructor/Assign operator ---------------------------------//
		reverse_iterator(): _it() {}
		explicit reverse_iterator(Iter it): _it(it) {}
		template <class Iter2>
		reverse_iterator(const reverse_iterator<Iter2> &rev_it)
		: _it(rev_it.base()) {}

		~reverse_iterator() {}

		reverse_iterator	&operator=(const reverse_iterator<Iter> &other)
		{
			_it = other._it;
			return (*this);
		}

	//Member access operator ------------------------------------------------//
		Iter				base() const {return (_it);}

	//Dereference operators -------------------------------------------------//
		reference			operator*() const
		{
			Iter tmp = _it;
			return (*--tmp);
		}
		pointer				operator->() const {return &(operator*());}
		reference			operator[](difference_type n) const
		{
			return (base()[-n - 1]);
		}

	//Increment/decrement operators -----------------------------------------//
		reverse_iterator	&operator++()
		{
			_it--;
			return (*this);
		}
		reverse_iterator	operator++(int)
		{
			reverse_iterator<Iter> tmp(*this);
			_it--;
			return (tmp);
		}
		reverse_iterator	&operator+=(difference_type n)
		{
			_it -= n;
			return (*this);
		}
		reverse_iterator	operator+(difference_type n) const
		{
			return reverse_iterator(_it - n);
		}
		reverse_iterator	&operator--()
		{
			_it++;
			return (*this);
		}
		reverse_iterator	operator--(int)
		{
			reverse_iterator<Iter> tmp(*this);
			_it++;
			return (tmp);
		}
		reverse_iterator	&operator-=(difference_type n)
		{
			_it += n;
			return (*this);
		}
		reverse_iterator	operator-(difference_type n) const
		{
			return reverse_iterator(_it + n);
		}
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