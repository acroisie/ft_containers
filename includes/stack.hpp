#pragma		once

#include	"vector.hpp"

namespace	ft
{
    template	<typename T, typename Container = ft::vector<T> >
    class		stack
	{
    public:
        typedef Container							container_type;
        typedef typename Container::value_type		value_type;
        typedef typename Container::size_type		size_type;
        typedef typename Container::reference		reference;
        typedef typename Container::const_reference	const_reference;

    private:
        container_type _data;

    public:
//Member functions -----------------------------------------------------------//
	//Constructor/Destructor/Assign content ----------------------------------//
		//Default ------------------------------------------------------------//
        explicit stack(const container_type& cont = container_type())
		: _data(cont) {}

		//Destructor ---------------------------------------------------------//
		~stack() {}

		//Assign operator ----------------------------------------------------//
		stack&				operator=(const stack& other)
		{
			_data = other._data;
			return (*this);
		}

	//Element access ---------------------------------------------------------//
        value_type&			top() {return (_data.back());}
        const value_type&	top() const {return (_data.back());}

	//Capacity ---------------------------------------------------------------//
        bool				empty() const {return (_data.empty());}
        size_type			size() const {return (_data.size());}

	//Modifiers --------------------------------------------------------------//
        void				push(const value_type& value) {_data.push_back(value);}
        void				pop() {_data.pop_back();}

    };

//Non-member functions -------------------------------------------------------//
	//Operators --------------------------------------------------------------//
	template< class T, class Container >
	bool operator==(const stack<T, Container>& lhs,
					const stack<T, Container>& rhs)
	{
		return (lhs == rhs);
	}
	template< class T, class Container >
	bool operator!=(const stack<T, Container>& lhs,
					const stack<T, Container>& rhs)
	{
		return (!(lhs == rhs));
	}
	template< class T, class Container >
	bool operator<(const stack<T, Container>& lhs,
					const stack<T, Container>& rhs)
	{
		return (lhs < rhs);
	}
	template< class T, class Container >
	bool operator<=(const stack<T, Container>& lhs,
					const stack<T, Container>& rhs)
	{
		return (lhs <= rhs);
	}
	template< class T, class Container >
	bool operator>(const stack<T, Container>& lhs,
					const stack<T, Container>& rhs)
	{
		return (lhs > rhs);
	}
	template< class T, class Container >
	bool operator>=(const stack<T, Container>& lhs,
					const stack<T, Container>& rhs)
	{
		return (lhs >= rhs);
	}

}
