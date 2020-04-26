#include "../Vector/MyVector.h"

#include <iostream>
#include <cmath>
#include <cstring>

MyVector::MyVector(size_t size, ResizeStrategy strategy, float coef)
	:_size(size), _strategy(strategy), _coef(coef)
{	
	switch (_strategy) {
	case (ResizeStrategy::Multiplicative):
		if (size == 0) {
			_capacity = 1;
			_data = new ValueType[_capacity];
		}
		else {
			_capacity =  (1.0 * _size) * _coef + 1;
			_data = new ValueType[_capacity];
		}
		break;

	case (ResizeStrategy::Additive):
		_capacity =  (_size + _coef) + 1;
		_data = new ValueType[_capacity];
		break;

	default:
		std::cout << "ERROR: ResizeStrategy unknown" << std::endl;
		break;
	}

}

MyVector::MyVector(size_t size, ValueType value, ResizeStrategy strategy, float coef)
	:_size(size), _strategy(strategy), _coef(coef)
{
	switch (_strategy) {
	case (ResizeStrategy::Multiplicative):
		if (size == 0) {
			_capacity = 1;
			_data = new ValueType[_capacity];
		}
		else {
			_capacity = (1.0 * _size) * _coef + 1;
			_data = new ValueType[_capacity];
		}
		break;

	case (ResizeStrategy::Additive):
		_capacity = (_size + _coef) + 1;
		_data = new ValueType[_capacity];
		break;

	default:
		std::cout << "ERROR: ResizeStrategy unknown" << std::endl;
		break;
	}
	for (size_t index = 0; index < _size; index++) {
		_data[index] = value;
	}

}

MyVector::MyVector(const MyVector& copy)
	: _size(copy._size), _capacity(copy._capacity), _strategy(copy._strategy), _coef(copy._coef)
{
	_data = new ValueType[_capacity];
	for (size_t i = 0; i < _size; i++)
	{
		_data[i] = copy._data[i];
	}
}

MyVector& MyVector::operator=(const MyVector& copy)
{

	if (this == &copy)
		return *this;
	if (_data == nullptr) return *this;
	_size = copy._size;
	_capacity = copy._capacity;
	_strategy = copy._strategy;
	_coef = copy._coef;

	delete[] _data;
	_data = new ValueType[_capacity];
	for (size_t i = 0; i < _size; ++i) {
		_data[i] = copy._data[i];
	}

	return *this;
}

MyVector::~MyVector()
{
	if (_data != nullptr) {
		delete[] _data;
		_data = nullptr;
	}
	_size = 0;
	_capacity = 0;
}

size_t MyVector::capacity() const
{
	return _capacity;
}

size_t MyVector::size() const
{
	return _size;
}

float MyVector::loadFactor()
{
	return 1.0 * _size / _capacity;
}

ValueType& MyVector::operator[](const size_t i) const
{
	if (i < _size && i >= 0) return _data[i];
	else std::cout << "incorrect index" << std::endl;
}

void MyVector::pushBack(const ValueType& value)
{
	if (loadFactor() >= 1)
	{
		if (_strategy == ResizeStrategy::Multiplicative)
			reserve(_capacity * _coef);
		else if (_strategy == ResizeStrategy::Additive)
			reserve(_capacity + _coef);
	}
	_data[_size] = value;
	_size++;
}

void MyVector::insert(const size_t i, const ValueType& value)
{
	if (i > _size) {
		std::cout << "ERROR: INDEX OUT OF RANGE TO INSERT" << std::endl;
		return;
	}
		;
	if (loadFactor() >= 1)
	{
		if (_strategy == ResizeStrategy::Multiplicative)
			reserve(_capacity * _coef);
		else if (_strategy == ResizeStrategy::Additive)
			reserve(_capacity + _coef);
	}
	ValueType* tempCopy = new ValueType(_capacity);
	for (int j = 0; j < i; j++)
	{
		tempCopy[j] = _data[j];
	}
	tempCopy[i] = value;
	for (int j = i + 1; j < _size + 1; j++)
	{
		tempCopy[j] = _data[j - 1];
	}
	_data = tempCopy;
	_size++;
}

void MyVector::insert(const size_t idx, const MyVector& value)
{
	if (_capacity - value._size < 0)
	{
		_capacity = _capacity + value._size;
	}
	ValueType* tempCopy = new ValueType(_capacity);
	for (int j = 0; j < idx; j++)
	{
		tempCopy[j] = _data[j];
	}
	for (int j = idx; j < idx + value._size; j++)
	{
		tempCopy[j] = value[j - idx];
	}
	for (int j = idx + value._size; j < _size + value._size; j++)
	{
		tempCopy[j] = _data[j - value._size];
	}
	_data = tempCopy;
}

void MyVector::popBack()
{
	_size--;
}

void MyVector::erase(const size_t i)
{
	for (size_t j = i; j < _size - 1; j++)
	{
		_data[j] = _data[j + 1];
	}
	_size--;

}

void MyVector::erase(const size_t i, const size_t len)
{
	for (size_t j = i; j < _size; j++)
	{
		_data[j] = _data[j + len];
	}
	_size -= len;
}

long long int MyVector::find(const ValueType& value, bool isBegin) const
{
	ValueType tmp = -1;
	for (size_t i = 0; i < _size; i++)
	{
		if (_data[i] == value)
		{
			tmp = i;
			if (isBegin) return tmp;
		}
	}

	return tmp;
}

void MyVector::reserve(const size_t capacity)
{	 
	if (capacity < _size)
		_size = capacity;
	ValueType* tmp_data = new ValueType[capacity];
	memcpy(tmp_data, _data, _size * sizeof(ValueType));
	delete[]_data;
	_data = tmp_data;
	_capacity = capacity;
}


void MyVector::resize(const size_t size, const ValueType value)
{
	if (size > _size)
	{
		if (size > _capacity)
		{
			reserve(size);
		}
		for (size_t i = _size; i < _capacity; i++)
		{
			_data[i] = value;
		}
		_size = size;
	}
	else if (size < _size)
	{
		ValueType* tempCopy = new ValueType(size);
		for (int i = 0; i < _size; i++)
		{
			tempCopy[i] = _data[i];
		}
		for (int i = _size; i < size; i++){
			tempCopy[i] = value;
		}
		delete[] _data;
		_data = tempCopy;
		_size = size;
	}
}

void MyVector::clear()
{
	for (size_t i = 0; i < _size; i++)
	{
		_data[i] = 0;
	}
	_size = 0;
}

MyVector MyVector::sortedSquares(const MyVector& vec, SortedStrategy strategy)
{
	MyVector sqr(vec);

	int right = _size - 1;
	int left = 0;
	int i;
	if (strategy == SortedStrategy::Decr) i = 0;
	else if (strategy == SortedStrategy::Incr) i = _size - 1;
	while (left != right)
	{
		if (abs(vec[left]) > abs(vec[right]))
		{
			sqr._data[i] = vec[left] * vec[left];
			left++;
			if (strategy == SortedStrategy::Decr) i++;
			else if (strategy == SortedStrategy::Incr) i--;
			continue;
		}
		else if (abs(vec[left]) < abs(vec[right]))
		{
			sqr._data[i] = vec[right] * vec[right];
			right--;
			if (strategy == SortedStrategy::Decr) i++;
			else if (strategy == SortedStrategy::Incr) i--;
			continue;
		}
		else
		{
			sqr._data[i] = vec[right] * vec[right];
			if (strategy == SortedStrategy::Decr) i++;
			else if (strategy == SortedStrategy::Incr) i--;
			sqr._data[i] = vec[left] * vec[left];
			left++;
			right--;
			if (strategy == SortedStrategy::Decr) i++;
			else if (strategy == SortedStrategy::Incr) i--;
		}

	}
	sqr._data[i] = vec[left];

	return sqr;
}
