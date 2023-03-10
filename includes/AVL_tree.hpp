#pragma		once

#include	"node.hpp"
#include	"pair.hpp"
#include	<memory>

namespace	ft
{
	template	<class Key, class Value, class Compare = std::less<Key> >
	class		AVL_tree
	{
	public :
		typedef Compare									key_compare;
		typedef pair<const Key, Value>					pair_type;
		typedef typename ft::node<const Key, Value>		node_type;
		typedef typename ft::node<const Key, Value>*	node_ptr;
		typedef typename std::allocator<node_type>		allocator_type;

		key_compare										keyComp;
		node_ptr 										root;
		size_t											size;
		allocator_type									alloc;

	public:
//Member functions ----------------------------------------------------------//
	//Constructor/Destructor ------------------------------------------------//
		//Default -----------------------------------------------------------//
		AVL_tree(const key_compare& comp = key_compare(),
		const allocator_type& allocator = std::allocator<node_type>())
		: keyComp(comp), root(NULL), size(0), alloc(allocator) {}

		//Default -----------------------------------------------------------//
		AVL_tree(Key key, Value value, 
		const key_compare& comp = key_compare(),
		const allocator_type& allocator = std::allocator<node_type>())
		: keyComp(comp), root(NULL), size(0), alloc(allocator)
		{
			insertNode(key, value);
		}

		//Destructor --------------------------------------------------------//
		~AVL_tree() {}

	//Getters ---------------------------------------------------------------//
		node_ptr		minValue(node_ptr node) const
		{
			node_ptr current = node;
			while (current->getLeftChild())
				current = current->getLeftChild();
			return (current);
		}
		node_ptr		maxValue(node_ptr node) const
		{
			node_ptr current = node;
			while (current->getRightChild())
				current = current->getRightChild();
			return (current);
		}
		int				balanceFactor(node_ptr node)
		{
			if (node == NULL)
				return (0);
			return (height(node->getLeftChild()) - height(node->right));
		}
		int				height(node_ptr node)
		{
			if (node == NULL)
				return 0;
			return (node->getHeight());
		}

	//New node --------------------------------------------------------------//
		node_ptr		newNode(Key key, Value value)
		{
			node_ptr node = alloc.allocate(1);
			alloc.construct(node, make_pair(key, value)); 
			node->setFirst(key);
			node->setLeftChild(NULL);
			node->setRightChild(NULL);
			node->setHeight(1);
			return (node);
		}

	//Rotations -------------------------------------------------------------//
		int				max(int lhs, int rhs)
		{
			return ((lhs > rhs) ? lhs : rhs);
		}
		node_ptr		rightRotate(node_ptr y)
		{
			node_ptr x = y->getLeftChild();
			node_ptr T2 = x->getRightChild();
			x->setRightChild(y);
			y->setLeftChild(T2);
			y->setHeight(max(height(y->left), height(y->right)) + 1);
			x->setHeight(max(height(x->left), height(x->right)) + 1);
			return (x);
		}
		node_ptr		leftRotate(node_ptr x)
		{
			node_ptr y = x->right;
			node_ptr T2 = y->left;
			y->left = x;
			x->right = T2;
			x->setHeight(max(height(x->left), height(x->right)) + 1);
			y->setHeight(max(height(y->left), height(y->right)) + 1);
			return (y);
		}

	//Insertion -------------------------------------------------------------//
		void			insertPair(pair_type pair)
		{
			root = insertNode(root, pair.first, pair.second);
			if (root)
				root->setParent(NULL);
		}
		node_ptr		insertNode(pair_type const& pair)
		{
			return (insertNode(root, pair.first, pair.second));
		}
		node_ptr		insertNode(node_ptr node, Key key, Value value)
		{
			if (node == NULL)
				return (newNode(key, value));
			if (key < node->getFirst())
				node->setLeftChild(insertNode(node->getLeftChild(), key, value));
			else if (key > node->getFirst())
				node->setRightChild(insertNode(node->getRightChild(), key, value));
			else
				return (node);

			node->height = 1 + max(height(node->getLeftChild()),
						height(node->getRightChild()));
			int balance = balanceFactor(node);
			if (balance > 1)
			{
				if (key < node->getLeftChild()->getFirst())
				{
					return (rightRotate(node));
				}
				else if (key > node->getLeftChild()->getFirst())
				{
					node->setLeftChild(leftRotate(node->getLeftChild()));
					return (rightRotate(node));
				}
			}
			if (balance < -1)
			{
				if (key > node->getRightChild()->getFirst())
				{
					return (leftRotate(node));
				}
				else if (key < node->getRightChild()->getFirst())
				{
					node->setRightChild(rightRotate(node->getRightChild()));
					return (leftRotate(node));
				}
			}
			return (node);
		}

	//Deletion --------------------------------------------------------------//
		void			deleteFrom(node_type node)
		{
			size = 0;
			if(node)
			{
				deleteFrom(node.getRightChild());
				deleteFrom(node.getLeftChild());
				alloc.destroy(node);
				alloc.deallocate(node, 1);
			}
		}
		node_ptr		deleteNode(node_ptr root, Key key)
		{
			if (root == NULL)
				return (root);
			if (key < root->getFirst())
				root->setLeftChild(deleteNode(root->getLeftChild(), key));
			else if (key > root->getFirst())
				root->seRightChild(deleteNode(root->geRightChild(), key));
			else
			{
				if ((root->getLeftChild() == NULL) || (root->geRightChild() == NULL))
				{
					node_ptr temp = root->getLeftChild() ? root->getLeftChild() : root->geRightChild();
					if (temp == NULL)
					{
						temp = root;
						root = NULL;
					} 
					else
						*root = *temp;
					alloc.destroy(temp);
					alloc.deallocate(temp, 1);
				}
				else
				{
					node_ptr temp = minValue(root->geRightChild());
					root->getFirst(temp->getFirst());
					root->geRightChild(deleteNode(root->geRightChild(), temp->getFirst()));
				}
			}

			if (root == NULL)
				return (root);

			root->setHeight(1 + max(height(root->getLeftChild()), height(root->geRightChild())));
			int balanceFactor = getBalanceFactor(root);
			if (balanceFactor > 1)
			{
				if (getBalanceFactor(root->getLeftChild()) >= 0)
				{
					return rightRotate(root);
				}
				else
				{
					root->setLeftChild(leftRotate(root->getLeftChild()));
					return rightRotate(root);
				}
			}
			if (balanceFactor < -1)
			{
				if (getBalanceFactor(root->geRightChild()) <= 0)
				{
					return leftRotate(root);
				}
				else
				{
					root->seRightChild(rightRotate(root->geRightChild()));
					return leftRotate(root);
				}
			}
			return (root);

		}
		node_ptr		search(const Key key) const
		{
			return (search(root, key));
		}
		node_ptr		search(node_ptr node, const Key key) const
		{
			if (node)
			{
				if (key == node->key.first)
					return (node);
				else if (key_compare(key, node->key.first))
					return (search(node->getLeftChild(), key));
				else
					return (search(node->getRightChild(), key));
			}
			return (NULL);
		}

	};

}