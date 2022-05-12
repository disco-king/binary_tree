#include "Tree.hpp"

int main()
{
	Tree t;

	t.addValue(3);
	t.addValue(1);
	t.addValue(0);
	t.addValue(2);
	t.addValue(7);
	t.addValue(10);
	t.addValue(9);
	t.addValue(500);
	t.addValue(5);
	t.addValue(6);
	t.addValue(-1);
	t.addValue(4);

	// t.printTree();
	// std::cout << "height " << t.getHeight() << '\n';

	// Tree::Node *n;
	// n = t.getMin();
	// std::cout << "min " << n->val << '\n';
	// n = t.getMax();
	// std::cout << "max " << n->val << '\n';
	// n = t.successor(t.getRoot());
	// std::cout << "next to root " << n->val << '\n';
	// n = t.predecessor(t.getRoot());
	// std::cout << "prev to root " << n->val << '\n';
	
	// n = t.findValue(5);
	// if(n)
	// 	std::cout << "5 found\n";


	t.removeValue(2);
	t.removeValue(0);
	std::cout << "\nremoved 2 and 0\n";

	t.graphicPrint();

	t.addValue(2);
	t.addValue(0);
	std::cout << "\nadded 2 and 0\n";
	t.removeValue(7);
	std::cout << "removed 7\n";

	t.graphicPrint();
}