#pragma once
#include "StackImplementation.h"
#include "MyVector.h"
#include "MyVector.cpp"

// вариант с использованием ранее написанного вектора и множественного наследования
// если бы вектор не был реализован, то было бы наследование только от интерфейса
// множественное наследование можно заменить на композицию
class VectorStack : public StackImplementation, public MyVector
{
	VectorStack() {};
	// добавление в хвост
	void push(const ValueType& value);
	// удаление с хвоста
	void pop();
	// посмотреть элемент в хвосте
	ValueType& top();
	const ValueType& top() const;
	// проверка на пустоту
	bool isEmpty() const;
	// размер 
	size_t size() const;
	// виртуальный деструктор
	~VectorStack() override {};
};

