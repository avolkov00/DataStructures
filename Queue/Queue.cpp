#include "Queue.h"
#include "ListQueue.h"
#include "DoubleListQueue.h"
#include "VectorQueue.h"
#include "QueueImplementation.h"
#include <cstdlib>

#include <stdexcept>
#include <iostream>

Queue::Queue(QueueContainer container)
	: _containerType(container)
{
	switch (container)
	{
	case QueueContainer::SinglyLinkedList: {
		_pimpl = new ListQueue();	// конкретизируйте под ваши конструкторы, если надо
		break;
	}
	case QueueContainer::Vector: {
		_pimpl = new VectorQueue();     // конкретизируйте под ваши конструкторы, если надо
		break;
	}
	case QueueContainer::DoublyLinkedList: {
		_pimpl = new DoubleListQueue();	// конкретизируйте под ваши конструкторы, если надо
		break;
	}
	default:
		throw std::runtime_error("Неизвестный тип контейнера");
	}
}

Queue::Queue(const ValueType* valueArray, const size_t arraySize, QueueContainer container)
	: Queue(container)
{
	for (size_t i = 0; i < arraySize; i++) {
		_pimpl->enqueue(valueArray[i]);
	}
}

Queue::Queue(const Queue& copyQueue)
	: Queue(copyQueue._containerType) 
{
	switch (_containerType)
	{
	case QueueContainer::SinglyLinkedList: {
		_pimpl = new ListQueue(*static_cast<ListQueue*>(copyQueue._pimpl));
		break;
	}
	case QueueContainer::Vector: {
		_pimpl = new VectorQueue(*(static_cast<VectorQueue*>(copyQueue._pimpl)));     // конкретизируйте под ваши конструкторы, если надо
		break;
	}
	case QueueContainer::DoublyLinkedList:{
		_pimpl = new DoubleListQueue(*(static_cast<DoubleListQueue*>(copyQueue._pimpl)));     // конкретизируйте под ваши конструкторы, если надо
		break;
	}
	default:
		throw std::runtime_error("Неизвестный тип контейнера");
	}
}


Queue& Queue::operator=(const Queue& copyQueue)
{
	if (this == &copyQueue) {
		return *this;
	}
	delete _pimpl;
	_containerType = copyQueue._containerType;

	switch (_containerType)
	{
	case QueueContainer::SinglyLinkedList: {
		_pimpl = new ListQueue(*static_cast<ListQueue*>(copyQueue._pimpl));
		break;
	}
	case QueueContainer::Vector: {
		_pimpl = new VectorQueue(*(static_cast<VectorQueue*>(copyQueue._pimpl)));     // конкретизируйте под ваши конструкторы, если надо
		break;
	}
	case QueueContainer::DoublyLinkedList:{
	   _pimpl = new DoubleListQueue(*(static_cast<DoubleListQueue*>(copyQueue._pimpl)));     // конкретизируйте под ваши конструкторы, если надо
	   break;
	}
	default:
	   throw std::runtime_error("Неизвестный тип контейнера");
	}

	return *this;
}

Queue::~Queue()
{
	delete _pimpl;		// композиция!
}

void Queue::enqueue(const ValueType& value)
{
	// можно, т.к. push определен в интерфейсе
	_pimpl->enqueue(value);
}

void Queue::dequeue()
{
	if (Queue::size() == 0) {
		throw std::out_of_range("size = 0");
	}
	else {
		_pimpl->dequeue();
	}
}

const ValueType& Queue::front() const
{
	return _pimpl->front();
}

bool Queue::isEmpty() const
{
	return _pimpl->isEmpty();
}

size_t Queue::size() const
{
	return _pimpl->size();
}

int main() {
	Queue st(QueueContainer::Vector);
	st.enqueue(1);
	st.enqueue(2);
	Queue st2(QueueContainer::Vector);
	st2 = st;
	std::cout << st2.front();
	st2.dequeue();
	std::cout << st2.front();
	return 0;

}
