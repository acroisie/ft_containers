#pragma		once

#include	<memory>
#include	<map>
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
		typedef Key                                     				key_type;
		typedef T                                       				mapped_type;
		typedef pair<const key_type, mapped_type>       				value_type;
		typedef Compare                                 				key_compare;
		typedef Allocator                               				allocator_type;
		typedef typename allocator_type::reference      				reference;
		typedef typename allocator_type::const_reference				const_reference;
		typedef typename allocator_type::pointer        				pointer;
		typedef typename allocator_type::const_pointer  				const_pointer;
		typedef typename allocator_type::size_type      				size_type;
		typedef typename allocator_type::difference_type				difference_type;
		typedef typename ft::bidirectional_iterator<value_type>			iterator;
		typedef typename ft::bidirectional_iterator<const value_type>	const_iterator;
		typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;

	private:
		value_type*		_data;
		size_type		_size;
		size_type		_capacity;
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
		//Default ------------------------------------------------------------//
		map(): _data(NULL) {}

		//Empty --------------------------------------------------------------//
		explicit map(const Compare& comp, const Allocator& alloc = Allocator())
		: _data(NULL) {}

		//Range --------------------------------------------------------------//
		template<class InputIt>
		map(InputIt first, InputIt last, const Compare& comp = Compare(),
			const Allocator& alloc = Allocator()): _data(NULL) {}

		//Copy ---------------------------------------------------------------//
		map(const map& other): _data(NULL)
		{
			*this = other;
		}

		//Destructor ---------------------------------------------------------//
		~map() {}

		//Assign operator ----------------------------------------------------//
		map& operator=(const map& other)
		{
			_data = other._data;
			return *this;
		}

		//Allocator ----------------------------------------------------------//
		allocator_type			get_allocator() const {return (_alloc);}

	//Element access ---------------------------------------------------------//
		mapped_type&			at(const Key& key) {}
		const mapped_type&		at(const Key& key) const {}
		mapped_type&			operator[](const Key& key) {}

	//Iterators --------------------------------------------------------------//
		iterator				begin() {return iterator(_data.begin());}
		const_iterator			begin() const {return iterator(_data.begin());}
		iterator				end() {return iterator(_data.end());}
		const_iterator			end() const {return iterator(_data.end());}
		reverse_iterator		rbegin() {return reverse_iterator(_data.rbegin());}
		const_reverse_iterator	rbegin() const {return const_reverse_iterator(_data.rbegin());}
		reverse_iterator		rend() {return reverse_iterator(_data.rend());}
		const_reverse_iterator	rend() const {return const_reverse_iterator(_data.rend());}

	//Capacity ---------------------------------------------------------------//
		bool					empty() const {return (begin() == end());}
		size_type				size() const {return (_size);}
		size_type				max_size() const {return (_capacity);}

	//Modifiers --------------------------------------------------------------//
		void					clear() {}
		pair<iterator, bool>	insert(const value_type& value) {}
		iterator				insert(iterator pos, const value_type& value) {}
		template<class InputIt>
		void 					insert(InputIt first, InputIt last) {}
		iterator				erase(iterator pos) {}
		iterator				erase(iterator first, iterator last) {}
		size_type				erase(const Key& key) {}
		void					swap(map& other) {}

	//Lookup -----------------------------------------------------------------//
		size_type				count(const Key& key) const {}
		iterator				find(const Key& key) {}
		const_iterator			find(const Key& key) const {}
		pair<iterator,iterator>	equal_range(const Key& key) {}
		pair<const_iterator,
		const_iterator>			equal_range(const Key& key) const {}
		iterator				lower_bound(const Key& key) {}
		const_iterator			lower_bound(const Key& key) const {}
		iterator				upper_bound(const Key& key) {}
		const_iterator			upper_bound(const Key& key) const {}

	//Observers --------------------------------------------------------------//
		key_compare				key_comp() const {}
		map::value_compare		value_comp() const {}

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