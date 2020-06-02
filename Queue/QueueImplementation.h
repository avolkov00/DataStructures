#pragma once
#include <cstdlib>

// приходится тянуть ValueType во все места,
// наглядная демонстрация того, почему с шаблонами было бы легче.
// Ждем, когда дойдете до этого на МиСП.
using ValueType = double;

// интерфейс для конкретных реализаций контейнера для стека
class QueueImplementation {
public:	
	// добавление в хвост
	virtual void enqueue(const ValueType& value) = 0;
	// удаление с хвоста
	virtual void dequeue() = 0;
	// посмотреть элемент в хвосте
	virtual const ValueType& front() const = 0;
	// проверка на пустоту
	virtual bool isEmpty() const = 0;
	// размер 
	virtual size_t size() const = 0;
	// виртуальный деструктор
	virtual ~QueueImplementation() {};
};
