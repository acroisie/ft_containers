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
        node*			_lChild;
        node*			_rChild;
        int				_height;

    public:
//Member functions -----------------------------------------------------------//
	//Constructor/Destructor -------------------------------------------------//
		//Default ------------------------------------------------------------//
        node(): _parent(NULL), _lChild(NULL), _rChild(NULL), _height(0) {}

		//Pair ---------------------------------------------------------------//
        node(const pair<T1, T2>& data, node* parent = NULL,
		node* lChild = NULL, node* rChild = NULL, int height = 0)
        : _pair(data), _parent(parent), _lChild(lChild),
		_rChild(rChild), _height(height) {}

		//Destructor ---------------------------------------------------------//
        ~node() {}

	//Getters/Setters --------------------------------------------------------//
        const pair<T1, T2>&	getPair() const {return (_pair);}
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