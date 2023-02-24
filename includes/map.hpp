#pragma		once

#include	<memory>
#include	<map>

namespace	ft
{
	template<class Key, class T, class Compare = std::less<Key>,
	class Allocator = std::allocator<std::pair<const Key, T>> >
	class map
	{
	public:
		typedef Key                                      key_type;
		typedef T                                        mapped_type;
		typedef pair<const key_type, mapped_type>        value_type;
		typedef Compare                                  key_compare;
		typedef Allocator                                allocator_type;
		typedef typename allocator_type::reference       reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer         pointer;
		typedef typename allocator_type::const_pointer   const_pointer;
		typedef typename allocator_type::size_type       size_type;
		typedef typename allocator_type::difference_type difference_type;

		// typedef implementation-defined                   iterator;
		// typedef implementation-defined                   const_iterator;
		// typedef std::reverse_iterator<iterator>          reverse_iterator;
		// typedef std::reverse_iterator<const_iterator>    const_reverse_iterator;

	private:
		/* data */
	public:
//Member functions -----------------------------------------------------------//
	//Constructor/Destructor/Assign operator ---------------------------------//
		map() {}

		explicit map(const Compare& comp,
					const Allocator& alloc = Allocator()) {}

		template< class InputIt >
		map(InputIt first, InputIt last,
			const Compare& comp = Compare(),
			const Allocator& alloc = Allocator());

		map(const map& other);

		~map();

		map& operator=(const map& other)
		{
			return *this;
		}
	};
	
}