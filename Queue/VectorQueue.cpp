#include "VectorQueue.h"
#include <cstdlib>

void VectorQueue::enqueue(const ValueType& value) {
	MyVector::pushBack(value);
}

void VectorQueue::dequeue() {
	_headIndex++;
	if (float(MyVector::size())/_headIndex > 2) {
		MyVector bufVector(*this);
		MyVector::clear();
		for (size_t i = _headIndex; i < bufVector.size(); i++) {
			MyVector::pushBack(bufVector[i]);
		}
		_headIndex = 0;
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
