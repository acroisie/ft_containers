#pragma		once

#include	<memory>
#include	<map>
#include	"pair.hpp"
#include	"equal.hpp"
#include	"bidirectional_iterator.hpp"
#include	"reverse_iterator.hpp"
#include	"node.hpp"
#include	"AVL_tree.hpp"

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
		typedef	node<key_type, value_type>								node_type;
		typedef	node<key_type, value_type>*								node_ptr;
		typedef typename ft::bidirectional_iterator<value_type, node_type>			iterator;
		typedef typename ft::bidirectional_iterator<const value_type, node_type>	const_iterator;
		typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef typename ft::AVL_tree<key_type, mapped_type>			tree_type;

	private:
		key_compare		_comp;
		allocator_type	_alloc;
		tree_type		_tree;

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
		template<class InputIt>
		map(InputIt first, InputIt last, const Compare& comp = Compare(),
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
		map& operator=(const map& other)
		{
			clear();
			const_iterator it = other.begin();
			while(it != other.end())
				insert(*it++);
			return( *this );
		}

		//Allocator ----------------------------------------------------------//
		allocator_type			get_allocator() const {return (_alloc);}

	//Element access ---------------------------------------------------------//
		mapped_type&			at(const Key& key)
		{
			if (_tree.search(key))
				return (_tree.search(key));
			throw std::out_of_range("map"); 
		}
		const mapped_type&		at(const Key& key) const
		{
			if (_tree.search(key))
				return (_tree.search(key));
			throw std::out_of_range("map"); 
		}
		mapped_type&			operator[](const Key& key)
		{
			if (_tree.search(key))
				return (_tree.search(key)->_pair.second);
			_tree.insertPair(make_pair(key, T()));
			_tree.size++;
			return (_tree.search(key)->_pair.second);
		}

	//Iterators --------------------------------------------------------------//
		iterator				begin()
		{
			return iterator(_tree.minValue(_tree.root));
		}
		const_iterator			begin() const
		{
			return iterator(_tree.minValue(_tree.root));
		}
		iterator				end()
		{
			return iterator(_tree.maxValue(_tree.root));
		}
		const_iterator			end() const
		{
			return iterator(_tree.maxValue(_tree.root));
		}
		reverse_iterator		rbegin()
		{
			return reverse_iterator(_tree.maxValue(_tree.root));
		}
		const_reverse_iterator	rbegin() const
		{
			return const_reverse_iterator(_tree.maxValue(_tree.root));
		}
		reverse_iterator		rend()
		{
			return reverse_iterator(_tree.minValue(_tree.root));
		}
		const_reverse_iterator	rend() const
		{
			return const_reverse_iterator(_tree.minValue(_tree.root));
		}

	//Capacity ---------------------------------------------------------------//
		bool					empty() const {return (begin() == end());}
		size_type				size() const {return (_tree.size);}
		size_type				max_size() const {return (_alloc.max_size());}

	//Modifiers --------------------------------------------------------------//
		void					clear() {_tree.deleteFrom(_tree.root);}
		pair<iterator, bool>	insert(const value_type& value)
		{
			iterator tmp(_tree.search(_tree.root, value.first));
			_tree.insertPair(value);
			iterator it(_tree.search(_tree.root, value.first));
			if (it != NULL && tmp == NULL)
			{
				_tree.size++;
				return (ft::make_pair<iterator, bool>(it, true));
			}
			return (ft::make_pair<iterator, bool>(it, false));
		}
		iterator				insert(iterator pos, const value_type& value)
		{
				(void) pos;
				insert(value);
				return (iterator(_tree.search(value.first), &_tree));
		}
		template<class InputIt>
		void 					insert(InputIt first, InputIt last)
		{
			for (; first != last; first++)
				insert(*first);
		}
		iterator				erase(iterator pos)
		{
			_tree.deleteNode(pos);
		}
		iterator				erase(iterator first, iterator last)
		{
			for (; first != last;)
			{
				_tree.deleteNode((*first++).first);	
				_tree.size--;
			}
		}
		size_type				erase(const Key& key)
		{
			_tree.deleteNode(_tree, key);
		}
		void					swap(map& other)
		{
			_tree.swap(other._tree);
			std::swap(_alloc, other._alloc);
			std::swap(_comp, other._comp);
		}

	//Lookup -----------------------------------------------------------------//
		size_type				count(const Key& key) const
		{
			if (find(key))
				return (1);
			return (0);
		}
		iterator				find(const Key& key)
		{
			return (iterator(_tree.search(key), &_tree));
		}
		const_iterator			find(const Key& key) const
		{
			return (const_iterator(_tree.search(key), &_tree));
		}
		pair<iterator,iterator>	equal_range(const Key& key)
		{
			iterator	tmpBeginIt = end();
			iterator	tmpEndIt = end();

			iterator it = begin();

			for (; it != end(); it++)
			{
				if (!comp(it->first, key))
				{
					tmpBeginIt = it;
					break ;
				}
			}
			it = begin();
			for (; it != end(); it++)
			{
				if (comp(key, it->first))
				{
					tmpEndIt = it;
					break ;
				}
			}
			return (ft::make_pair(tmpBeginIt, tmpEndIt));
		}
		pair<const_iterator,
		const_iterator>			equal_range(const Key& key) const
		{
			iterator	tmpBeginIt = end();
			iterator	tmpEndIt = end();

			iterator it = begin();

			for (; it != end(); it++)
			{
				if (!comp(it->first, key))
				{
					tmpBeginIt = it;
					break ;
				}
			}
			it = begin();
			for (; it != end(); it++)
			{
				if (comp(key, it->first))
				{
					tmpEndIt = it;
					break ;
				}
			}
			return (ft::make_pair(tmpBeginIt, tmpEndIt));
		}
		iterator				lower_bound(const Key& key)
		{
			iterator it = begin();

			for (; it != end(); it++)
			{
				if (!comp(it->first, key))
					return (it);
			}
			return (it);
		}
		const_iterator			lower_bound(const Key& key) const
		{
			iterator it = begin();

			for (; it != end(); it++)
			{
				if (!comp(it->first, key))
					return (it);
			}
			return (it);
		}
		iterator				upper_bound(const Key& key)
		{
			iterator it = begin();

			for (; it != end(); it++)
			{
				if (!comp(key, it->first))
					return (it);
			}
			return (it);
		}
		const_iterator			upper_bound(const Key& key) const
		{
			iterator it = begin();

			for (; it != end(); it++)
			{
				if (!comp(key, it->first))
					return (it);
			}
			return (it);
		}

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