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

        pair_type       m_pair;
        node*			m_parent;
        node*			m_lChild;
        node*			m_rChild;

    public:
//Member functions -----------------------------------------------------------//
	//Constructor/Destructor -------------------------------------------------//
		//Pair ---------------------------------------------------------------//
        node(pair_type data = NULL, node* parent = NULL,
		node* lChild = NULL, node* rChild = NULL)
        : m_pair(data), m_parent(parent), m_lChild(lChild),
		m_rChild(rChild) {}

		//Destructor ---------------------------------------------------------//
        ~node(){}

	//Increment/decrement operators ------------------------------------------//
        node&               operator++()
        {
            if (m_rChild)
            {
                node* current = m_rChild;
                while (current->m_lChild)
                    current = current->m_lChild;
                return (*current);
            }
            node* current = this;
            node* parent = m_parent;
            while (parent != NULL && current == parent->m_rChild)
            {
                current = parent;
                parent = parent->m_parent;
            }
            return (*parent);
        }
        node&               operator--()
        {
            if (m_lChild)
            {
                node* current = m_lChild;
                while (current->m_rChild)
                    current = current->m_rChild;
                return (*current);
            }
            node* current = this;
            node* parent = m_parent;
            while (parent != NULL && current == parent->m_lChild)
            {
                current = parent;
                parent = parent->m_parent;
            }
            return (*parent);
        }

    };

}