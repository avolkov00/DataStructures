#include "ListStack.h"
#include "LinkedList.cpp"
#include "LinkedList.h"

void ListStack::push(const ValueType& value)
{
	pushFront(value);
}

void ListStack::pop()
{
	removeFront();
}

ValueType& ListStack::top()
{
	return getNode(0)->value;
}

const ValueType& ListStack::top() const
{
	return getNode(0)->value;
}

bool ListStack::isEmpty() const
{
	if (size() == 0) return true;
	return false;
}

size_t ListStack::size() const
{
	return size();
}