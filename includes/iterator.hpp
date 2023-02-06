#pragma		once

#include	<iterator>
#include	<cstddef>

namespace	ft
{
//Classes --------------------------------------------------------------------//
	//Iterator base class ----------------------------------------------------//
	template	<class Category, class T, class Distance = ptrdiff_t,
	class Pointer = T*, class Reference = T&>
  	struct	iterator
	{
		typedef	T											value_type;
		typedef	Distance									difference_type;
		typedef	Pointer										pointer;
		typedef	Reference									reference;
		typedef	Category									iterator_category;
	};

	//Iterator traits --------------------------------------------------------//
	template	<class Iterator>
	struct	iterator_traits
	{
		typedef	typename	Iterator::difference_type		difference_type;
		typedef	typename	Iterator::value_type			value_type;
		typedef	typename	Iterator::pointer				pointer;
		typedef	typename	Iterator::reference				reference;
		typedef	typename	Iterator::iterator_category		iterator_category;
	};

	template	<class T>
	struct	iterator_traits<T*>
	{
		typedef	std::ptrdiff_t								difference_type;
		typedef	T											value_type;
		typedef	T*											pointer;
		typedef	T&											reference;
		typedef	std::random_access_iterator_tag				iterator_category;
	};

	template	<class T>
	struct	iterator_traits<const T*>
	{
		typedef	std::ptrdiff_t								difference_type;
		typedef	T											value_type;
		typedef	const T*									pointer;
		typedef	const T&									reference;
		typedef	std::random_access_iterator_tag				iterator_category;
	};

	//Iterator tag -----------------------------------------------------------//
	typedef	std::input_iterator_tag					input_iterator_tag;
	typedef	std::output_iterator_tag				output_iterator_tag;
	typedef	std::forward_iterator_tag				forward_iterator_tag;
	typedef	std::bidirectional_iterator_tag			bidirectional_iterator_tag;
	typedef	std::random_access_iterator_tag			random_access_iterator_tag;
}