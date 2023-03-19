#pragma		once

#include	"iterator.hpp"
#include	"iterator_traits.hpp"
#include	"node.hpp"

namespace	ft
{
	template<class I, class node>
	class bidirectional_iterator : public iterator<std::bidirectional_iterator_tag, I>
	{
	public:
		typedef typename bidirectional_iterator::difference_type		difference_type;
		typedef typename bidirectional_iterator::value_type				value_type;
		typedef typename bidirectional_iterator::pointer				pointer;
		typedef typename bidirectional_iterator::reference				reference;
		typedef typename bidirectional_iterator::iterator_category		iterator_category;

		typedef	node													node_type;
		typedef	iterator<std::bidirectional_iterator_tag, node_type>	node_it;
		typedef typename iterator_traits<node_it>::pointer 				node_pointer;

		operator bidirectional_iterator<const I, const node_type> () const
		{return (bidirectional_iterator<const I, const node_type>(_ptr));}

	private:
		node_pointer	_ptr;

	public:
//Member function ------------------------------------------------------------//
	//Constructor/Destructor/Assign content ----------------------------------//
		//Default ------------------------------------------------------------//
		bidirectional_iterator(): _ptr(NULL) {}

		//node ---------------------------------------------------------------//
		bidirectional_iterator(node_pointer begin) : _ptr(begin) {}

		//Copy ---------------------------------------------------------------//
		bidirectional_iterator(const bidirectional_iterator &obj)
		{
			_ptr = obj._ptr;
		}
		bidirectional_iterator(const iterator_traits<bidirectional_iterator<I, node> >&obj)
		:_ptr(obj._ptr) {}

		//Destructor ---------------------------------------------------------//
		~bidirectional_iterator() {}

		//Assign operator ----------------------------------------------------//
		bidirectional_iterator	&operator=(const bidirectional_iterator &obj)
		{
			if (this != &obj)
				_ptr = obj._ptr;
			return (*this);
		}

	//Member access operator -------------------------------------------------//
		pointer					base() const {return (_ptr);}

	//Dereference operators --------------------------------------------------//
		reference				operator*() const {return (_ptr->m_pair);}
		pointer					operator->() const {return (&(_ptr->m_pair));}

	//Increment/decrement operators ------------------------------------------//
	    bidirectional_iterator&	operator++()
        {
            if (_ptr->m_right)
            {
                _ptr = _ptr->m_right;
                while (_ptr->m_left)
                    _ptr = _ptr->m_left;
            }
            else
            {
                while (_ptr->m_up && _ptr->m_up->m_right == _ptr)
                    _ptr = _ptr->m_up;
                _ptr = _ptr->m_up;
            }
            return (*this);
        }
        bidirectional_iterator	operator++(int)
        {
            bidirectional_iterator tmp(*this);
            operator++();
            return (tmp);
        }
        bidirectional_iterator&	operator--()
        {
            if (_ptr->m_left)
            {
                _ptr = _ptr->m_left;
                while (_ptr->m_right)
                    _ptr = _ptr->m_right;
            }
            else
            {
                while (_ptr->m_up && _ptr->m_up->m_left == _ptr)
                    _ptr = _ptr->m_up;
                _ptr = _ptr->m_up;
            }
            return (*this);
        }
        bidirectional_iterator	operator--(int)
        {
            bidirectional_iterator tmp(*this);
            operator--();
            return (tmp);
        }
		node_pointer getPtr()
		{
			return (_ptr);
		}
	//Inequality relational operators ----------------------------------------//
		friend bool	operator==(const bidirectional_iterator &lhs,
		const bidirectional_iterator &rhs) {return (lhs._ptr == rhs._ptr);}
		friend bool	operator!=(const bidirectional_iterator &lhs,
		const bidirectional_iterator &rhs) {return (lhs._ptr != rhs._ptr);}

	};

}