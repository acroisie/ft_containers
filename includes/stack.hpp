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

    protected:
        container_type c;

    public:
//Member functions -----------------------------------------------------------//
	//Constructor/Destructor/Assign content ----------------------------------//
		//Default ------------------------------------------------------------//
        explicit stack(const container_type& cont = container_type())
		: c(cont) {}

		//Destructor ---------------------------------------------------------//
		~stack() {}

		//Assign operator ----------------------------------------------------//
		stack&				operator=(const stack& other)
		{
			c = other.c;
			return (*this);
		}

	//Element access ---------------------------------------------------------//
        value_type&			top() {return (c.back());}
        const value_type&	top() const {return (c.back());}

	//Capacity ---------------------------------------------------------------//
        bool				empty() const {return (c.empty());}
        size_type			size() const {return (c.size());}

	//Modifiers --------------------------------------------------------------//
        void				push(const value_type& value) {c.push_back(value);}
        void				pop() {c.pop_back();}

	//Operators --------------------------------------------------------------//
		friend bool			operator==(const stack<value_type, container_type>& lhs,
						const stack<value_type, container_type>& rhs)
		{
			return (lhs.c == rhs.c);
		}
		friend bool			operator!=(const stack<value_type, container_type>& lhs,
						const stack<value_type, container_type>& rhs)
		{
			return (!(lhs.c == rhs.c));
		}
		friend bool			operator<(const stack<value_type, container_type>& lhs,
						const stack<value_type, container_type>& rhs)
		{
			return (lhs.c < rhs.c);
		}
		friend bool			operator<=(const stack<value_type, container_type>& lhs,
						const stack<value_type, container_type>& rhs)
		{
			return (lhs.c <= rhs.c);
		}
		friend bool			operator>(const stack<value_type, container_type>& lhs,
						const stack<value_type, container_type>& rhs)
		{
			return (lhs.c > rhs.c);
		}
		friend bool			operator>=(const stack<value_type, container_type>& lhs,
						const stack<value_type, container_type>& rhs)
		{
			return (lhs.c >= rhs.c);
		}
    };

}
