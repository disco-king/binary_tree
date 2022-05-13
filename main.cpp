#include "Tree.hpp"
#include <cstdlib>

int main()
{
	Tree t;

	t.addValue(3);
	t.addValue(1);
	t.addValue(0);
	t.addValue(2);
	t.addValue(7);
	t.addValue(10);
	t.addValue(20);
	t.addValue(5);
	t.addValue(-1);

	t.graphicPrint();
	std::cout << "height " << t.getHeight() << '\n';

	Tree::Node *n = t.findValue(7);
	t.rotateLeft(n);

	t.graphicPrint();
	std::cout << "height " << t.getHeight() << '\n';

	n = t.findValue(10);
	t.rotateLeft(n);

	t.graphicPrint();
	std::cout << "height " << t.getHeight() << '\n';

	n = t.findValue(20);
	t.rotateRight(n);

	t.graphicPrint();
	std::cout << "height " << t.getHeight() << '\n';

	n = t.findValue(10);
	t.rotateRight(n);

	t.graphicPrint();
	std::cout << "height " << t.getHeight() << '\n';

	n = t.findValue(5);
	t.checkPars(n);
	n = t.findValue(20);
	t.checkPars(n);
}