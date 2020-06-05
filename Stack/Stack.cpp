#include "Stack.h"
#include "ListStack.h"
#include "VectorStack.h"
#include "StackImplementation.h"
#include <cstdlib>

#include <stdexcept>
#include <iostream>

Stack::Stack(StackContainer container)
	: _containerType(container)
{
	switch (container)
	{
	case StackContainer::List: {
		_pimpl = new ListStack();	// конкретизируйте под ваши конструкторы, если надо
		break;
	}
	case StackContainer::Vector: {
		_pimpl = new VectorStack();     // конкретизируйте под ваши конструкторы, если надо
		break;
	}
	default:
		throw std::runtime_error("Неизвестный тип контейнера");
	}
}

Stack::Stack(const ValueType* valueArray, const size_t arraySize, StackContainer container)
	: Stack(container)
{
	for (size_t i = 0; i < arraySize; i++) {
		_pimpl->push(valueArray[i]);
	}
}

Stack::Stack(const Stack& copyStack)
	: Stack(copyStack._containerType) 
{
	switch (_containerType)
	{
	case StackContainer::List: {
		_pimpl = new ListStack(*dynamic_cast<ListStack*>(copyStack._pimpl));
		break;
	}
	case StackContainer::Vector: {
		_pimpl = new VectorStack(*(dynamic_cast<VectorStack*>(copyStack._pimpl)));     // конкретизируйте под ваши конструкторы, если надо
		break;
	}
	default:
		throw std::runtime_error("Неизвестный тип контейнера");
	}
}


Stack& Stack::operator=(const Stack& copyStack)
{
	if (this == &copyStack) {
		return *this;
	}
	delete _pimpl;
	_containerType = copyStack._containerType;

	switch (_containerType)
	{
	case StackContainer::List: {
		_pimpl = new ListStack(*static_cast<ListStack*>(copyStack._pimpl));
		break;
	}
	case StackContainer::Vector: {
		_pimpl = new VectorStack(*(static_cast<VectorStack*>(copyStack._pimpl)));     // конкретизируйте под ваши конструкторы, если надо
		break;
	}
	default:
		throw std::runtime_error("Неизвестный тип контейнера");
	}

	return *this;
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
	return _pimpl->size();
}
/*
int main() {
	Stack st1(StackContainer::Vector);
	st1.push(1);
	st1.push(2);
	Stack st2(StackContainer::Vector);
	st2 = st1;
	std::cout << st2.top();
	st2.pop();
	std::cout << st2.top();
	return 0;

}
*/