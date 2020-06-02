#include "DoubleListQueue.h"
#include <cstdlib>

void DoubleListQueue::enqueue(const ValueType& value)
{
	DoublyLinkedList::pushFront(value);
}

void DoubleListQueue::dequeue()
{
	DoublyLinkedList::removeBack();
}

const ValueType& DoubleListQueue::front() const
{
	return getNode(DoublyLinkedList::size() - 1)->value;
}

bool DoubleListQueue::isEmpty() const
{
	if (DoublyLinkedList ::size() == 0) return true;
	return false;
}

size_t DoubleListQueue::size() const
{
	return DoublyLinkedList ::size();
}