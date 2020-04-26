#include "ListQueue.h"

void ListQueue::enqueue(const ValueType& value)
{
	pushFront(value);
}

void ListQueue::dequeue()
{
	removeBack();
}

ValueType& ListQueue::front()
{
	return getNode(size()-1)->value;
}

const ValueType& ListQueue::front() const
{
	return getNode(0)->value;
}

bool ListQueue::isEmpty() const
{
	if (size() == 0) return true;
	return false;
}

size_t ListQueue::size() const
{
	return size();
}