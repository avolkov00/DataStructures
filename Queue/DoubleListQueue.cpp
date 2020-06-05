#include "DoubleListQueue.h"
#include <cstdlib>
#include <stdexcept>
void DoubleListQueue::enqueue(const ValueType& value)
{
	DoublyLinkedList::pushFront(value);
}

void DoubleListQueue::dequeue()
{
	if (DoubleListQueue::size() == 0) {
		throw std::out_of_range("size = 0");
	}
	else {
		DoublyLinkedList::removeBack();
	}
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