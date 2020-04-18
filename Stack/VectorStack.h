#pragma once
#include "StackImplementation.h"
#include "MyVector.h"
#include "MyVector.cpp"

// вариант с использованием ранее написанного вектора и множественного наследования
// если бы вектор не был реализован, то было бы наследование только от интерфейса
// множественное наследование можно заменить на композицию
class VectorStack : public StackImplementation, public MyVector
{
	// вот тут вы вступаете в дело
};

