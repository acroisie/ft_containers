#pragma			once

#include		<memory>
#include		"random_access_iterator.hpp"
#include		"reverse_iterator.hpp"

namespace		ft
{
	template	<class T, class Allocator = std::allocator<T> >
	class		vector
	{
	public:
		typedef T														value_type;
		typedef Allocator												allocator_type;
		typedef typename allocator_type::reference						reference;
		typedef typename allocator_type::const_reference				const_reference;
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer					const_pointer;
		typedef typename ft::random_access_iterator<value_type>			iterator;
		typedef typename ft::random_access_iterator<const value_type>	const_iterator;
		typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef typename allocator_type::difference_type				difference_type;
		typedef typename allocator_type::size_type						size_type;

	private:
		value_type*		_data;
		size_type		_size;
		size_type		_capacity;
		allocator_type	_alloc;

	public:
//Member functions -----------------------------------------------------------//
	//Constructor/Destructor/Assign content ----------------------------------//
		//Default ------------------------------------------------------------//
		explicit	vector(const allocator_type& alloc = allocator_type())
		: _data(NULL), _size(0), _capacity(0), _alloc(alloc) {}

		//Fill  --------------------------------------------------------------//
		explicit	vector(size_type count,  const T& value = T(),
        const Allocator& alloc = Allocator())
		: _data(NULL), _size(0), _capacity(0), _alloc(alloc)
		{
			assign(count, value);
		}

		//Range --------------------------------------------------------------//
		template<class InputIt>	vector(InputIt first, InputIt last, 
        const Allocator& alloc = Allocator())
		: _data(NULL), _size(0), _capacity(0), _alloc(alloc)
		{
			assign(first, last);
		}

		//Copy ---------------------------------------------------------------//
		vector(const vector& other)
		: _data(NULL), _size(other._size), _capacity(other._capacity), _alloc(other._alloc)
		{
			*this = other;
		}

		//Destructor ---------------------------------------------------------//
		~vector(){}

		//Assign operator ----------------------------------------------------//
		vector&	operator=(const vector& x)
		{
			if (x._capacity > 0)
			{
				reserve(x._capacity);
				assign(x.begin(), x.end());
			}
			return (*this);
		}

	//Iterators --------------------------------------------------------------//
		iterator				begin() {return (iterator(_data));}
		const_iterator			begin() const {return const_iterator((_data));}
		iterator				end() {return (iterator((_data + _size) - 1));}
		const_iterator			end() const {return const_iterator((_data + _size));}
		reverse_iterator		rbegin() {return ((_data + _size));}
		const_reverse_iterator	rbegin() const {return ((_data + _size));}
		reverse_iterator 		rend() {return (reverse_iterator(_data));}
		const_reverse_iterator	rend() const {return const_reverse_iterator((_data));}

	//Capacity ---------------------------------------------------------------//
		size_type				size() const {return(_size);}
		size_type				max_size() const {return(_alloc.max_size());}
		// void					resize(size_type n, value_type val = value_type()); //To define
		size_type				capacity() const {return(_capacity);}
		bool					empty() const
		{
			if (_size)
				return (false);
			return (true);
		}
		void 					reserve (size_type n)
		{
			// if (n <= _capacity)
			// 	return;
			value_type* newData = _alloc.allocate(n);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct((newData + i), _data[i]);
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(_data + i);
			_alloc.deallocate(_data, _capacity);
			_data = newData;
			_capacity = n;
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
		template <class InputIterator>
		void					assign(InputIterator first, InputIterator last)
		{
			clear();
			for (; first != last; ++first)
				push_back(*first);
		}
		void					assign(size_type n, const value_type& val)
		{
			if (n <= 0)
				return;
			if (n > _capacity)
				reserve(n);
			clear();
			for (size_type i = 0; i < n; i++)
				_alloc.construct(_size++, val);
		}
		void					push_back(const_reference value)
		{
			if (_size == _capacity)
			{
				if (_capacity == 0)
					_capacity = 1;
				reserve(_capacity * 2);
			}
			_alloc.construct((_data + _size++), value);
		}
		void					pop_back()
		{
			if (_size != 0)
				_alloc.destroy((_data + _size--) - 1);
		}
		// iterator				insert (iterator position, const value_type& val);
		// void					insert (iterator position, size_type n, const value_type& val);
		// template <class InputIterator>
		// void					insert (iterator position, InputIterator first, InputIterator last);
		iterator				erase (iterator position)
		{
			for (; position != (_data + _size); position++)
			{
				_alloc.destroy(position);
				_size--;
			}
		}
		iterator				erase (iterator first, iterator last)
		{
			for (; first != last; first++)
			{
				_alloc.destroy(first);
				_size--;
			}
		}
		void					swap (vector& x)
		{
			vector	tmp(*this);
			*this = x;
			x = tmp;
		}
		void					clear()
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(_data + i);
			_size = 0;
		}

	//Allocator --------------------------------------------------------------//
		allocator_type			get_allocator() const {return(_alloc);};
	};
}