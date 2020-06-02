#include "ListQueue.h"
#include <cstdlib>

void ListQueue::enqueue(const ValueType& value)
{
	SinglyLinkedList::pushFront(value);
}

void ListQueue::dequeue()
{
	SinglyLinkedList::removeBack();
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