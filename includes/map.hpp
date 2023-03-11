#pragma		once

#include	<memory>
#include	"pair.hpp"
#include	"equal.hpp"
#include	"bidirectional_iterator.hpp"
#include	"reverse_iterator.hpp"
#include	"node.hpp"

namespace	ft
{
	template <class Key, class T, class Compare = std::less<Key>,
	class Allocator = std::allocator<pair<const Key, T> >
	> class map
	{
	public:
		typedef Key                                     								key_type;
		typedef T                                       								mapped_type;
		typedef pair<const key_type, mapped_type>       								value_type;
		typedef Compare                                 								key_compare;
		typedef Allocator                               								allocator_type;
		typedef typename allocator_type::reference      								reference;
		typedef typename allocator_type::const_reference								const_reference;
		typedef typename allocator_type::pointer        								pointer;
		typedef typename allocator_type::const_pointer  								const_pointer;
		typedef typename allocator_type::size_type      								size_type;
		typedef typename allocator_type::difference_type								difference_type;
		typedef	node<const key_type, mapped_type>										node_type;
		typedef	node<const key_type, mapped_type>*										node_ptr;
		typedef typename ft::bidirectional_iterator<value_type, node_type>				iterator;
		typedef typename ft::bidirectional_iterator<const value_type, const node_type>	const_iterator;
		typedef typename ft::reverse_iterator<iterator>									reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>							const_reverse_iterator;

	private:
		node_type		_root;
		size_type		_size;
		key_compare		_comp;
		allocator_type	_alloc;

	public:
//Member class ---------------------------------------------------------------//
        class value_compare
		{
            friend class map;

		public:
			typedef bool		result_type;
			typedef	value_type	first_argument_type;
			typedef value_type	second_argument_type;
		
		protected:
			Compare	comp;
			value_compare(Compare c): comp(c) {}
			bool operator()(const value_type& lhs, const value_type& rhs) const
			{
				return (comp(lhs.first, rhs.first));
			}

        };

//Member functions -----------------------------------------------------------//
	//Constructor/Destructor/Assign operator ---------------------------------//
		//Empty --------------------------------------------------------------//
		explicit map(const Compare& comp = key_compare(),
		const Allocator& alloc = allocator_type())
		: _comp(comp), _alloc(alloc) {}

		//Range --------------------------------------------------------------//
		template<class iterator>
		map(iterator first, iterator last, const Compare& comp = Compare(),
		const Allocator& alloc = Allocator())
		: _comp(comp), _alloc(alloc)
		{
			insert(first, last);
		}

		//Copy ---------------------------------------------------------------//
		map(const map& other, const Compare& comp = key_compare(),
		const Allocator& alloc = allocator_type())
		: _comp(comp), _alloc(alloc), _tree(NULL)
		{
			*this = other;
		}

		//Destructor ---------------------------------------------------------//
		~map() {}

		//Assign operator ----------------------------------------------------//
		map&					operator=(const map& other) {}

		//Allocator ----------------------------------------------------------//
		allocator_type			get_allocator() const {return (_alloc);}

	//Element access ---------------------------------------------------------//
		mapped_type&			at(const Key& key) {}
		const mapped_type&		at(const Key& key) const {}
		mapped_type&			operator[](const Key& key) {}

	//Iterators --------------------------------------------------------------//
		iterator				begin() {}
		const_iterator			begin() const {}
		iterator				end() {}
		const_iterator			end() const {}
		reverse_iterator		rbegin() {}
		const_reverse_iterator	rbegin() const {}
		reverse_iterator		rend() {}
		const_reverse_iterator	rend() const {}

	//Capacity ---------------------------------------------------------------//
		bool					empty() const {return (begin() == end());}
		size_type				size() const {return (_size);}
		size_type				max_size() const {return (_alloc.max_size());}

	//Modifiers --------------------------------------------------------------//
		void					clear() {}
		pair<iterator,bool>		insert (const value_type& val) {}
		iterator				insert (iterator position, const value_type& val) {}
		template <class iterator> 
		void					insert (iterator first, iterator last) {}
		iterator				erase(iterator pos) {}
		iterator				erase(iterator first, iterator last) {}
		size_type				erase(const Key& key) {}
		void					swap(map& other) {}

	//Lookup -----------------------------------------------------------------//
		size_type				count(const Key& key) const {}
		iterator				find(const Key& key) {}
		const_iterator			find(const Key& key) const {}
		pair<iterator,iterator>	equal_range(const Key& key) {}
		pair<const_iterator, const_iterator>	equal_range(const Key& key) const {}
		iterator				lower_bound(const Key& key) {}
		const_iterator			lower_bound(const Key& key) const {}
		iterator				upper_bound(const Key& key) {}
		const_iterator			upper_bound(const Key& key) const {}
	//Observers --------------------------------------------------------------//
		key_compare				key_comp() const {return (_comp);}
		// map::value_compare		value_comp() const {}

	};

//Non-member functions -------------------------------------------------------//
	//Operators --------------------------------------------------------------//
	template<class Key, class T, class Compare, class Alloc>
	bool operator==(const map<Key, T, Compare, Alloc>& lhs,
					const map<Key, T, Compare, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
	template<class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc>& lhs,
					const map<Key, T, Compare, Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}
	template<class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key, T, Compare, Alloc>& lhs,
					const map<Key, T, Compare, Alloc>& rhs)
	{
		return (lexicographical_compare(lhs.begin(), lhs.end(),
		rhs.begin(), rhs.end()));
	}
	template<class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc>& lhs,
					const map<Key, T, Compare, Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}
	template<class Key, class T, class Compare, class Alloc>
	bool operator>(const map<Key, T, Compare, Alloc>& lhs,
					const map<Key, T, Compare, Alloc>& rhs)
	{
		return (rhs < lhs);
	}
	template<class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc>& lhs,
					const map<Key, T, Compare, Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

}