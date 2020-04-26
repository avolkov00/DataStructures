#include "../LinkedList/DoubleLinkedList.h"

#include <cassert>
#include <stdexcept>

DoubleLinkedList::Node::Node(const ValueType& value, Node* prev, Node* next) 
	:value(value), prev(prev), next(next) {};

DoubleLinkedList::Node::~Node()
{
	// ничего не удаляем, т.к. агрегация
}

void DoubleLinkedList::Node::insertNext(const ValueType& value)
{
	Node* newNode = new Node(value, this, this->next);
	this->next = newNode;
}

void DoubleLinkedList::Node::removeNext()
{
	Node* removeNode = this->next;
	Node* newNext = removeNode->next;
	delete removeNode;
	this->next = newNext;
	newNext->prev = this;
}

DoubleLinkedList::DoubleLinkedList()
	: _head(nullptr), _tail(nullptr), _size(0) 
{}

DoubleLinkedList::DoubleLinkedList(const DoubleLinkedList& copyList)
{
	_size = copyList._size;
	if (_size == 0) {
		_head = nullptr;
		_tail = nullptr;
		return;
	}

	_head = new Node(copyList._head->value);

	Node* curentNode = _head;
	Node* curentCopyNode = copyList._head;

	while (curentCopyNode->next) {
		curentCopyNode = curentCopyNode->next;
		curentNode->next = new Node(curentCopyNode->value, curentNode);
		curentNode = curentNode->next;
	}
	_tail = curentNode;
}

DoubleLinkedList& DoubleLinkedList::operator=(const DoubleLinkedList& copyList)
{
	if (this == &copyList) {
		return *this;
	}
	DoubleLinkedList* bufList = new DoubleLinkedList(copyList);
	forceNodeDelete(_head);

	this->_size = bufList->_size;
	this->_head = bufList->_head;
	this->_tail = bufList->_tail;

	return *this;
}


DoubleLinkedList::DoubleLinkedList(DoubleLinkedList&& moveList) noexcept
{
	this->_size = moveList._size;
	this->_tail = moveList._tail;
	this->_head = moveList._head;

	moveList._size = 0;
	moveList._tail = nullptr;
	moveList._head = nullptr;
}

DoubleLinkedList& DoubleLinkedList::operator=(DoubleLinkedList&& moveList) noexcept
{
	if (this == &moveList) {
		return *this;
	}

	forceNodeDelete(_head);

	this->_size = moveList._size;
	this->_tail = moveList._tail;
	this->_head = moveList._head;

	moveList._size = 0;
	moveList._tail = nullptr;
	moveList._head = nullptr;

	return *this;
}

DoubleLinkedList::~DoubleLinkedList()
{
	forceNodeDelete(_head);
}

ValueType& DoubleLinkedList::operator[](const size_t pos) const
{
	return getNode(pos)->value;
}

DoubleLinkedList::Node* DoubleLinkedList::getNode(const size_t pos) const
{
	if (pos < 0) {
		assert(pos < 0);
	}
	else if (pos >= this->_size) {
		assert(pos >= this->_size);
	}

	size_t halfSize = _size / 2;
	Node* bufNode;

	if (pos < halfSize) {
		bufNode = _head;
		for (int i = 0; i < pos; i++)
			bufNode = bufNode->next;
	}
	else {
		bufNode = _tail;
		for (int i = _size - 1; i > pos; i--)
			bufNode = bufNode->prev;
	}

	return bufNode;
}

void DoubleLinkedList::insert(const size_t pos, const ValueType& value)
{
	if (pos < 0) {
		assert(pos < 0);
	}
	else if (pos > this->_size) {
		assert(pos > this->_size);
	}

	if (pos == 0)
		pushFront(value);

	Node* bufNode = getNode(pos - 1);
	bufNode->insertNext(value);
	++_size;

}

void DoubleLinkedList::insertAfterNode(Node* node, const ValueType& value)
{
	node->insertNext(value);
	++_size;
}

void DoubleLinkedList::pushBack(const ValueType& value)
{
	Node* newNode = new Node(value, _tail);
	if (_tail != nullptr) {
		_tail->next = newNode;
	}
	else if (_head == nullptr) {
		_head = newNode;
	}
	_tail = newNode;
	++_size;
}

void DoubleLinkedList::pushFront(const ValueType& value)
{
	Node* newNode = new Node(value, nullptr, _head);
	if (_head != nullptr) {
		_head->prev = newNode;
	}
	else if (_tail == nullptr) {
		_tail = newNode;
	}
	_head = newNode;
	++_size;
}

void DoubleLinkedList::remove(const size_t pos)
{
	if (pos == 0) {
		removeFront();
	}
	else if (pos == _size - 1) {
		removeBack();
	}
	else
	{
		Node* temp = getNode(pos - 1);

		Node* newNode = temp->next;
		temp->next = temp->next->next;
		delete newNode;
		--_size;
	}
}

void DoubleLinkedList::removeNextNode(Node* node)
{
	Node* curentDeleteNode = node->next;
	Node* curentNode = curentDeleteNode->next;
	node->next = curentNode;
	curentNode->prev = node;

	delete curentDeleteNode;
	--_size;
}

void DoubleLinkedList::removeBack()
{
	if (_tail == nullptr)
		return;

	Node* temp = _tail;
	_tail = _tail->prev;
	delete temp;
	--_size;
}

void DoubleLinkedList::removeFront()
{
	if (_head == nullptr)
		return;

	Node* temp = _head;
	_head = _head->next;
	delete temp;
	--_size;
}

long long int DoubleLinkedList::findIndex(const ValueType& value) const
{
	Node* curentNode = _head;
	for (int i = 0; i < _size; ++i) {
		if (curentNode->value == value)
			return i;

		curentNode = curentNode->next;
	}
	return -1;
}

DoubleLinkedList::Node* DoubleLinkedList::findNode(const ValueType& value) const
{
	Node* curentNode = _head;
	for (int i = 0; i < _size; ++i) {
		if (curentNode->value == value)
			return curentNode;

		curentNode = curentNode->next;
	}
	return nullptr;
}

void DoubleLinkedList::reverse()
{
	Node* temp = _head;
	_head = _tail;
	_tail = temp;

	Node* cur = _head;
	while (cur != nullptr) {
		temp = cur->next;
		cur->next = cur->prev;
		cur->prev = temp;
		cur = cur->next;
	}
}

DoubleLinkedList DoubleLinkedList::reverse() const
{
	return getReverseList();
}

DoubleLinkedList DoubleLinkedList::getReverseList() const
{
	DoubleLinkedList list(*this);
	Node* temp = list._head;
	list._head = list._tail;
	list._tail = temp;

	Node* cur = list._head;
	while (cur != nullptr) {
		temp = cur->next;
		cur->next = cur->prev;
		cur->prev = temp;
		cur = cur->next;
	}

	return list;
}

size_t DoubleLinkedList::size() const
{
	return _size;
}

void DoubleLinkedList::forceNodeDelete(Node* node)
{
	if (node == nullptr) {
		return;
	}

	Node* nextDeleteNode = node->next;
	delete node;
	forceNodeDelete(nextDeleteNode);
}