#include "ListQueue.h"
#include <cstdlib>
#include <stdexcept>

void ListQueue::enqueue(const ValueType& value)
{
	SinglyLinkedList::pushFront(value);
}

void ListQueue::dequeue()
{
	if (ListQueue::size() == 0) {
		throw std::out_of_range("size = 0");
	}
	else {
		SinglyLinkedList::removeBack();
	}
}

const ValueType& ListQueue::front() const
{
	return getNode(SinglyLinkedList::size() - 1)->value;
}

bool ListQueue::isEmpty() const
{
	if (SinglyLinkedList::size() == 0) return true;
	return false;
}

size_t ListQueue::size() const
{
	return SinglyLinkedList::size();
}