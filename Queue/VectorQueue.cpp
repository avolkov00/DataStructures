#include "VectorQueue.h"

void VectorQueue::enqueue(const ValueType& value) {
	this->pushBack(value);
}

void VectorQueue::dequeue() {
	_headIndex++;
	if (float(size())/_headIndex > 2) {
		MyVector bufVector(*this);
		this->clear();
		for (size_t i = _headIndex; i < bufVector.size(); i++) {
			this->pushBack(bufVector[i]);
		}
		_headIndex = 0;
	}
}

 ValueType& VectorQueue::front()
{
	return (*this)[_headIndex];
}

const ValueType& VectorQueue::front() const {
	return (*this)[_headIndex];
}

bool VectorQueue::isEmpty() const {
	return MyVector::size();
}

size_t VectorQueue::size() const {
	return  MyVector::size();
}
