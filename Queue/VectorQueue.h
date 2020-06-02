#pragma once
#include "QueueImplementation.h"
#include "MyVector.h"
#include <cstdlib>

// вариант с использованием ранее написанного вектора и множественного наследования
// если бы вектор не был реализован, то было бы наследование только от интерфейса
// множественное наследование можно заменить на композицию
class VectorQueue : public QueueImplementation, public MyVector
{
public:
	VectorQueue() : _headIndex(0) {};
	VectorQueue(VectorQueue& que) : _headIndex(que._headIndex),MyVector(que) {};

	// добавление в хвост
	void enqueue(const ValueType& value);
	// удаление с хвоста
	void dequeue();
	// посмотреть элемент в хвосте
	const ValueType& front() const;
	// проверка на пустоту
	bool isEmpty() const;
	// размер 
	size_t size() const;
	// виртуальный деструктор
	~VectorQueue() override {};
private:
	size_t _headIndex;
};

