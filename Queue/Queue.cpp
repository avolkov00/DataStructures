#include "Queue.h"
#include "ListQueue.h"
#include "DoubleListQueue.h"
#include "VectorQueue.h"
#include "QueueImplementation.h"

#include <stdexcept>
#include <iostream>

Queue::Queue(QueueContainer container)
	: _containerType(container)
{
	switch (container)
	{
	case QueueContainer::List: {
		_pimpl = new ListQueue();	// конкретизируйте под ваши конструкторы, если надо
		break;
	}
	case QueueContainer::Vector: {
		_pimpl = new VectorQueue();     // конкретизируйте под ваши конструкторы, если надо
		break;
	}
	case QueueContainer::DoubleList: {
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
	size_t size = copyQueue._pimpl->size();
	ValueType* bufArr = new ValueType[size];

	for (size_t i = 0; i < size; i++)
	{
		bufArr[i] = copyQueue._pimpl->front();
		copyQueue._pimpl->dequeue();
	}

	for (size_t i = 0; i < size; i++) 
		{
		_pimpl->enqueue(bufArr[i]);
		copyQueue._pimpl->enqueue(bufArr[i]);
	}

	delete[] bufArr;
}


Queue& Queue::operator=(const Queue& copyQueue)
{
	delete _pimpl;
	_containerType = copyQueue._containerType;

	size_t size = copyQueue._pimpl->size();
	ValueType* bufArr = new ValueType[size];

	for (size_t i = 0; i < size; i++)
	{
		bufArr[i] = copyQueue._pimpl->front();
		copyQueue._pimpl->dequeue();
	}

	for (size_t i = 0; i < size; i++)
	{
		_pimpl->enqueue(bufArr[i]);
		copyQueue._pimpl->enqueue(bufArr[i]);
	}

	delete[] bufArr;

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
	_pimpl->dequeue();
}

ValueType& Queue::front()
{
	return _pimpl->front();
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
	return _pimpl->isEmpty();
}

int main() {
	Queue st(QueueContainer::Vector);
	st.enqueue(1);
	st.enqueue(2);
	std::cout << st.front();
	st.dequeue();
	std::cout << st.front();
	return 0;

}
