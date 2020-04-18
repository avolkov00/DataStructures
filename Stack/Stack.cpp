#include "Stack.h"
#include "ListStack.h"
#include "VectorStack.h"
#include "StackImplementation.h"

#include <stdexcept>

Stack::Stack(StackContainer container)
	: _containerType(container)
{
	switch (container)
	{
	case StackContainer::List: {
		ListStack _pimpl;	// конкретизируйте под ваши конструкторы, если надо
		break;
	}
	case StackContainer::Vector: {
		_pimpl = VectorStack();	// конкретизируйте под ваши конструкторы, если надо
		break;
	}
	default:
		throw std::runtime_error("Неизвестный тип контейнера");
	}
}

Stack::Stack(const ValueType* valueArray, const size_t arraySize, StackContainer container)
	: _containerType(container)
{
	switch (container)
	{
	case StackContainer::List: {
		_pimpl = ListStack();	// конкретизируйте под ваши конструкторы, если надо
		for (size_t i = 0; i < arraySize; i++) _pimpl->push(valueArray[i]);
		break;
	}
	case StackContainer::Vector: {
		_pimpl = VectorStack();	// конкретизируйте под ваши конструкторы, если надо
		for (size_t i = 0; i < arraySize; i++) _pimpl->push(valueArray[i]);
		break;
	}
	default:
		throw std::runtime_error("Неизвестный тип контейнера");
	}
}

Stack::Stack(const Stack& copyStack)
	:_containerType(copyStack._containerType)
{
	*_pimpl = *(copyStack._pimpl);
}

Stack& Stack::operator=(const Stack& copyStack)
{
	// TODO: вставьте здесь оператор return
}

Stack::~Stack()
{
	delete _pimpl;		// композиция!
}

void Stack::push(const ValueType& value)
{
	// можно, т.к. push определен в интерфейсе
	_pimpl->push(value);
}

void Stack::pop()
{
	_pimpl->pop();
}

ValueType& Stack::top()
{
	return _pimpl->top();
}

const ValueType& Stack::top() const
{
	return _pimpl->top();
}

bool Stack::isEmpty() const
{
	return _pimpl->isEmpty();
}

size_t Stack::size() const
{
	return _pimpl->isEmpty();
}
