#include "MyVector.h"

#include <iostream>
#include <cstring>
#include<utility>
#include <cmath>
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
			_capacity =  ceil(_coef *_size);
			_data = new ValueType[_capacity];
		}
		break;

	case (ResizeStrategy::Additive):
		_capacity = ceil(_size + _coef) ;
		_data = new ValueType[_capacity];
		break;

	default:
		throw std::invalid_argument("Incorrect Strategy");
		break;
	}
	for (size_t index = 0; index < _size; index++) {
		_data[index] = ValueType();
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
			_capacity = ceil(_coef * _size);
			_data = new ValueType[_capacity];
		}
		break;

	case (ResizeStrategy::Additive):
		_capacity = ceil(_size + _coef);
		_data = new ValueType[_capacity];
		break;

	default:
		throw std::out_of_range("Incorrect idx");
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
	MyVector buf(copy);
	_size = copy._size;
	_capacity = copy._capacity;
	_strategy = copy._strategy;
	_coef = copy._coef;
	std::swap(_data, buf._data);
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
	else throw std::out_of_range("Incorrect idx");
 }

void MyVector::pushBack(const ValueType& value)
{
	if (loadFactor() >= 1)
	{
		if (_strategy == ResizeStrategy::Multiplicative)
			reserve(ceil(_coef * _capacity));
		else if (_strategy == ResizeStrategy::Additive)
			reserve(ceil(_capacity + _coef));
	}
	_data[_size] = value;
	_size++;
}

void MyVector::insert(const size_t i, const ValueType& value)
{
	if (i > _size) {
		throw std::out_of_range("Incorrect idx");
		return;
	};
	if (i == _size) {
		pushBack(value);
		return;
	}
	if (loadFactor() >= 1)
	{
		if (_strategy == ResizeStrategy::Multiplicative)
			reserve(ceil(_coef * _capacity));
		else if (_strategy == ResizeStrategy::Additive)
			reserve(ceil(_capacity + _coef));
	}

	ValueType* tempCopy = new ValueType[_capacity];
	for (int j = 0; j < i; j++)
	{
		tempCopy[j] = _data[j];
	}
	tempCopy[i] = value;
	for (int j = i + 1; j < _size + 1; j++)
	{
		tempCopy[j] = _data[j - 1];
	}
	std::swap(_data, tempCopy);
	delete[] tempCopy;
	_size++;
}

void MyVector::insert(const size_t idx, const MyVector& value)
{
	if (_capacity < value._size + _size)
	{
		_capacity = _capacity + value._size;
	}
	ValueType* tempCopy = new ValueType[_capacity];
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
	std::swap(_data, tempCopy);
	delete[] tempCopy;
	_size += value._size;
}

void MyVector::popBack()
{
	if (_size>0)
		_size--;
	if (loadFactor() <= (1.0 /( _coef*_coef))) {
		resize(_size);
	}
}

void MyVector::erase(const size_t i)
{
	if (_size == 0) {
		throw std::out_of_range("Size = 0");
	}
	else {
		for (size_t j = i; j < _size - 1; j++)
		{
			if (j + 1 < _size)
				_data[j] = _data[j + 1];
		}
		_size--;
		if (loadFactor() <= (1.0 / (_coef * _coef))) {
			resize(_size);
		}
	}
}

void MyVector::erase(const size_t i, const size_t len)
{
	if (i+len>_size) {
		throw std::out_of_range("Too many to erase");
	}
	else {
		for (size_t j = i; j < i + len; j++)
		{
			if (j + len < _size)
				_data[j] = _data[j + len];
		}
		_size -= len;
		if (loadFactor() <= (1.0 / (_coef * _coef))) {
			resize(_size);
		}
	}
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
	if (_data == nullptr) {
		_data = new ValueType[capacity];
	}
	else {
		memcpy(tmp_data, _data, _size * sizeof(ValueType));
		std::swap(_data, tmp_data);
		delete[] tmp_data;
		_capacity = capacity;
	}
}


void MyVector::resize(const size_t size, const ValueType value)
{
	if (size > _size)
	{
		if (size > _capacity)
		{
			reserve(size); 
		}
		for (size_t i = _size; i < size; i++)	
		{
			_data[i] = value;
		}
		_size = size;
		if (loadFactor() >= 1)
		{
			if (_strategy == ResizeStrategy::Multiplicative)
				reserve(ceil(_coef * _capacity));
			else if (_strategy == ResizeStrategy::Additive)
				reserve(ceil(_capacity + _coef));
		}
	}
	else if (size < _size)
	{
		ValueType* tempCopy = new ValueType[size];
		for (int i = 0; i < size; i++)
		{
			tempCopy[i] = _data[i];
		}
		std::swap(_data, tempCopy);
		delete[] tempCopy;
		_capacity = size;
		_size = size;
		if (loadFactor() >= 1)
		{
			if (_strategy == ResizeStrategy::Multiplicative)
				reserve(ceil(_coef * _capacity));
			else if (_strategy == ResizeStrategy::Additive)
				reserve(ceil(_capacity + _coef));
		}
	}
	else {
		if (_strategy == ResizeStrategy::Multiplicative)
			reserve(ceil(_coef * _size));
		else if (_strategy == ResizeStrategy::Additive)
			reserve(ceil(_size + _coef));	

	}
}

void MyVector::clear()
{
	for (size_t i = 0; i < _size; i++)
	{
		_data[i] = ValueType();
	} 
	_size = 0;
	resize(1);
}

MyVector MyVector::sortedSquares(const MyVector& vec, SortedStrategy strategy)
{
	MyVector sqr(vec);

	int right = vec._size - 1;
	int left = 0;
	int i;
	if (strategy == SortedStrategy::Decr) i = 0;
	else if (strategy == SortedStrategy::Incr) i = vec._size - 1;
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
			right--;
		}

	}
	sqr._data[i] = vec[left];

	return sqr;
}

int main() {
	int n = 10;
	int mas[] = { -5, -5, -4, 1, 1, 3, 3, 5, 10, 11 };
	MyVector vec;
	for (size_t i = 0; i < n; ++i) {
		vec.pushBack(mas[i]);
	}/*
	for (auto&& x : MyVector::sortedSquares(vec, SortedStrategy::Incr)) {
		std::cout << x << " ";
	}
	std::cout << std::endl;
	for (auto&& x : MyVector::sortedSquares(vec, SortedStrategy::Decr)) {
		std::cout << x << " ";
}*/
	vec.erase(2, 8);
	std::cout << vec[0] << " " << vec[1] << " " << vec.capacity() << " " << vec.size();
 	return 0;
}