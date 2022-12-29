#pragma		once
#include	"Utils.hpp"

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
	private:
		T*			_data;
		size_t		_size;
		size_t		_capacity;
		Allocator	_alloc;

//Member functions------------------------------------------------------------//
	void	realloc(size_t newCapacity)
		{
			T* newData = alloc.allocate(newCapacity);
			if (newCapacity < _size)
				_size = newCapacity;
			for (size_t i = 0; i < _size; i++)
				newData[i] = _data[i];

			alloc.deallocate(_data, _capacity);
			_data = newData;
			_capacity = newCapacity;
		}
	public:
	//Constructor/Destructor--------------------------------------------------//
		vector(void): _data(NULL), _size(0), _capacity(0){realloc(2);};
		~vector(){};

	//Iterators---------------------------------------------------------------//

	//Capacity----------------------------------------------------------------//
		size_t		size() const{return(_size);}
		size_t		max_size() const{return(_alloc.max_size());}

	//Element access----------------------------------------------------------//
		const T&	operator[](size_t index) const {return(_data[index]);}
		T&			operator[](size_t index) {return(_data[index]);}

	//Modifiers---------------------------------------------------------------//
		void push_back(const T& value)
		{
			if (_size == _capacity)
				vector::realloc(_capacity * 2);
			_data[_size++] = value;
		}

	//Allocator---------------------------------------------------------------//

	};
}