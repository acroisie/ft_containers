#include	"../includes/vector.hpp"
#include	<vector>

template <class T>
void	printVector(const ft::vector<T>& vector)
{
	for (size_t i = 0; i < vector.size(); i++)
		std::cout << vector[i] << std::endl;
}

int	main(void)
{
	ft::vector<std::string> strVector;

	strVector.push_back("1rst");
	strVector.push_back("2nd");
	strVector.push_back("3rd");
	strVector.push_back("4rth");
	printVector(strVector);

	return (0);
}