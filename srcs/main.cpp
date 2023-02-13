#include	"../includes/vector.hpp"
#include	<iostream>
#include	<vector>
#include	<iterator>

template <class T>
void	printVector(const ft::vector<T>& vector)
{
	std::cout << "//New Vector-----//" << std::endl;
	for (size_t i = 0; i < vector.size(); i++)
		std::cout << vector[i] << std::endl;
}

int	main(void)
{
	std::vector<std::string> V;
	ft::vector<std::string> strVector;
	ft::vector<std::string> strVector2;
	ft::vector<std::string> strVector3;
	ft::vector<std::string> emptyVector;

	strVector.push_back("1rst");
	strVector.push_back("2nd");
	strVector.push_back("3rd");
	strVector.push_back("4rth");
	strVector.push_back("5th");
	strVector3.push_back("lol");
	strVector3.push_back("Hola");
	strVector3.push_back("mani");
	strVector3.push_back("man");

	printVector(strVector);
	std::cout << "Capacity ; " << strVector.capacity() << std::endl;
	strVector.shrink_to_fit();
	std::cout << "Capacity ; " << strVector.capacity() << std::endl;

	strVector2 = strVector;
	printVector(strVector2);
	std::cout << "Capacity ; " << strVector.capacity() << std::endl;

	if (!strVector2.empty())
		std::cout << "Not empty" << std::endl;
	if (emptyVector.empty())
		std::cout << "Empty" << std::endl;

	std::cout << "Back :" << strVector2.back() << std::endl;
	std::string* tmpV = strVector2.data();
	*tmpV = "10";
	++tmpV;
	*tmpV = "20";
	tmpV[2] = "200";

	std::cout << "myvector contains:";
	for (unsigned i=0; i<strVector2.size(); ++i)
		std::cout << ' ' << strVector2[i] << std::endl;

	ft::vector<std::string>::iterator it = strVector.begin();
	std::cout << *it << std::endl;
	it++;
	std::cout << *it << std::endl;
	++it;
	std::cout << *it << std::endl;
	--it;
	std::cout << *it << std::endl;
	ft::vector<std::string>::iterator it2 = strVector.end();
	if (it == it2)
		std::cout << "Equal" << std::endl;
	else
		std::cout << "Not equal" << std::endl;

	printVector(strVector2);
	strVector2.swap(strVector3);
	printVector(strVector2);
	printVector(strVector3);



	return (0);
}