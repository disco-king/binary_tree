#include "Tree.hpp"
#include <stdlib.h>
#include <unistd.h>

int main()
{
	Tree t;

	t.addValue(0);
	t.addValue(1);
	t.addValue(2);
	t.addValue(3);
	t.addValue(5);
	t.addValue(7);
	t.addValue(10);
	t.addValue(20);
	t.addValue(-1);
	t.addValue(-2);
	t.addValue(-3);

	std::cout << "tree created\n";

	t.graphicPrint();
	std::cout << "height " << t.getHeight() << '\n';
	
	std::cout << "removing -1\n";
	t.removeValue(-1);
	std::cout << "removing 3\n";
	t.removeValue(3);
	std::cout << "removing 3\n";
	t.removeValue(10);

	t.graphicPrint();
	std::cout << "height " << t.getHeight() << '\n';

	Tree::Node *n = t.getMin();
	t.checkPars(n);
	n = t.getMax();
	t.checkPars(n);

	
	// for (size_t i = 1; i < 17; i++)
	// {
	// 	t.addValue(i);
	// 	t.graphicPrint();
	// 	sleep(2);
	// 	if(system("CLS"))
	// 		system("clear");
	// }
	// for (size_t i = 16; i > 1; i--)
	// {
	// 	t.removeValue(i);
	// 	t.graphicPrint();
	// 	sleep(2);
	// 	if(system("CLS"))
	// 		system("clear");
	// }
}