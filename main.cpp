#include "Tree.hpp"

int main()
{
	Tree t;

	t.addValue(3);
	t.addValue(5);

	if(t.findValue(3))
		std::cout << "3 found\n";
	else
		std::cout << "3 not found\n";

	if(t.findValue(5))
		std::cout << "5 found\n";
	else
		std::cout << "5 not found\n";

}