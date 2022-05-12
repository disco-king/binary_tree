#pragma once

#include <iostream>

class Tree
{
private:
	struct Node{
		Node *p;
		Node *left;
		Node *right;
		int val;
		Node(int val = 0): p(0), left(0), right(0), val(val){}
	};
	Node *head;
	int height;

	void addNode(Node *n, int val);
	void printNodes(Node *n);

public:
	Tree() : head(0), height(0){}
	void addValue(int val);
	void removeValue(int val);
	Node *findValue(int val);
	void printTree();
};

void Tree::addNode(Node *n, int val)
{
	Node **target;
	if(val < n->val)
		target = &(head->left);
	else
		target = &(head->right);

	if(*target == 0)
	{
		*target = new Node(val);
		(*target)->p = n;
	}
	else
		addNode(*target, val);
}

void Tree::addValue(int val)
{
	if(!head)
		head = new Node(val);
	else
		addNode(head, val);
}

Tree::Node *Tree::findValue(int val)
{
	if(!head)
		return head;

	Node *n = head;
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

void removeValue(int val)
{

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
	printNodes(head);
	std::cout << "\n";
}