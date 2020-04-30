#include "DoubleListQueue.h"

void DoubleListQueue::enqueue(const ValueType& value)
{
	pushFront(value);
}

void DoubleListQueue::dequeue()
{
	removeBack();
}

ValueType& DoubleListQueue::front()
{
	return getNode(size()-1)->value;
}

const ValueType& DoubleListQueue::front() const
{
	return getNode(size() - 1)->value;
}

bool DoubleListQueue::isEmpty() const
{
	if (size() == 0) return true;
	return false;
}

size_t DoubleListQueue::size() const
{
	return size();
}