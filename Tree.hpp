#pragma once

#include <iostream>
#include <cmath>

#define RED true
#define BLACK false
#define LEFT true
#define RIGHT false

class Tree
{


public:
	struct Node{
		Node *p;
		Node *left;
		Node *right;
		int val;
		bool color;

		Node(int val = 0, Node *ptr = 0): p(ptr), left(ptr),
		right(ptr), val(val), color(RED) {}
	};

private:
	Node *root;
	Node * const nil;
	int height;

	Node *addNode(Node *head, int val, int depth);
	void insertFixup(Node *n);
	void deleteFixup(Node *n);
	void printNodes(Node *head);
	void printLevel(Node *head, int level, int depth);
	Node *treeMinimum(Node *head);
	Node *treeMaximum(Node *head);
	void transplant(Node *prev_n, Node * new_n);
	void updateHeight();
	void clearNodes(Node *head);
	// Node *getPtr(Node *par, bool side);

public:
	Tree() : root(0), height(0), nil(new Node()){
		nil->color = BLACK;
	}
	~Tree(){
		clearNodes(root);
	}

	int maxHeight(Node *head, int depth);
	void addValue(int val);
	void removeValue(int val);
	Node *findValue(int val);
	void printTree();
	void graphicPrint();
	Node *successor(Node *x);
	Node *predecessor(Node *x);
	void rotateLeft(Node *x);
	void rotateRight(Node *x);

	int getHeight(){ return height; }
	Node *getRoot(){ return root; }
	Node *getMin(){ return treeMinimum(root); }
	Node *getMax(){ return treeMaximum(root); }
	void checkPars(Node *head);
};

void Tree::insertFixup(Node *x)
{
	Node *y;
	while(x->p->color == RED)
	{
		if(x->p == x->p->p->left)
		{
			y = x->p->p->right;
			if(y->color == RED)
			{
				y->color = BLACK;
				x->p->color = BLACK;
				y->p->color = RED;
				x = x->p->p;
			}
			else
			{
				if(x == x->p->right)
					rotateLeft(x = x->p);
				x->p->color = BLACK;
				x->p->p->color = RED;
				rotateRight(x->p->p);
			}
		}
		else
		{
			y = x->p->p->left;
			if(y->color == RED)
			{
				y->color = BLACK;
				x->p->color = BLACK;
				y->p->color = RED;
				x = x->p->p;
			}
			else
			{
				if(x == x->p->left)
					rotateRight(x = x->p);
				x->p->color = BLACK;
				x->p->p->color = RED;
				rotateLeft(x->p->p);
			}
		}
	}
	root->color = BLACK;
}

void Tree::rotateLeft(Node *x)
{
	Node *y = x->right;
	x->right = y->left;
	if(y->left != nil)
		y->left->p = x;

	y->p = x->p;
	if(y->p == nil)
		root = y;
	else if(x == x->p->left)
		y->p->left = y;
	else
		y->p->right = y;
	x->p = y;
	y->left = x;
	updateHeight();
}

void Tree::rotateRight(Node *x)
{
	Node *y = x->left;
	x->left = y->right;
	if(y->right != nil)
		y->right->p = x;

	y->p = x->p;
	if(y->p == nil)
		root = y;
	else if(x == x->p->left)
		y->p->left = y;
	else
		y->p->right = y;
	x->p = y;
	y->right = x;
	updateHeight();
}

void Tree::updateHeight()
{
	int h = maxHeight(root, 0);
	if(h != height)
		height = h;
}

int Tree::maxHeight(Node *head, int depth)
{
	if(head == nil)
		return depth - 1;
	if(head->right == nil)
		return maxHeight(head->left, depth + 1);
	if(head->left == nil)
		return maxHeight(head->right, depth + 1);

	int left = maxHeight(head->left, depth + 1);
	int right = maxHeight(head->right, depth + 1);
	return (left > right) ? left : right;
}

Tree::Node *Tree::addNode(Node *n, int val, int depth)
{
	if(val < n->val)
	{
		if(n->left == nil)
		{
			height = (++depth > height) ? depth : height;
			n->left = new Node(val, nil);
			n->left->p = n;
			return n->left;
		}
		return addNode(n->left, val, depth + 1);
	}
	else
	{
		if(n->right == nil)
		{
			height = (++depth > height) ? depth : height;
			n->right = new Node(val, nil);
			n->right->p = n;
			return n->right;
		}
		return addNode(n->right, val, depth + 1);
	}
}

void Tree::addValue(int val)
{
	if(val > 999 || val < -99)
		return;
	if(!root)
	{
		root = new Node(val, nil);
		root->color = BLACK;
	}
	else
		insertFixup(addNode(root, val, 0));
}

Tree::Node *Tree::findValue(int val)
{
	if(root == nil)
		return root;

	Node *n = root;
	while (n != nil)
	{
		if(val == n->val)
			break;
		if(val < n->val)
			n = n->left;
		else
			n = n->right;
	}
	return n;
}

void Tree::transplant(Node *prev_n, Node * new_n)
{
	if(prev_n->p == nil)
		root = new_n;
	else if(prev_n == prev_n->p->left)
		prev_n->p->left = new_n;
	else
		prev_n->p->right = new_n;
	new_n->p = prev_n->p;
}

void Tree::removeValue(int val)
{
	Node *n = findValue(val);
	if(n == nil)
		return;
	Node *repl;
	bool orig_color = n->color;

	if(n->right == nil)
	{
		repl = n->left;
		transplant(n, n->left);
	}
	else if(n->left == nil)
	{
		repl = n->right;
		transplant(n, n->right);
	}
	else
	{
		Node *subs = treeMinimum(n->right);
		orig_color = subs->color;
		repl = subs->right;
		if(subs->p == n)
			repl->p = subs;
		else
		{
			transplant(subs, subs->right);
			subs->right = n->right;
			subs->right->p = subs;
		}
		transplant(n, subs);
		subs->left = n->left;
		subs->left->p = subs;
		subs->color = n->color;
	}

	delete n;
	if(orig_color == BLACK)
		deleteFixup(repl);
	updateHeight();
}

void Tree::deleteFixup(Node *n)
{
	Node *s;
	while(n != root && n->color == BLACK)
	{
		if(n == n->p->left)
		{
			s = n->p->right;
			if(s->color == RED)
			{
				s->color = BLACK;
				s->p->color = RED;
				rotateLeft(s->p);
				s = n->p->right;
			}
			if(s->left->color == BLACK && s->right->color == BLACK)
			{
				s->color = RED;
				n = n->p;
			}
			else
			{
				if(s->right->color == BLACK)
				{
					s->left->color = BLACK;
					s->color = RED;
					rotateRight(s);
					s = n->p->right;
				}
				s->color = n->p->color;
				n->p->color = BLACK;
				s->right->color = BLACK;
				rotateLeft(n->p);
				n = root;
			}
		}
		else
		{
			s = n->p->left;
			if(s->color == RED)
			{
				s->color = BLACK;
				s->p->color = RED;
				rotateRight(s->p);
				s = n->p->left;
			}
			if(s->left->color == BLACK && s->right->color == BLACK)
			{
				s->color = RED;
				n = n->p;
			}
			else
			{
				if(s->left->color == BLACK)
				{
					s->right->color = BLACK;
					s->color = RED;
					rotateLeft(s);
					s = n->p->left;
				}
				s->color = n->p->color;
				n->p->color = BLACK;
				s->left->color = BLACK;
				rotateRight(n->p);
				n = root;
			}
		}
	}
	n->color = BLACK;
}


void Tree::printNodes(Node *head)
{
	if(head->left != nil)
		printNodes(head->left);
	std::cout << head->val << ' ';
	if(head->right != nil)
		printNodes(head->right);
}

void Tree::printTree()
{
	printNodes(root);
	std::cout << "\n";
}

Tree::Node *Tree::treeMinimum(Node *head)
{
	if(head->left == nil)
		return head;
	
	return treeMinimum(head->left);
}

Tree::Node *Tree::treeMaximum(Node *head)
{
	if(head->right == nil)
		return head;
	
	return treeMaximum(head->right);
}

int width(int num)
{
	if(!num)
		return 1;
	int count = 0;
	if (num < 0)
	{
		num *= -1;
		count++;
	}
	while(num > 0)
	{
		num /= 10;
		count++;
	}
	return count;
}

void Tree::printLevel(Tree::Node *head, int level, int depth)
{
	if(depth != level)
	{
		if(head->left != nil)
			printLevel(head->left, level, depth + 1);
		else
			printLevel(0, depth + 1, depth + 1);
		if(head->right != nil)
			printLevel(head->right, level, depth + 1);
		else
			printLevel(0, depth + 1, depth + 1);
		return;
	}
	int pad = pow(2, height - depth + 1) - 1;
	int num_width = pad + 1 - (head ? width(head->val) : 1);
	for (size_t i = 0; i < num_width; i++)
		std::cout << ' ';
	if(head)
		std::cout << head->val << (head->color ? 'r' : 'b');
	else
		std::cout << ' ' << ' ';
	for (size_t i = 0; i < pad; i++)
		std::cout << ' ';
}

void Tree::graphicPrint()
{
	for (int i = 0; i <= height; i++)
	{
		printLevel(root, i, 0);
		std::cout << '\n' << '\n';
	}
}

Tree::Node *Tree::successor(Node *x)
{
	if(x->right != nil)
		return treeMinimum(x->right);
	Node *y = x;
	while(y != nil && x != y->left)
	{
		x = y;
		y = y->p;
	}
	return y;
}

Tree::Node *Tree::predecessor(Node *x)
{
	if(x->left != nil)
		return treeMaximum(x->left);
	Node *y = x;
	while(y != nil && x != y->right)
	{
		x = y;
		y = y->p;
	}
	return y;
}

void Tree::checkPars(Node *head)
{
	if(head == nil)
		return;
	std::cout << "path to root for " << head->val << ": ";
	head = head->p;
	while(head != nil)
	{
		std::cout << head->val << ' ';
		head = head->p;
	}
	std::cout << "\nroot reached\n";
}

void Tree::clearNodes(Node *head)
{
	if(head == nil)
		return;
	if(head->left != nil)
		clearNodes(head->left);
	if(head->right != nil)
		clearNodes(head->right);
	delete head;
}

// Tree::Node *Tree::getPtr(Node *par, bool side)
// {
// 	Node *ret;
// 	if(side == LEFT)
// 		ret = par->left;
// 	else
// 		ret = par->right;
// 	if(ret == 0)
// 	{
// 		nil->p = &(*par);
// 		ret = nil;
// 	}
// 	return ret;
// }