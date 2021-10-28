#pragma once
class linkedlist
{
public:
	int value;
	linkedlist *next;

public:
	linkedlist();
	linkedlist(int value);

	static linkedlist* InsertNode(linkedlist *node, linkedlist *root);
	static linkedlist* clearList(linkedlist *node);
};

