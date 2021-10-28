#include "linkedlist.h"

linkedlist::linkedlist()
{
}

linkedlist::linkedlist(int value)
{
	this->value = value;
	this->next = 0;
}

linkedlist * linkedlist::InsertNode(linkedlist * node, linkedlist * root)
{
	if (root != nullptr)
	{
		node->next = root;
		return node;
	}
	else
	{
		root = node;
		return root;
	}
}

linkedlist * linkedlist::clearList(linkedlist * node)
{
	return nullptr;
}
