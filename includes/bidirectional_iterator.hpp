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
		operator bidirectional_iterator<const I> () const
		{return (bidirectional_iterator<const I>(_ptr));}

	private:
		pointer	_ptr;

	public:
//Member function ------------------------------------------------------------//
	//Constructor/Destructor/Assign content ----------------------------------//
		bidirectional_iterator(): _ptr(NULL) {}
		bidirectional_iterator(pointer ptr): _ptr(ptr) {}
		bidirectional_iterator(const bidirectional_iterator& cpy)
		: _ptr(cpy._ptr) {}

		~bidirectional_iterator() {}

		bidirectional_iterator&	operator=(const bidirectional_iterator& obj)
		{
			_ptr = obj._ptr;
			return (*this);
		}
		
	//Member access operator ------------------------------------------------//
		pointer					base() const {return (_ptr);}

	//Dereference operators -------------------------------------------------//
		reference				operator*() const {return (*_ptr);}
		pointer					operator->() const {return (_ptr);}

	//Increment/decrement operators -----------------------------------------//
		bidirectional_iterator&	operator++()
		{
			_ptr++;
			return (*this);
		}
		bidirectional_iterator	operator++(int)
		{
			bidirectional_iterator cpy(*this);
			_ptr++;
			return (cpy);
		}
		bidirectional_iterator&	operator--()
		{
			_ptr--;
			return (*this);
		}
		bidirectional_iterator	operator--(int)
		{
			bidirectional_iterator cpy = *this;
			_ptr--;
			return (cpy);
		}

	//Inequality relational operators ---------------------------------------//
		friend bool	operator==(const bidirectional_iterator &lhs,
		const bidirectional_iterator &rhs) {return (lhs._ptr == rhs._ptr);}
		friend bool	operator!=(const bidirectional_iterator &lhs,
		const bidirectional_iterator &rhs) {return (lhs._ptr != rhs._ptr);}

	};

}