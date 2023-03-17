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
	srand(time(NULL));
	std::map<int, std::string> test;

	// test[rand()] = "blabla";
	// test[rand()] = "foo";
	// test[rand()] = "bar";
	// test[rand()] = "lol";
	// test[rand()] = "prout";
	// test[rand()] = "caca";
	// test[rand()] = "pop";
	// test[rand()] = "poupi";
	// test[rand()] = "koko1";
	// test[rand()] = "koko2";
	// test[rand()] = "koko3";


	std::map<int, std::string>::iterator it = test.begin();
	std::map<int, std::string>::iterator it_end = test.end();
	// test.printTree(test._meta, "	", false);
	std::cout << "Key: " << it->first << "| Value: " << it->second << std::endl;
	// ++it;
	// std::cout << "Key: " << it->first << "| Value: " << it->second << std::endl;
	// it++;
	// std::cout << "Key: " << it->first << "| Value: " << it->second << std::endl;
	// it++;
	// std::cout << "Key: " << it->first << "| Value: " << it->second << std::endl;
	// it++;
	// std::cout << "Key: " << it->first << "| Value: " << it->second << std::endl;
	// it++;
	std::cout << "Key: END " << it_end->first << "| Value: " << it_end->second << std::endl;
	// it_end--;
	// std::cout << "Key: " << it_end->first << "| Value: " << it_end->second << std::endl;
	// it_end--;
	// std::cout << "Key: " << it_end->first << "| Value: " << it_end->second << std::endl;
	// it_end--;
	// std::cout << "Key: " << it_end->first << "| Value: " << it_end->second << std::endl;
	// it_end--;
	// std::cout << "Key: " << it_end->first << "| Value: " << it_end->second << std::endl;
	// it_end--;
	// std::cout << "Key: " << it_end->first << "| Value: " << it_end->second << std::endl;
	// it_end--;
	// std::cout << "Key: " << it_end->first << "| Value: " << it_end->second << std::endl;

	return (0);
}