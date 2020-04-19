#pragma once
#include <cstddef>

// ����� �������� �� �������
using ValueType = double;

class DoubleLinkedList
{
	struct Node {
		Node(const ValueType& value, Node* prev = nullptr, Node* next = nullptr);
		~Node();

		void insertNext(const ValueType& value);
		void removeNext();

		ValueType value;
		Node *prev, *next;
	};

public:
	////
	DoubleLinkedList();
	DoubleLinkedList(const DoubleLinkedList& copyList);
	DoubleLinkedList& operator=(const DoubleLinkedList& copyList);

	DoubleLinkedList(DoubleLinkedList&& moveList) noexcept;
	DoubleLinkedList& operator=(DoubleLinkedList&& moveList) noexcept;

	~DoubleLinkedList();
	////

	// ������ � �������� �������� �� �������
	ValueType& operator[](const size_t pos) const;
	// ������ � ���� �� �������
	DoubleLinkedList::Node* getNode(const size_t pos) const;

	// ������� �������� �� �������, ������� ����, ���� ��������� (�(n)), ����� ��������� (O(1))
	void insert(const size_t pos, const ValueType& value);
	// ������� �������� ����� ����, (O(1))
	void insertAfterNode(Node* node, const ValueType& value);
	// ������� � ����� (�(n))
	void pushBack(const ValueType& value);
	// ������� � ������ (�(1))
	void pushFront(const ValueType& value);

	// ��������
	void removeFront();
	void removeBack();
	void remove(const size_t pos);
	void removeNextNode(Node* node);

	// �����, �(n)
	long long int findIndex(const ValueType& value) const;
	Node* findNode(const ValueType& value) const;

	// �������� ������
	void reverse();					// ��������� �������� ������
	DoubleLinkedList reverse() const;		// �������� ������ ������ (��� ����������� ��������)
	DoubleLinkedList getReverseList() const;	// ����� ������������� ������ ���� ��� ���������� ����� ����������� ������

	size_t size() const;
private:
	Node* _head;
	Node* _tail;
	size_t	_size;

	void forceNodeDelete(Node* node);
};

