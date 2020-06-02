#pragma once

#include "QueueImplementation.h"
#include "LinkedList.h"
#include <cstdlib>

// вариант с использованием ранее написанного списка и множественного наследования
// если бы список не был реализован, то было бы наследование только от интерфейса
// множественное наследование можно заменить на композицию
class ListQueue : public QueueImplementation, public SinglyLinkedList
{
public:
	ListQueue() {};
	ListQueue(ListQueue& que) : SinglyLinkedList(que) {};
	// добавление в хвост
	void enqueue(const ValueType& value);
	// удаление с хвоста
	void dequeue();
	// посмотреть элемент в хвосте
	const ValueType& front() const;
	// проверка на пустоту
	bool isEmpty() const ;
	// размер 
	size_t size() const ;
	// виртуальный деструктор
	~ListQueue() override {};
};

