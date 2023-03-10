#pragma		once

#include	"pair.hpp"

namespace	ft
{
    template	<class T1, class T2>
    class		node
    {
    public:
        typedef pair<T1, T2>                     pair_type;
        typedef typename pair_type::first_type   first;
        typedef typename pair_type::second_type  second;

        pair_type       _pair;
        node*			_parent;
        node*			_lChild;
        node*			_rChild;
        int				_height;

    public:
//Member functions -----------------------------------------------------------//
	//Constructor/Destructor -------------------------------------------------//
		//Default ------------------------------------------------------------//
        node(): _parent(NULL), _lChild(NULL), _rChild(NULL), _height(0) {}

		//Pair ---------------------------------------------------------------//
        node(pair_type data, node* parent = NULL,
		node* lChild = NULL, node* rChild = NULL, int height = 0)
        : _pair(data), _parent(parent), _lChild(lChild),
		_rChild(rChild), _height(height) {}

		//Destructor ---------------------------------------------------------//
        ~node() {}

	//Increment/decrement operators ------------------------------------------//
        node&               operator++()
        {
            if (_rChild)
            {
                node* current = _rChild;
                while (current->_lChild)
                    current = current->_lChild;
                return (*current);
            }
            node* current = this;
            node* parent = _parent;
            while (parent != NULL && current == parent->_rChild)
            {
                current = parent;
                parent = parent->_parent;
            }
            return (*parent);
        }
        node&               operator--()
        {
            if (_lChild)
            {
                node* current = _lChild;
                while (current->_rChild)
                    current = current->_rChild;
                return (*current);
            }
            node* current = this;
            node* parent = _parent;
            while (parent != NULL && current == parent->_lChild)
            {
                current = parent;
                parent = parent->_parent;
            }
            return (*parent);
        }

	//Getters/Setters --------------------------------------------------------//
        const pair<T1, T2>&	getPair() const {return (_pair);}
        const first     	getFirst() const {return (_pair.first);}
        const second    	getSecond() const {return (_pair.second);}
        void				setPair(const pair<T1, T2>& pair) {_pair = pair;}

        node*				getParent() const {return (_parent);}
        void				setParent(node* parent) {_parent = parent;}

        node*				getLeftChild() const {return (_lChild);}
        void				setLeftChild(node* lChild) {_lChild = lChild;}

        node*				getRightChild() const {return (_rChild);}
        void				setRightChild(node* rChild) {_rChild = rChild;}

        int					getHeight() const {return (_height);}
        void				setHeight(int height) {_height = height;}

    };

}