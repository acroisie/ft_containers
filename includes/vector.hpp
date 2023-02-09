#pragma		once

#include	<memory>
#include	"random_access_iterator.hpp"

namespace	ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
	public:
		typedef T												value_type;
		typedef Allocator										allocator_type;
		typedef typename allocator_type::reference				reference;
		typedef typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer			const_pointer;
		typedef typename ft::random_access_iterator<value_type>	iterator;
		// typedef typename ft::const_iterator						const_iterator;
		// typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
		// typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef typename allocator_type::difference_type		difference_type;
		typedef typename allocator_type::size_type				size_type;

	private:
		value_type*		_data;
		size_type		_size;
		size_type		_capacity;
		allocator_type	_alloc;

//Member functions -----------------------------------------------------------//
		void	realloc(size_type newCapacity) //Or Reserve ??
		{
			T* newData = _alloc.allocate(newCapacity);
			// _alloc.construct(newData, );
	 		if (newCapacity < _size)
				_size = newCapacity;
			for (size_type i = 0; i < _size; i++)
				newData[i] = _data[i];
			_alloc.deallocate(_data, _capacity);
			_data = newData;
			_capacity = newCapacity;
		}

	public:
	//Constructor/Destructor -------------------------------------------------//
		//Default ------------------------------------------------------------//
		explicit	vector(const allocator_type& alloc = allocator_type())
		: _data(NULL), _size(0), _capacity(0), _alloc(alloc) {}

		//Fill ---------------------------------------------------------------//
		// explicit	vector(size_type n, const value_type& val = value_type(), 
		// const allocator_type& alloc = allocator_type())
		// : _data(NULL), _size(0), _capacity(0), _alloc(alloc)
		// {
		// 	assign(n, val);
		// }

		//Range --------------------------------------------------------------//
		// template <class InputIterator>	vector(InputIterator first, InputIterator last,
		// const allocator_type& alloc = allocator_type())
		// : _data(NULL), _size(0), _capacity(0), _alloc(alloc)
		// {
		// 	assign(first, last);
		// }

		//Copy ---------------------------------------------------------------//
		vector(const vector& x) {return (*this = x);}

		~vector(){}
		
		vector&	operator=(const vector& x) // To modify with deep copy i think
		{
			_data = x._data;
			_size = x._size;
			_capacity = x._capacity;
			_alloc = x._alloc;
			return (*this);
		}

	//Iterators --------------------------------------------------------------//
		iterator				begin() {return (iterator(_data));}
		// const_iterator			begin() const {return const_iterator((_data));}
		iterator				end() {return (iterator(_data + (_size - 1)));}
		// const_iterator			end() const {return const_iterator((_data + _size));}
		// reverse_iterator		rbegin() {return (this->end);}
		// const_reverse_iterator	rbegin() const {return (this->end);}
		// reverse_iterator 		rend() {return (reverse_iterator(_data));}
		// const_reverse_iterator	rend() const {return const_reverse_iterator((_data));}

	//Capacity ---------------------------------------------------------------//
		size_type				size() const {return(_size);}
		size_type				max_size() const {return(_alloc.max_size());}
		void					resize(size_type n, value_type val = value_type()); //To define
		size_type				capacity() const {return(_capacity);}
		bool					empty() const
		{
			if (_size)
				return (false);
			return (true);
		}
		void 					reserve (size_type n)
		{
			if (n > _size)
				realloc(n);
		}
		void					shrink_to_fit()
		{
			if (_capacity > _size)
				realloc(_size);
		}

	//Element access ---------------------------------------------------------//
		reference				operator[](size_type n) {return(_data[n]);}
		const_reference			operator[](size_type n) const {return(_data[n]);}
		reference				at(size_type n)
		{
			if (n >= _size)
				throw std::out_of_range("vector");
			return(_data[n]);
		}
		const_reference			at(size_type n) const 
		{
			if (n >= _size)
				throw std::out_of_range("vector");
			return(_data[n]);
		}
		reference 				back() {return(_data[_size - 1]);}
		const_reference			back() const {return(_data[_size - 1]);}
		reference 				front() {return(_data[0]);}
		const_reference			front() const {return(_data[0]);}
		value_type* 			data() {return(&_data[0]);}
		const value_type*		data() const {return(&_data[0]);}

	//Modifiers --------------------------------------------------------------//
		void					push_back(const_reference value)
		{
			if (_size == _capacity)
				vector::realloc(_capacity * 2);
			_data[_size++] = value;
		}

	//Allocator --------------------------------------------------------------//

	};
}