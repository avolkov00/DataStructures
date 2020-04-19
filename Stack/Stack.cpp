#include "Stack.h"
#include "ListStack.h"
#include "VectorStack.h"
#include "StackImplementation.h"

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
	size_t size = copyStack._pimpl->size();
	ValueType* bufArr = new ValueType[size];

	for (size_t i = 0; i < size; i++)
	{
		bufArr[i] = copyStack._pimpl->top();
		copyStack._pimpl->pop();
	}

	for (size_t i = 0; i < size; i++) 
		{
		_pimpl->push(bufArr[i]);
		copyStack._pimpl->push(bufArr[i]);
	}

	delete[] bufArr;
}


Stack& Stack::operator=(const Stack& copyStack)
{
	delete _pimpl;
	_containerType = copyStack._containerType;

	size_t size = copyStack._pimpl->size();
	ValueType* bufArr = new ValueType[size];

	for (size_t i = 0; i < size; i++)
	{
		bufArr[i] = copyStack._pimpl->top();
		copyStack._pimpl->pop();
	}

	for (size_t i = 0; i < size; i++)
	{
		_pimpl->push(bufArr[i]);
		copyStack._pimpl->push(bufArr[i]);
	}

	delete[] bufArr;

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
/*
int main() {
	Stack st(StackContainer::Vector);
	st.push(1);
	st.push(2);
	std::cout << st.top();
	st.pop();
	std::cout << st.top();
	return 0;

}
*/