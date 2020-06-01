#include "VectorStack.h"
#include <cstdlib>

void VectorStack::push(const ValueType& value) {
	this->pushBack(value);
}

void VectorStack::pop() {
	this->popBack();
}

 ValueType& VectorStack::top() 
{
	return (*this)[size() - 1];
}

const ValueType& VectorStack::top() const {
	return (*this)[size() - 1];
}

bool VectorStack::isEmpty() const {
	if (MyVector::size() == 0) return true;
	return false;
}

size_t VectorStack::size() const {
	return  MyVector::size();
}
