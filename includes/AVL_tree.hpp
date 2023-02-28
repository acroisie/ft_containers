#pragma		once

#include	"node.hpp"

namespace	ft
{
	template	<class T1, class T2>
	class		AVL_tree
	{
	private:
		node<T1, T2>*	_root;

	public:
		AVL_tree(/* args */);
		~AVL_tree();

	};

}