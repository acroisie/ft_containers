#pragma		once

namespace	ft
{
	template<class T1, class T2>
	struct pair
	{
//Member types ---------------------------------------------------------------//
		typedef	T1	first_type;
		typedef	T2	second_type;

//Member objects -------------------------------------------------------------//
		first_type	first;
		second_type	second;
		
//Member functions -----------------------------------------------------------//
	//Constructor/Destructor/Assign content ----------------------------------//
		//Default ------------------------------------------------------------//
		pair(): first(), second() {}

		//Initialize ---------------------------------------------------------//
		pair(const T1& x, const T2& y): first(x), second(y) {}
		template< class U1, class U2 >
		pair(const pair<U1, U2>& p): first(p.first), second(p.second) {}

		//Assign operator ----------------------------------------------------//
		pair& operator=(const pair& other)
		{
			first = other.first;
			second = other.second;
			return (*this);
		}

		//Destructor ---------------------------------------------------------//
		~pair() {}
	};

//Non-member functions -------------------------------------------------------//
	template< class T1, class T2 >
	pair<T1, T2> make_pair( T1 t, T2 u )
  	{
    	return (pair<T1,T2>(t, u));
  	}
	
	//Operators --------------------------------------------------------------//
	template <class T1, class T2>
  	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}
	template <class T1, class T2>
  	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (!(lhs == rhs));
	}
	template <class T1, class T2>
	bool operator< (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
	}
	template <class T1, class T2>
  	bool operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (!(rhs < lhs));
	}
	template <class T1, class T2>
  	bool operator> (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (rhs < lhs);
	}
	template <class T1, class T2>
  	bool operator>=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (!(lhs < rhs));
	}
}