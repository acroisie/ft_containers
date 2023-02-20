#pragma			once

#include		<memory>
#include		"random_access_iterator.hpp"
#include		"reverse_iterator.hpp"
#include		"enable_if.hpp"
#include		"is_integral.hpp"

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
		: _data(NULL), _size(0), _capacity(0), _alloc(other._alloc)
		{
			*this = other;
		}

		//Destructor ---------------------------------------------------------//
		~vector(){}

		//Assign operator ----------------------------------------------------//
		vector&	operator=(const vector& x)
		{
			if (x.capacity() > 0)
			{
				reserve(x.capacity());
				assign(x.begin(), x.end());
			}
			return (*this);
		}

	//Iterators --------------------------------------------------------------//
		iterator				begin() {return (iterator(_data));}
		const_iterator			begin() const {return const_iterator((_data));}
		iterator				end() {return iterator(_data + _size);}
		const_iterator			end() const {return const_iterator(_data + _size);}
		reverse_iterator		rbegin() {return reverse_iterator(_data + _size - 1);}
		const_reverse_iterator	rbegin() const {return const_reverse_iterator(_data + _size - 1);}
		reverse_iterator		rend() {return reverse_iterator(_data - 1);}
		const_reverse_iterator	rend() const {return const_reverse_iterator(_data - 1);}

	//Capacity ---------------------------------------------------------------//
		size_type				size() const {return(_size);}
		size_type				max_size() const {return(_alloc.max_size());}
		void					resize(size_type n)
		{
			if (n > _capacity)
				reserve(n);
			if (n > size())
				for (size_t i = size(); i < n; ++i)
					push_back(T());
			else
				for (size_t i = size(); i > n; --i)
					pop_back();
		}
		size_type				capacity() const {return(_capacity);}
		bool					empty() const
		{
			if (_size)
				return (false);
			return (true);
		}
		void 					reserve(size_type n)
		{
			if (n <= _capacity)
				return;
			pointer newData = _alloc.allocate(n);
			for (size_type i = 0; i < _size; i++)
			{
				_alloc.construct(newData + i, _data[i]);
				_alloc.destroy(_data + i);
			}
			if (_data)
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
		void					assign(typename ft::enable_if
		<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
		 InputIterator last)
		{
			clear();
			for (; first != last; ++first)
				push_back(*first);
		}
		void					assign(size_type n, const_reference val)
		{
			if (n <= 0)
				return;
			if (n > _capacity)
				reserve(n);
			clear();
			for (size_type i = 0; i < n; i++)
				_alloc.construct(_data + _size++, val);
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
		iterator				insert(iterator position, const_reference val)
		{
			size_t pos = 0;
			for (iterator it = begin(); it != end(); ++it)
			{
				if (it == position)
				{
					insert(position, 1, val);
					return position;
				}
				pos++;
			}
			if (pos == _size)
				push_back(val);
			return (end());
		}
		void					insert(iterator position, size_type n, const_reference val)
		{
			iterator it = begin();
			size_t pos = 0;
			for (; it != end(); ++it)
			{
				if (it == position)
				{
					for (size_t i = 0; i < n; ++i)
						insert(position, val);
					return;
				}
				++pos;
			}
			if (pos == size())
			{
				for (size_t i = 0; i < n; ++i)
					push_back(val);
			}
		}
		template <class InputIterator>
		void					insert(iterator position, typename ft::enable_if<
		!ft::is_integral<InputIterator>::value, InputIterator>::type first,
		InputIterator last)
		{
			while (first != last)
			{
				insert(position, *first);
				first++;
			}
		}
		iterator				erase(iterator position)
		{
			for (iterator it = position; it != _data + _size - 1; it++)
			{
				_alloc.destroy(&(*it));
				_alloc.construct(&(*it), *(it + 1));
			}
			_size--;
			return (position);
		}
		iterator				erase(iterator first, iterator last)
		{
			size_type range = last - first;
			for (iterator it = first; it != _data + _size - range; it++)
			{
				_alloc.destroy(&(*it));
				_alloc.construct(&(*it), *(it + (int)range));
			}
			for (iterator it = _data + _size - range; it != _data + _size; it++)
				_alloc.destroy(&(*it));
			_size -= range;
			return (first);
		}
		void					swap(vector& x)
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