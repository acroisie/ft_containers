#include	"../includes/vector.hpp"
#include	"../includes/map.hpp"
#include	"../includes/bidirectional_iterator.hpp"
#include	<iostream>
#include	<vector>
#include	<map>
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
	// srand(time(NULL));
	ft::map<int, std::string> test;

	test[34] = "blabla";
	test[654] = "foo";
	test[4] = "bar";
	test[3] = "lol";
	test[56] = "prout";
	test[7] = "caca";
	test[89] = "pop";
	test[3] = "poupi";
	test[45] = "koko1";
	test[7] = "koko2";
	test[10] = "koko3";

	ft::map<int, std::string>::iterator it = test.begin();
	ft::map<int, std::string>::iterator it_end = test.end();
	test.printTree(test._meta, "	", false);
	std::cout << "Key: " << it->first << "| Value: " << it->second << std::endl;
	++it;
	std::cout << "Key: " << it->first << "| Value: " << it->second << std::endl;
	it++;
	std::cout << "Key: " << it->first << "| Value: " << it->second << std::endl;
	it++;
	std::cout << "Key: " << it->first << "| Value: " << it->second << std::endl;
	it++;
	std::cout << "Key: " << it->first << "| Value: " << it->second << std::endl;
	it++;
	std::cout << "Key: END " << it_end->first << "| Value: " << it_end->second << std::endl;
	it_end--;
	std::cout << "Key: " << it_end->first << "| Value: " << it_end->second << std::endl;
	it_end--;
	std::cout << "Key: " << it_end->first << "| Value: " << it_end->second << std::endl;
	it_end--;
	std::cout << "Key: " << it_end->first << "| Value: " << it_end->second << std::endl;
	it_end--;
	std::cout << "Key: " << it_end->first << "| Value: " << it_end->second << std::endl;
	it_end--;
	std::cout << "Key: " << it_end->first << "| Value: " << it_end->second << std::endl;
	it_end--;
	std::cout << "Key: " << it_end->first << "| Value: " << it_end->second << std::endl;

	return (0);
}