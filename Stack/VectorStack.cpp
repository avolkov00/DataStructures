#include "VectorStack.h"
#include <cstdlib>
#include <stdexcept>

void VectorStack::push(const ValueType& value) {
	this->pushBack(value);
}

void VectorStack::pop() {
	if (VectorStack::size() == 0) {
		throw std::out_of_range("size = 0");
	}
	else {
		this->popBack();
	}	
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
