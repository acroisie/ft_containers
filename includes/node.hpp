#pragma		once

#include	"pair.hpp"

namespace	ft
{
    template	<class T1, class T2>
    class		node
    {
    private:
        pair<T1, T2>	_pair;
        node*			_parent;
        node*			_leftChild;
        node*			_rightChild;
        int				_height;

    public:
//Member functions -----------------------------------------------------------//
	//Constructor/Destructor -------------------------------------------------//
		//Default ------------------------------------------------------------//
        node(): _parent(NULL), _leftChild(NULL), _rightChild(NULL), _height(0) {}

		//Pair ---------------------------------------------------------------//
        node(const pair<T1, T2>& data, node* parent = NULL,
		node* leftChild = NULL, node* rightChild = NULL, int height = 0)
        : _pair(data), _parent(parent), _leftChild(leftChild),
		_rightChild(rightChild), _height(height) {}

		//Destructor ---------------------------------------------------------//
        ~node() {}

	//Getters/Setters --------------------------------------------------------//
        const pair<T1, T2>&	getPair() const
		{
            return (_pair);
        }
        void				setPair(const pair<T1, T2>& pair)
		{
            _pair = pair;
        }

        node*				getParent() const
		{
            return (_parent);
        }
        void				setParent(node* parent)
		{
            _parent = parent;
        }

        node*				getLeftChild() const
		{
            return (_leftChild);
        }
        void				setLeftChild(node* leftChild)
		{
            _leftChild = leftChild;
        }

        node*				getRightChild() const
		{
            return (_rightChild);
        }
        void				setRightChild(node* rightChild)
		{
            _rightChild = rightChild;
        }

        int					getHeight() const
		{
            return (_height);
        }
        void				setHeight(int height)
		{
            _height = height;
        }
    };

}