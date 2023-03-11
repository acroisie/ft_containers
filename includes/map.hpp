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
		typedef	node<const key_type, mapped_type>*										node_pointer;
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
//Public member class --------------------------------------------------------//
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

//Public member functions ----------------------------------------------------//
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
		pair<const_iterator,
		const_iterator>			equal_range(const Key& key) const {}
		iterator				lower_bound(const Key& key) {}
		const_iterator			lower_bound(const Key& key) const {}
		iterator				upper_bound(const Key& key) {}
		const_iterator			upper_bound(const Key& key) const {}
	//Observers --------------------------------------------------------------//
		key_compare				key_comp() const {return (_comp);}
		// map::value_compare		value_comp() const {}
	
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
		node_pointer			newNode(key_type key, value_type value)
		{
			node_pointer N = _alloc.allocate(1);
			_alloc.construct(N, node_type(key, value));
			return (N);
		}
		node_pointer			rightRotate(node_pointer y)
		{
			node_pointer x = y->m_left;
			node_pointer T2 = x->m_right;
			x->m_right = y;
			y->m_left = T2;
			y->m_height = max(m_height(y->m_left), m_height(y->m_right)) + 1;
			x->m_height = max(m_height(x->m_left), m_height(x->m_right)) + 1;
			return (x);
		}
		node_pointer			leftRotate(node_pointer x)
		{
			node_pointer y = x->m_right;
			node_pointer T2 = y->m_left;
			y->m_left = x;
			x->m_right = T2;
			x->m_height = max(m_height(x->m_left), m_height(x->m_right)) + 1;
			y->m_height = max(m_height(y->m_left), m_height(y->m_right)) + 1;
			return (y);
		}
		int						getBalanceFactor(node_pointer N)
		{
			if (N == NULL)
				return (0);
			return (m_height(N->m_left) - m_height(N->m_right));
		}
		node_pointer			insertNode(node_pointer N, key_type key, value_type value)
		{
			//Find the correct postion and insert the node
			if (N == NULL)
				return (newNode(key, value));
			if (_comp(key, N->m_pair.first))
			{
				N->m_left = insertNode(N->m_left, key);
				if (N->m_left)
					N->m_left->m_up = N;
			}
			else if (_comp(N->m_pair.first, key))
			{
				N->m_right = insertNode(N->m_right, key);
				if (N->m_right)
					N->m_right->m_up = N;
			}
			else
				return (N);

			//Update the balance factor of each node and balance the tree
			N->m_height = 1 + max(m_height(N->m_left), m_height(N->m_right));
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
					return leftRotate(N);
				}
				else if (_comp(key, N->m_right->m_pair.first))
				{
					N->m_right = rightRotate(N->m_right);
					if (N->m_right)
						N->m_right->m_up = NULL;
					return leftRotate(N);
				}
			}
			return (N);
		}
		node_pointer			nodeWithMimumValue(node_pointer N)
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
		node_pointer 			deleteNode(node_pointer root, key_type key)
		{
			// Find the node and delete it
			if (root == NULL)
				return (root);
			if (_comp(key, root->m_pair.first))
			{
				root->m_left = deleteNode(root->m_left, key);
				if (root->m_left)
					root->m_left->up = root;
			}
			else if (_comp(root->m_pair.first, key))
			{
				root->m_right = deleteNode(root->m_right, key);
				if (root->m_right)
					root->m_right->up = root;
			}
			else
			{
				if ((root->m_left == NULL) || (root->m_right == NULL))
				{
					node_pointer temp = root->m_left ? root->m_left : root->m_right;
					if (temp == NULL)
					{
						temp = root;
						root = NULL;
					}
				}
				else
					*root = *temp;
				_alloc.destroy(temp);
				_alloc.deallocate(temp, 1);
			}
			else
			{
				node_pointer temp = nodeWithMimumValue(root->m_right);
				root->m_pair = temp->m_pair;
				root->m_right = deleteNode(root->m_right, temp->key);
			}
			if (root == NULL)
				return (root);

			// Update the balance factor of each node and
			// balance the tree
			root->m_height = 1 + max(m_height(root->m_left), m_height(root->m_right));
			int balanceFactor = getBalanceFactor(root);
			if (balanceFactor > 1)
			{
				if (getBalanceFactor(root->m_left) >= 0)
				{
					return rightRotate(root);
				}
				else
				{
					root->m_left = leftRotate(root->m_left);
					return rightRotate(root);
				}
			}
			if (balanceFactor < -1)
			{
				if (getBalanceFactor(root->m_right) <= 0)
				{
					return leftRotate(root);
				}
				else
				{
					root->m_right = rightRotate(root->m_right);
					return leftRotate(root);
				}
			}
			return (root);

		}
		node_ptr				search(const key_type key) const
		{
			return (search(_root, key));
		}
		node_ptr				search(node_ptr N, const key_type key) const
		{
			if (N)
			{
				if (key == N->key.first)
					return (N);
				else if (_comp(key, N->key.first))
					return (search(N->left, key));
				else
					return (search(N->right, key));
			}
			return (NULL);
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