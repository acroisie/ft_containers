#pragma		once

#include	"node.hpp"
#include	"pair.hpp"
#include	<memory>

namespace	ft
{
	template	<class Key,class Value, class Compare = std::less<Key> >
	class		AVL_tree
	{
	public :
		typedef Compare									key_compare;
		typedef pair<const Key, Value>					pair_type;
		typedef typename ft::node<pair_type>		 	node_type;
		typedef typename ft::node<pair_type>*			node_ptr;
		typedef typename std::allocator<node_type>		allocator_type;

		key_compare										_keyComp;
		node_ptr 										_root;
		size_t											_size;
		allocator_type									_alloc;

	public:
//Member functions -----------------------------------------------------------//
	//Constructor/Destructor -------------------------------------------------//
		//Default ------------------------------------------------------------//
		AVL_tree(const key_compare& comp = key_compare(),
		const allocator_type& alloc = std::allocator<node_type>())
		:_keyComp(comp), _root(NULL), _size(0), _alloc(alloc){}

		//Destructor ---------------------------------------------------------//
		~AVL_tree() {deleteAll();}

	//Getters ----------------------------------------------------------------//
		node_ptr		minValue(node_ptr node) const
		{
			node_ptr current = node;
			while (current.getLeftChild())
				current = current.getLeftChild();
			return (current);
		}
		node_ptr		maxValue(node_ptr node) const
		{
			node_ptr current = node;
			while (current.getRightChild())
				current = current.getRightChild();
			return (current);
		}
		int				balanceFactor(node_ptr node)
		{
			if (node == NULL)
				return (0);
			return (height(node.getLeftChild()) - height(node->right));
		}
		int				height(node_ptr node)
		{
			if (node == NULL)
				return 0;
			return (node.getHeight());
		}

	//New node ---------------------------------------------------------------//
		node_ptr		newNode(Key key, Value value)
		{
			node_ptr node = _alloc.allocate(1);
			_alloc.construct(node, make_pair(key, value)); 
			node.getFirst() = key;
			node.getLeftChild() = NULL;
			node.getRightChild() = NULL;
			node->height = 1;
			return (node);
		}

	//Rotations -------------------------------------------------------------//
		int				max(int lhs, int rhs)
		{
			return ((lhs > rhs) ? lhs : rhs);
		}
		node_ptr		rightRotate(node_ptr y)
		{
			node_ptr x = y->left;
			node_ptr T2 = x->right;
			x->right = y;
			y->left = T2;
			y->height = max(height(y->left), height(y->right)) + 1;
			x->height = max(height(x->left), height(x->right)) + 1;
			return (x);
		}
		node_ptr		leftRotate(node_ptr x)
		{
			node_ptr y = x->right;
			node_ptr T2 = y->left;
			y->left = x;
			x->right = T2;
			x->height = max(height(x->left), height(x->right)) + 1;
			y->height = max(height(y->left), height(y->right)) + 1;
			return (y);
		}

	//Insertion -------------------------------------------------------------//
		node_ptr		insertNode(node_ptr node, Key key, Value value)
		{
			if (node == NULL)
				return (newNode(key, value));
			if (key < node.getFirst())
				node.getLeftChild() = insertNode(node.getLeftChild(), key);
			else if (key > node.getFirst())
				node.getRightChild() = insertNode(node.getRightChild(), key);
			else
				return (node);

			node->height = 1 + max(height(node.getLeftChild()),
						height(node.getRightChild()));
			int balanceFactor = getBalanceFactor(node);
			if (balanceFactor > 1)
			{
				if (key < node.getLeftChild()->key)
				{
					return (rightRotate(node));
				}
				else if (key > node.getLeftChild()->key)
				{
					node.getLeftChild() = leftRotate(node.getLeftChild());
					return (rightRotate(node));
				}
			}
			if (balanceFactor < -1)
			{
				if (key > node.getRightChild()->key)
				{
					return (leftRotate(node));
				}
				else if (key < node.getRightChild()->key)
				{
					node.getRightChild() = rightRotate(node.getRightChild());
					return (leftRotate(node));
				}
			}
			return (node);
		}

	//Deletion --------------------------------------------------------------//
		void			deleteAll(void)
		{
			_size = 0;
			if(_root)
			{
				clearTree(_root->getRightChild());
				clearTree(_root->getLeftChild());
				_alloc.destroy(_root);
				_alloc.deallocate(_root, 1);
			}
		}
		node_ptr		deleteNode(node_ptr root, Key key)
		{
			if (root == NULL)
				return (root);
			if (key < root.getFirst())
				root.getLeftChild() = deleteNode(root.getLeftChild(), key);
			else if (key > root.getFirst())
				root.geRightChild() = deleteNode(root.geRightChild(), key);
			else
			{
				if ((root.getLeftChild() == NULL) || (root.geRightChild() == NULL))
				{
					node_ptr temp = root.getLeftChild() ? root.getLeftChild() : root.geRightChild();
					if (temp == NULL)
					{
						temp = root;
						root = NULL;
					} 
					else
						*root = *temp;
					_alloc.destroy(temp);
					_alloc.deallocate(temp, 1);
				}
				else
				{
					node_ptr temp = nodeWithMimumValue(root.geRightChild());
					root.getFirst() = temp.getFirst();
					root.geRightChild() = deleteNode(root.geRightChild(), temp.getFirst());
				}
			}

			if (root == NULL)
				return (root);

			root->height = 1 + max(height(root.getLeftChild()), height(root.geRightChild()));
			int balanceFactor = getBalanceFactor(root);
			if (balanceFactor > 1)
			{
				if (getBalanceFactor(root.getLeftChild()) >= 0)
				{
					return rightRotate(root);
				}
				else
				{
					root.getLeftChild() = leftRotate(root.getLeftChild());
					return rightRotate(root);
				}
			}
			if (balanceFactor < -1)
			{
				if (getBalanceFactor(root.geRightChild()) <= 0)
				{
					return leftRotate(root);
				}
				else
				{
					root.geRightChild() = rightRotate(root.geRightChild());
					return leftRotate(root);
				}
			}
			return (root);

		}

	};

}