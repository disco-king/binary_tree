#pragma once

#include <iostream>
#include <cmath>


class Tree
{
public:
	struct Node{
		Node *p;
		Node *left;
		Node *right;
		int val;
		bool black;
		Node(int val = 0): p(0), left(0),
		right(0), val(val), black(true) {}
	};

private:
	Node *root;
	int height;

	void addNode(Node *head, int val, int depth);
	void printNodes(Node *head);
	void printLevel(Node *head, int level, int depth);
	Node *treeMinimum(Node *head);
	Node *treeMaximum(Node *head);
	void transplant(Node *prev_n, Node * new_n);

public:
	Tree() : root(0), height(0){}

	void addValue(int val);
	void removeValue(int val);
	Node *findValue(int val);
	void printTree();
	void graphicPrint();
	Node *successor(Node *x);
	Node *predecessor(Node *x);

	int getHeight(){ return height; }
	Node *getRoot(){ return root; }
	Node *getMin(){ return treeMinimum(root); }
	Node *getMax(){ return treeMaximum(root); }
};

void Tree::addNode(Node *n, int val, int depth)
{
	if(val < n->val)
	{
		if(!n->left)
		{
			n->left = new Node(val);
			n->left->p = n;
		}
		else
			return addNode(n->left, val, depth + 1);
	}
	else
	{
		if(!n->right)
		{
			n->right = new Node(val);
			n->right->p = n;
		}
		else
			return addNode(n->right, val, depth + 1);
	}
	if(depth > height)
		height = depth;
}

void Tree::addValue(int val)
{
	if(val > 999 || val < -99)
		return;
	if(!root)
		root = new Node(val);
	else
		addNode(root, val, 1);
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

	if(!n->right)
		transplant(n, n->left);
	else if(!n->left)
		transplant(n, n->right);
	else
	{
		Node *subs = treeMinimum(n->right);
		if(subs->p != n)
		{
			transplant(subs, subs->right);
			subs->right = n->right;
			subs->right->p = subs;
		}
		transplant(n, subs);
		subs->left = n->left;
		subs->left->p = subs;
	}

	delete n;
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
	int num_width = pad + 2 - (head ? width(head->val) : 1);
	for (size_t i = 0; i < num_width; i++)
		std::cout << ' ';
	if(head)
		std::cout << head->val;
	else
		std::cout << ' ';
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