#pragma		once

#include	<memory>
#include	<iostream> // to delete
#include	<algorithm>
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

	public: //temporary public
		node_pointer	_meta;
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
		: _root(NULL), _size(0), _comp(comp), _alloc(alloc)
		{
			value_type tmp;
			_meta = _alloc.allocate(1);	
			_alloc.construct(_meta, node<value_type>(tmp));
		}

		//Range --------------------------------------------------------------//
		template<class iterator>
		map(iterator first, iterator last, const Compare& comp = Compare(),
		const Allocator& alloc = Allocator())
		: _root(NULL), _size(0), _comp(comp), _alloc(alloc)
		{
			value_type tmp;
			_meta = _alloc.allocate(1);	
			_alloc.construct(_meta, node<value_type>(tmp));
			insert(first, last);
		}

		//Copy ---------------------------------------------------------------//
		map(const map& other, const Compare& comp = key_compare(),
		const Allocator& alloc = allocator_type())
		: _root(NULL), _size(0), _comp(comp), _alloc(alloc)
		{
			value_type tmp;
			_meta = _alloc.allocate(1);	
			_alloc.construct(_meta, node<value_type>(tmp));	
			*this = other;
		}

		//Destructor ---------------------------------------------------------//
		~map()
		{
			clearTree();
			_alloc.deallocate(_meta, 1);
		}

		//Assign operator ----------------------------------------------------//
		map&	operator=(const map& other) 
		{
			clear();
			insert(other.begin(), other.end());
			return (*this);
		}

		//Allocator ----------------------------------------------------------//
		allocator_type			get_allocator() const {return (_alloc);}

	//Element access ---------------------------------------------------------//
		mapped_type&			at (const key_type& key)
		{ 
			if (search(key))
				return (search(key).m_pair->second);
			throw std::out_of_range("map"); 
		}
		const mapped_type&		at (const key_type& key) const
		{
			if (search(key))
				return (search(key).m_pair->second);
			throw std::out_of_range("map"); 
		}
		mapped_type&			operator[](const key_type& key)
		{
			if (search(key))
				return (search(key)->m_pair.second);
			insertPair(ft::make_pair(key, T()));
			return (search(key)->m_pair.second);
		}

	//Iterators --------------------------------------------------------------//
		iterator				begin()
		{
			if (!_root)
				return (iterator(_meta));
			return (iterator(nodeWithMimumValue(_root)));
		}
		const_iterator			begin() const
		{
			if (!_root)
				return (const_iterator(_meta));
			return (const_iterator(nodeWithMimumValue(_root)));
		}
		iterator				end()
		{
			_meta->m_left = _root;
			if (_root)
				_root->m_up = _meta;
			return (iterator(_meta));
		}
		const_iterator			end() const
		{
			_meta->m_left = _root;
			if (_root)
				_root->m_up = _meta;
			return (const_iterator(_meta));
		}
		reverse_iterator		rbegin()
		{
			return (reverse_iterator(end()));
		}
		const_reverse_iterator	rbegin() const
		{
			return (const_reverse_iterator(end()));
		}
		reverse_iterator		rend()
		{
			return (reverse_iterator(begin()));
		}
		const_reverse_iterator	rend() const
		{
			return (const_reverse_iterator(begin()));
		}

	//Capacity ---------------------------------------------------------------//
		bool					empty() const {return (begin() == end());}
		size_type				size() const {return (_size);}
		size_type				max_size() const {return (_alloc.max_size());}

	//Modifiers --------------------------------------------------------------//
		void					clear() {clearTree();}
		pair<iterator,bool>		insert(const value_type& val)
		{
			iterator tmp(search(val.first));
			insertPair(val);
			iterator it(search(val.first));
			if (it != NULL && tmp == NULL)
				return (ft::make_pair<iterator, bool>(it, true));
			return (ft::make_pair<iterator, bool>(it, false));
		}
		iterator				insert(iterator position, const value_type& val)
		{
			(void) position;
			insert(val);
			return (iterator(search(val.first)));
		}
		template <class iterator> 
		void					insert(iterator first, iterator last)
		{
			for (; first != last; first++)
				insert(*first);
		}
		iterator				erase(iterator pos) 
		{
			deleteNode(pos.getPtr());
			return (pos);
		}
		iterator				erase(iterator first, iterator last) 
		{
			iterator tmp = first;
			while(first != last)
			{
				tmp++;
				deleteNode(first.getPtr());
				first = tmp;
			}
			return (tmp);
		}
		size_type				erase(const Key &key) 
		{
			iterator	it = find(key);
			if (it == end())
				return (0);
			deleteNode(it.getPtr());
			return (1);
		}
		void					swap(map& other)
		{
			node_pointer 	meta = other._meta;
			node_pointer 	root = other._root;
			size_type 		size = other._size;
			key_compare		comp = other._comp;
			allocator_type	alloc = other._alloc;

			other._meta = _meta;
			other._root = _root;
			other._size = _size;
			other._comp = _comp;
			other._alloc = _alloc;

			_meta = meta;
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
			node_pointer tmp = search(key);
			if (tmp)
				return (iterator(tmp));
			return (end());
		}
		const_iterator			find(const Key& key) const
		{
			node_pointer tmp = search(key);
			if (tmp)
				return (const_iterator(tmp));
			return (end());
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
			_size++;
			return (N);
		}
		node_pointer			rightRotate(node_pointer N)
		{
			node_pointer x = N->m_left;
			node_pointer tmp = x->m_right;
			x->m_right = N;
			x->m_up = N->m_up;
			N->m_up = x;
			N->m_left = tmp;
			if (tmp)
				tmp->m_up = N;
			N->m_height = max(height(N->m_left), height(N->m_right)) + 1;
			x->m_height = max(height(x->m_left), height(x->m_right)) + 1;
			return (x);
		}
		node_pointer			leftRotate(node_pointer N)
		{
			node_pointer y = N->m_right;
			node_pointer tmp = y->m_left;
			y->m_left = N;
			N->m_right = tmp;
			y->m_up = N->m_up;
			N->m_up = y;
			if (tmp)
				tmp->m_up = N;
			N->m_height = max(height(N->m_left), height(N->m_right)) + 1;
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
		void					insertPair(const value_type& val)
		{
			_root = insertNode(_root, val.first, val.second);
			if (_root)	
				_root->m_up = _meta;
		}
		node_pointer			nodeWithMimumValue(node_pointer N) const
		{
			if (!N)
				return (NULL);
			node_pointer current = N;
			while (current->m_left != NULL)
				current = current->m_left;
			return (current);
		}
		node_pointer			nodeWithMaximumValue(node_pointer N) const
		{
			if (!N)
				return (NULL);
			node_pointer current = N;
			while (current->m_right != NULL)
				current = current->m_right;
			return (current);
		}
		void					relink(node_pointer N, node_pointer newNode)
		{
			if (N == _root)
				_root = newNode;
			else if (N == N->m_up->m_left)
				N->m_up->m_left = newNode;
			else if (N == N->m_up->m_right)
				N->m_up->m_right = newNode;
			if (newNode)
				newNode->m_up = N->m_up;
		}
		void					deleteNode(node_pointer N)
		{
			if(!N)
				return ;
			if (!N->m_left)
				relink(N, N->m_right);
			else if (!N->m_right)
				relink(N, N->m_left);
			else	
			{
				iterator it = find(N->m_pair.first);
				it++;
				node_pointer newRoot = it.getPtr();
				node_pointer tmp;
				tmp = newRoot;
				if (!tmp)
					return ;
				if (newRoot->m_up != N)
				{
					tmp = newRoot->m_up;
					relink(newRoot, newRoot->m_right);
					newRoot->m_right = N->m_right;
					newRoot->m_right->m_up = newRoot;
				}
				relink(N, newRoot);
				newRoot->m_left = N->m_left;
				newRoot->m_left->m_up = newRoot;
			}
			_alloc.destroy(N);
			_alloc.deallocate(N, 1);
			_size--;
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

	public: //temporary public
		void					printTree(node_pointer node, std::string indent, bool last) const
		{
			if (node != NULL)
			{
				std::cout << indent;
				std::cout << (last ? "├──" : "└──");
				std::cout << "[" << node->m_pair.first << "]" << std::endl;
				printTree(node->m_left, indent + (last ? "│   " : "    "), true);
				printTree(node->m_right, indent + (last ? "│   " : "    "), false);
			}
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