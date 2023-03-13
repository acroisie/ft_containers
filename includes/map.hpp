#pragma		once

#include	<memory>
#include	"pair.hpp"
#include	"equal.hpp"
#include	"lexicographical_compare.hpp"
#include	"bidirectional_iterator.hpp"
#include	"reverse_iterator.hpp"
#include	"node.hpp"

namespace	ft
{
	template <class Key, class T, class Compare = std::less<Key>,
	class Allocator = std::allocator<node<ft::pair<const Key, T> > >
	> class map
	{
	public:
		typedef Key                                     								key_type;
		typedef T                                       								mapped_type;
		typedef pair<const key_type, mapped_type>       								value_type;
		typedef Compare		                            								key_compare;
		typedef Allocator                               								allocator_type;
		typedef typename allocator_type::reference      								reference;
		typedef typename allocator_type::const_reference								const_reference;
		typedef typename allocator_type::pointer        								pointer;
		typedef typename allocator_type::const_pointer  								const_pointer;
		typedef typename allocator_type::size_type      								size_type;
		typedef typename allocator_type::difference_type								difference_type;
		typedef	node<value_type>														node_type;
		typedef	node<value_type>*														node_pointer;
		typedef typename ft::bidirectional_iterator<value_type, node_type>				iterator;
		typedef typename ft::bidirectional_iterator<const value_type, const node_type>	const_iterator;
		typedef typename ft::reverse_iterator<iterator>									reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>							const_reverse_iterator;

	private:
		node_pointer	_root;
		size_type		_size;
		key_compare		_comp;
		allocator_type	_alloc;

	public:
//Public member class --------------------------------------------------------//
        class value_compare
		{
            friend class map;

		public:
			typedef bool		result_type;
			typedef	value_type	first_argument_type;
			typedef value_type	second_argument_type;
		
			Compare	comp;
			value_compare(Compare c): comp(c) {}
			bool operator()(const value_type& lhs, const value_type& rhs) const
			{
				return (comp(lhs.first, rhs.first));
			}

        };

//Public member functions ----------------------------------------------------//
	//Constructor/Destructor/Assign operator ---------------------------------//
		//Empty --------------------------------------------------------------//
		explicit map(const Compare& comp = key_compare(),
		const Allocator& alloc = allocator_type())
		: _root(NULL), _size(0), _comp(comp), _alloc(alloc) {}

		//Range --------------------------------------------------------------//
		template<class iterator>
		map(iterator first, iterator last, const Compare& comp = Compare(),
		const Allocator& alloc = Allocator())
		: _root(NULL), _size(0), _comp(comp), _alloc(alloc)
		{
			insert(first, last);
		}

		//Copy ---------------------------------------------------------------//
		map(const map& other, const Compare& comp = key_compare(),
		const Allocator& alloc = allocator_type())
		: _root(NULL), _size(0), _comp(comp), _alloc(alloc)
		{
			*this = other;
		}

		//Destructor ---------------------------------------------------------//
		~map() {clearTree();}

		//Assign operator ----------------------------------------------------//
		map&	operator=(const map& other) 
		{
			clear();
			const_iterator beg = other.begin();
			while(beg != other.end())
				insert(*beg++);
			return (*this);
		}

		//Allocator ----------------------------------------------------------//
		allocator_type			get_allocator() const {return (_alloc);}

	//Element access ---------------------------------------------------------//
		mapped_type&			at (const key_type& key)
		{ 
			if (search(key))
				return (search(key));
			throw std::out_of_range("map"); 
		}
		const mapped_type&		at (const key_type& k) const
		{
			if (search(k))
				return (search(k));
			throw std::out_of_range("map"); 
		}
		mapped_type&			operator[](const key_type& key)
		{
			if (search(key))
				return (search(key)->m_pair.second);
			insertPair(ft::make_pair(key, T()));
			_size++;
			return (search(key)->m_pair.second);
		}

	//Iterators --------------------------------------------------------------//
		iterator				begin()
		{
			return iterator(nodeWithMimumValue(_root));
		}
		const_iterator			begin() const
		{
			return iterator(nodeWithMimumValue(_root));
		}
		iterator				end()
		{
			return (iterator(nodeWithMaxmumValue(_root)));
		}
		const_iterator			end() const
		{
			return (iterator(nodeWithMaxmumValue(_root)));
		}
		reverse_iterator		rbegin()
		{
			return reverse_iterator(begin());
		}
		const_reverse_iterator	rbegin() const
		{
			return const_reverse_iterator(begin());
		}
		reverse_iterator		rend()
		{
			return reverse_iterator(end());
		}
		const_reverse_iterator	rend() const
			{
				return const_reverse_iterator(end());
			}

	//Capacity ---------------------------------------------------------------//
		bool					empty() const {return (begin() == end());}
		size_type				size() const {return (_size);}
		size_type				max_size() const {return (_alloc.max_size());}

	//Modifiers --------------------------------------------------------------//
		void					clear() {clearTree();}
		pair<iterator,bool>		insert (const value_type& val)
		{
			iterator tmp(search(val.first));
			insertPair(val);
			iterator it(search(val.first));
			if (it != NULL && tmp == NULL)
			{
				_size++;
				return (ft::make_pair<iterator, bool>(it, true));
			}
			return (ft::make_pair<iterator, bool>(it, false));
		}
		iterator				insert (iterator position, const value_type& val)
		{
			(void) position;
			insert(val);
			return (iterator(search(val.first)));
		}
		template <class iterator> 
		void					insert (iterator first, iterator last)
		{
			for (; first != last; first++)
				insert(*first);
		}
		iterator				erase(iterator pos)
		{
			iterator tmp = pos;
			deleteNode(_root,(*pos).first);
			return (pos);
		}
		iterator				erase(iterator first, iterator last)
		{
			while(first != last)
			{
				if (first->first)
				{
					iterator tmp = first;
					erase((first++)->first);
					return (tmp);
				}
			}
			return (NULL);
		}
		size_type				erase(const Key& key)
		{
			if(search(key))
				{
					deleteNode(_root, key);
					return (1);
				}
				return(0);
		}
		void					swap(map& other)
		{
			node_pointer 	root = other._root;
			size_type 		size = other._size;
			key_compare		comp = other._comp;
			allocator_type	alloc = other._alloc;

			other._size = size;
			other._root = root;
			other._comp = comp;
			other._alloc = alloc;

			_size = size;
			_root = root;
			_comp = comp;
			_alloc = alloc;
		}

	//Lookup -----------------------------------------------------------------//
		size_type				count(const Key& key) const
		{
			return ((find(key) != end()) ? 1 : 0);
		}
		iterator				find(const Key& key)
		{
			return (iterator(search(key)));
		}
		const_iterator			find(const Key& key) const
		{
			return (const_iterator(search(key)));
		}
		pair<iterator,iterator>	equal_range(const Key& key)
		{
			return (make_pair<iterator, iterator>(lower_bound(key),upper_bound(key)));
		}
		pair<const_iterator,
		const_iterator>			equal_range(const Key& key) const
		{
			return (make_pair<const_iterator, const_iterator>(lower_bound(key),upper_bound(key)));			
		}
		iterator				lower_bound(const Key& key)
		{
			iterator it = begin();
			while (it != end())
			{
				if (_comp(it->first, key))
					it++;
				else
					return (it);
			}
			return (it);
		}
		const_iterator			lower_bound(const Key& key) const
		{
			const_iterator it = begin();
			while (it != end())
			{
				if (_comp(it->first, key))
					it++;
				else
					return(it);
			}
			return (it);
		}
		iterator				upper_bound(const Key& key) 
		{
			iterator it = begin();
			while (it != end())
			{
				if (_comp(it->first, key) || key == it->first)
					it++;
				else
					return (it);
			}
			return (it);
		}
		const_iterator			upper_bound(const Key& key) const 
		{
			const_iterator it = begin();
			while (it != end())
			{
				if (_comp(it->first, key) || key == it->first)
					it++;
				else
					return (it);
			}
			return (it);
		}

	//Observers --------------------------------------------------------------//
		key_compare				key_comp() const {return (_comp);}
		value_compare			value_comp() const
		{
			return (value_compare(key_comp()));
		}
	
	private:
//Public member functions ----------------------------------------------------//
	//AVL-Tree implementation ------------------------------------------------//
		int						height(node_pointer N)
		{
			if (N == NULL)
				return (0);
			return (N->m_height);
		}
		size_type 				max(size_type a, size_type b)
		{
			return ((a > b) ? a : b);
		}
		node_pointer			newNode(key_type key, mapped_type value)
		{
			node_pointer N = _alloc.allocate(1);
			_alloc.construct(N, node<value_type>(ft::make_pair(key, value)));
			return (N);
		}
		node_pointer			rightRotate(node_pointer y)
		{
			node_pointer x = y->m_left;
			node_pointer T2 = x->m_right;
			x->m_right = y;
			y->m_left = T2;
			y->m_height = max(height(y->m_left), height(y->m_right)) + 1;
			x->m_height = max(height(x->m_left), height(x->m_right)) + 1;
			return (x);
		}
		node_pointer			leftRotate(node_pointer x)
		{
			node_pointer y = x->m_right;
			node_pointer T2 = y->m_left;
			y->m_left = x;
			x->m_right = T2;
			x->m_height = max(height(x->m_left), height(x->m_right)) + 1;
			y->m_height = max(height(y->m_left), height(y->m_right)) + 1;
			return (y);
		}
		int						getBalanceFactor(node_pointer N)
		{
			if (N == NULL)
				return (0);
			return (height(N->m_left) - height(N->m_right));
		}
		node_pointer			insertNode(node_pointer N, key_type key, mapped_type value)
		{
			//Find the correct postion and insert the node
			if (N == NULL)
				return (newNode(key, value));
			if (_comp(key, N->m_pair.first))
			{
				N->m_left = insertNode(N->m_left, key, value);
				if (N->m_left)
					N->m_left->m_up = N;
			}
			else if (_comp(N->m_pair.first, key))
			{
				N->m_right = insertNode(N->m_right, key, value);
				if (N->m_right)
					N->m_right->m_up = N;
			}
			else
				return (N);

			//Update the balance factor of each node and balance the tree
			N->m_height = 1 + max(height(N->m_left), height(N->m_right));
			int balanceFactor = getBalanceFactor(N);
			if (balanceFactor > 1)
			{
				if (_comp(key, N->m_left->m_pair.first))
				{
					return (rightRotate(N));
				}
				else if (_comp(N->m_left->m_pair.first, key))
				{
					N->m_left = leftRotate(N->m_left);
					if (N->m_left)
						N->m_left->m_up = NULL;
					return (rightRotate(N));
				}
			}
			if (balanceFactor < -1)
			{
				if (_comp(N->m_right->m_pair.first, key))
				{
					return (leftRotate(N));
				}
				else if (_comp(key, N->m_right->m_pair.first))
				{
					N->m_right = rightRotate(N->m_right);
					if (N->m_right)
						N->m_right->m_up = NULL;
					return (leftRotate(N));
				}
			}
			return (N);
		}
		void					insertPair(value_type pair)
		{
			_root = insertNode(_root, pair.first, pair.second);
			if (_root)
				_root->m_up = NULL;
		}
		node_pointer			nodeWithMimumValue(node_pointer N)
		{
			node_pointer current = N;
			while (current->m_left != NULL)
				current = current->m_left;
			return (current);
		}
		node_pointer			nodeWithMimumValue(node_pointer N) const
		{
			node_pointer current = N;
			while (current->m_left != NULL)
				current = current->m_left;
			return (current);
		}
		node_pointer			nodeWithMaxmumValue(node_pointer N)
		{
			node_pointer current = N;
			while (current->m_right != NULL)
				current = current->m_right;
			return (current);
		}
		node_pointer			nodeWithMaxmumValue(node_pointer N) const
		{
			node_pointer current = N;
			while (current->m_right != NULL)
				current = current->m_right;
			return (current);
		}
		node_pointer			deleteNode(node_pointer N, key_type key)
		{
			if (N == NULL)
				return (NULL);

			if (_comp(key, N->m_pair.first))
				N->m_left = deleteNode(N->m_left, key);
			else if (_comp(N->m_pair.first, key))
				N->m_right = deleteNode(N->m_right, key);
			else
			{
				if (N->m_left == NULL)
					return (N->m_right);
				else if (N->m_right == NULL)
					return (N->m_left);
				else
				{
					node_pointer temp = nodeWithMimumValue(N->m_right);
					N= temp;
					N->m_right = deleteNode(N->m_right, temp->m_pair.first);
				}
			}

			N->m_height = 1 + max(height(N->m_left), height(N->m_right));

			int balanceFactor = getBalanceFactor(N);

			if (balanceFactor > 1 && getBalanceFactor(N->m_left) >= 0)
				return (rightRotate(N));

			if (balanceFactor < -1 && getBalanceFactor(N->m_right) <= 0)
				return (leftRotate(N));

			if (balanceFactor > 1 && getBalanceFactor(N->m_left) < 0)
			{
				N->m_left = leftRotate(N->m_left);
				return (rightRotate(N));
			}

			if (balanceFactor < -1 && getBalanceFactor(N->m_right) > 0)
			{
				N->m_right = rightRotate(N->m_right);
				return (leftRotate(N));
			}

			return (N);
		}
		node_pointer			search(const key_type key) const
		{
			return (search(_root, key));
		}
		node_pointer			search(node_pointer N, const key_type key) const
		{
			if (N)
			{
				if (key == N->m_pair.first)
					return (N);
				else if (_comp(key, N->m_pair.first))
					return (search(N->m_left, key));
				else
					return (search(N->m_right, key));
			}
			return (NULL);
		}
		void					clearFrom(node_pointer N)
		{
			if (N == NULL)
				return;
			if (N->m_left)
				clearFrom(N->m_left);
			if (N->m_right)
				clearFrom(N->m_right);
			_alloc.destroy(N);
			_alloc.deallocate(N, 1);
		}
		void					clearTree()
		{
			_size = 0;
			clearFrom(_root);
			_root = NULL;
		}

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