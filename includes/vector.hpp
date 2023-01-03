#pragma		once
#include	"Utils.hpp"

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
	public:
		typedef T                                        value_type;
		typedef Allocator                                allocator_type;
		typedef typename allocator_type::reference       reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer         pointer;
		typedef typename allocator_type::const_pointer   const_pointer;
		// typedef std::reverse_iterator<iterator>          reverse_iterator;
		// typedef implementation-defined                   iterator;
		// typedef implementation-defined                   const_iterator;
		// typedef std::reverse_iterator<const_iterator>    const_reverse_iterator;
		// typedef typename allocator_type::difference_type difference_type;
		typedef typename allocator_type::size_type       size_type;

	private:
		value_type*		_data;
		size_type		_size;
		size_type		_capacity;
		allocator_type	_alloc;

	public:
//Member functions------------------------------------------------------------//
	//Constructor/Destructor--------------------------------------------------//
		vector(void): _data(NULL), _size(0), _capacity(0){resize(2);};
		~vector(){};

	//Iterators---------------------------------------------------------------//

	//Capacity----------------------------------------------------------------//
		size_type			size() const {return(_size);}
		size_type			max_size() const {return(_alloc.max_size());}
		void				resize (size_type n, value_type val = value_type())
		{
			(void)val; //For the moment
			T* newData = _alloc.allocate(n);
			if (n < _size)
				_size = n;
			for (size_type i = 0; i < _size; i++)
				newData[i] = _data[i];

			_alloc.deallocate(_data, _capacity);
			_data = newData;
			_capacity = n;
		}

	//Element access----------------------------------------------------------//
		const value_type&	operator[](size_type index) const {return(_data[index]);}
		value_type&			operator[](size_type index) {return(_data[index]);}

	//Modifiers---------------------------------------------------------------//
		void				push_back(const value_type& value)
		{
			if (_size == _capacity)
				vector::resize(_capacity * 2);
			_data[_size++] = value;
		}

	//Allocator---------------------------------------------------------------//

	};
}