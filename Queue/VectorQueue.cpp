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
		if (float(_headIndex / MyVector::size())  > float(1/2)) {
			MyVector bufVector(*this);
			MyVector::clear();
			for (size_t i = _headIndex; i < bufVector.size(); i++) {
				MyVector::pushBack(bufVector[i]);
			}
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
