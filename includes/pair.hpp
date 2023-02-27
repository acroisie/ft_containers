#pragma		once

namespace	ft
{
	template<class T1, class T2>
	class pair
	{
	public:
		typedef	T1	first_type;
		typedef	T2	second_type;

	private:
		first_type	_first;
		second_type	_second;
		
	public:
//Member functions -----------------------------------------------------------//
	//Constructor/Destructor/Assign content ----------------------------------//
		pair(): _first(), _second() {}
		~pair();
	};

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
	template <class T1,class T2>
  	pair<T1,T2> make_pair (T1 x, T2 y)
  	{
    	return (pair<T1,T2>(x, y));
  	}
	
}