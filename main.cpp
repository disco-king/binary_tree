#include "Tree.hpp"
#include <cstdlib>

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

	// for (size_t i = 0; i < 16; i++)
	// {
	// 	t.addValue(i);
	// }
	std::cout << "tree created\n";

	t.graphicPrint();
	std::cout << "height " << t.getHeight() << '\n';

	Tree::Node *n = t.getMin();
	t.checkPars(n);
	n = t.getMax();
	t.checkPars(n);
}