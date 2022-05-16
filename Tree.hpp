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
	void deleteFixup(Node *n, bool side);
	void printNodes(Node *head);
	void printLevel(Node *head, int level, int depth);
	Node *treeMinimum(Node *head);
	Node *treeMaximum(Node *head);
	void transplant(Node *prev_n, Node * new_n);
	void updateHeight();
	void clearNodes(Node *head);
	Node *getPtr(Node *par, bool side);

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
	while(x->p && x->p->color == RED)
	{
		if(x->p == x->p->p->left)
		{
			y = x->p->p->right;
			if(y && y->color == RED)
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
			if(y && y->color == RED)
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
	if(y->left)
		y->left->p = x;

	y->p = x->p;
	if(!y->p)
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
	if(y->right)
		y->right->p = x;

	y->p = x->p;
	if(!y->p)
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
	if(!head)
		return depth - 1;
	if(!head->right)
		return maxHeight(head->left, depth + 1);
	if(!head->left)
		return maxHeight(head->right, depth + 1);

	int left = maxHeight(head->left, depth + 1);
	int right = maxHeight(head->right, depth + 1);
	return (left > right) ? left : right;
}

Tree::Node *Tree::addNode(Node *n, int val, int depth)
{
	if(val < n->val)
	{
		if(!n->left)
		{
			height = (++depth > height) ? depth : height;
			n->left = new Node(val);
			n->left->p = n;
			return n->left;
		}
		return addNode(n->left, val, depth + 1);
	}
	else
	{
		if(!n->right)
		{
			height = (++depth > height) ? depth : height;
			n->right = new Node(val);
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
		root = new Node(val);
		root->color = BLACK;
	}
	else
		insertFixup(addNode(root, val, 0));
}

Tree::Node *Tree::findValue(int val)
{
	if(!root)
		return root;

	Node *n = root;
	while (n)
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
	if(!prev_n->p)
		root = new_n;
	else if(prev_n == prev_n->p->left)
		prev_n->p->left = new_n;
	else
		prev_n->p->right = new_n;
	if(new_n)
		new_n->p = prev_n->p;
}

void Tree::removeValue(int val)
{
	Node *n = findValue(val);
	if(!n)
		return;
	Node *repl;
	bool side;
	bool orig_color = n->color;

	if(!n->right)
	{
		repl = getPtr(n, side = LEFT);
		transplant(n, n->left);
	}
	else if(!n->left)
	{
		repl = getPtr(n, side = RIGHT);
		transplant(n, n->right);
	}
	else
	{
		Node *subs = treeMinimum(n->right);
		orig_color = subs->color;
		repl = getPtr(subs, side = RIGHT);
		if(subs->p != n)
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
		deleteFixup(repl, side);
	updateHeight();
}

void Tree::deleteFixup(Node *n, bool side)
{
	Node *s;
	while(n != root && n->color != BLACK)
	{
		if(side == LEFT)
		{
			s = n->p->right;
			if(s->color == RED)
			{
				s->color = BLACK;
				s->p->color = RED;
				rotateLeft(s->p);
				s = n->p->right;
			}
			if((!s->left || s->left->color == BLACK) 
				&& (!s->right || s->right->color == BLACK))
			{
				s->color = RED;
				n = n->p;
			}
			else
			{
				if(!s->right || s->right->color == BLACK)
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

		}
	}
	n->color = BLACK;
}


void Tree::printNodes(Node *head)
{
	if(head->left)
		printNodes(head->left);
	std::cout << head->val << ' ';
	if(head->right)
		printNodes(head->right);
}

void Tree::printTree()
{
	printNodes(root);
	std::cout << "\n";
}

Tree::Node *Tree::treeMinimum(Node *head)
{
	if(!head->left)
		return head;
	
	return treeMinimum(head->left);
}

Tree::Node *Tree::treeMaximum(Node *head)
{
	if(!head->right)
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
		if(head->left)
			printLevel(head->left, level, depth + 1);
		else
			printLevel(0, depth + 1, depth + 1);
		if(head->right)
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
	if(x->right)
		return treeMinimum(x->right);
	Node *y = x;
	while(y && x != y->left)
	{
		x = y;
		y = y->p;
	}
	return y;
}

Tree::Node *Tree::predecessor(Node *x)
{
	if(x->left)
		return treeMaximum(x->left);
	Node *y = x;
	while(y && x != y->right)
	{
		x = y;
		y = y->p;
	}
	return y;
}

void Tree::checkPars(Node *head)
{
	if(!head)
		return;
	std::cout << "path to root for " << head->val << ": ";
	head = head->p;
	while(head)
	{
		std::cout << head->val << ' ';
		head = head->p;
	}
	std::cout << "\nroot reached\n";
}

void Tree::clearNodes(Node *head)
{
	if(!head)
		return;
	if(head->left)
		clearNodes(head->left);
	if(head->right)
		clearNodes(head->right);
	delete head;
}

Tree::Node *Tree::getPtr(Node *par, bool side)
{
	Node *ret;
	if(side == LEFT)
		ret = par->left;
	else
		ret = par->right;
	if(ret == 0)
	{
		nil->p = &(*par);
		ret = nil;
	}
	return ret;
}