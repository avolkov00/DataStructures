#include "VectorQueue.h"
#include <cstdlib>
#include <stdexcept>

void VectorQueue::enqueue(const ValueType& value) {
	MyVector::pushBack(value);
}

void VectorQueue::dequeue() {
	if (VectorQueue::size() == 0){
		throw std::out_of_range("size = 0");
	}
	else {
		_headIndex++;
		if ((float(VectorQueue::size()) / MyVector::capacity())  < (float(1)/((_coef)*(_coef)))){
			MyVector::erase(0, _headIndex);
			_headIndex = 0;
		}
	}
}


const ValueType& VectorQueue::front() const {
	return (*this)[_headIndex];
}

bool VectorQueue::isEmpty() const {
	if (MyVector::size() - _headIndex == 0) return true;
	return false;
}

size_t VectorQueue::size() const {
	return  (MyVector::size()-_headIndex);
}
