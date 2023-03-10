#pragma		once

#include	"pair.hpp"

namespace	ft
{
    template	<class T>
    class		node
    {
    public:
        typedef T                                   pair_type;
        typedef typename pair_type::first_type      first;
        typedef typename pair_type::second_type     second;

        pair_type       m_pair;
        node*			m_up;
        node*			m_left;
        node*			m_right;
        size_t			m_height;

    public:
//Member functions -----------------------------------------------------------//
	//Constructor/Destructor -------------------------------------------------//
		//Pair ---------------------------------------------------------------//
        node(const pair_type &content)
        : m_pair(content), m_up(NULL), m_left(NULL), m_right(NULL), m_height(1) {}
        node(const pair_type &content, const node *parent)
        : m_pair(content), m_up(parent), m_left(NULL), m_right(NULL), m_height(1) {}

		//Destructor ---------------------------------------------------------//
        ~node() {}

    };

}