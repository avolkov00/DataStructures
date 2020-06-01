#include "ListStack.h"
#include <cstdlib>
ListStack::ListStack() {}

ListStack::ListStack(const ListStack& copyList) : LinkedList(copyList) {}

void ListStack::push(const ValueType& value)
{
	pushFront(value);
}

void ListStack::pop()
{
	removeFront();
}

const ValueType& ListStack::top() const
{
	return getNode(0)->value;
}

bool ListStack::isEmpty() const
{
	if (LinkedList::size() == 0) return true;
	return false;
}

size_t ListStack::size() const
{
	return LinkedList::size();
}