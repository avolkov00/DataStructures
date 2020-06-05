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
}


Stack& Stack::operator=(const Stack& copyStack)
{
	if (&copyStack._pimpl == &this->_pimpl) {
		return *this;	
	}
	else {
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

int main() {
	Stack st1(StackContainer::Vector);
	for (int i = 0; i < 10; i++) {
		st1.push(i);
	}
	std::cout << st1.size() << std::endl;

	Stack st2(StackContainer::Vector);
	for (int i = 10; i < 13; i++) {
		st2.push(i);
	}
	std::cout << st2.size() << std::endl;

	st2 = st1;
	std::cout << st2.size() << std::endl;

	for (int i = 0; i < 10; i++) {
		st2.pop();
	}
	std::cout << st2.size() << std::endl;

	for (int i = 20; i < 30; i++) {
		st2.push(i);
	}
	st2 = st2;
	std::cout << st2.size() << std::endl;
	return 0;

}