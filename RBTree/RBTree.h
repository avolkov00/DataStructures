#pragma once

#include<iostream>

enum class Colour
{
	Red,
	Black
};

template <typename KeyType, typename ValueType>
class RBTree {
	struct Node {
		Node(const KeyType& key, const ValueType& value, Node* parent, Colour colour = Colour::Red);
		~Node();

		KeyType key;
		ValueType value;

		Node* parent;
		Node* left;
		Node* right;

		Colour colour;

		Node* uncle(Node* cur) const;
		Node* grandpa(Node* cur) const;
		Node* sibling(Node* cur) const;
	};	
public:
	//big five?
	RBTree();
	RBTree(const KeyType& key, const ValueType& value);

	RBTree(const RBTree& copyTree);
	RBTree& operator=(const RBTree& copyTree);

	~RBTree();

	void add(const KeyType& key, const ValueType& value);

	void deleteFirst(const KeyType& key, const ValueType& value);
	void deleteAll(const KeyType& key, const ValueType& value);

	ValueType findByKey(const KeyType& key);

	Node* findMaxKey();
	Node* findMinKey();

	size_t size(const RBTree& tree);

	bool isEmpty(const RBTree& tree);

private:
	void recursionCopy(Node* cur, Node* copy);

	void recursionDestruction(Node* cur);

	void balance(Node* cur);

	void first_add_case(Node* cur);
	void second_add_case(Node* cur);
	void third_add_case(Node* cur);
	void fourth_add_case(Node* cur);
	void fifth_add_case(Node* cur);

	void first_delete_case(Node* cur);
	void second_delete_case(Node* cur);
	void third_delete_case(Node* cur);
	void fourth_delete_case(Node* cur);
	void fifth_delete_case(Node* cur);
	void sixth_delete_case(Node* cur);

	Node* _head;
	size_t _size;
};

template<typename KeyType, typename ValueType>
RBTree<KeyType, ValueType>::Node::Node(const KeyType& key, const ValueType& value, Node* parent, Colour colour)
{
	this->key = key;
	this->value = value;
	
	this->parent = parent;
	this->left = nullptr;
	this->right = nullptr;

	this->colour = colour;
}

template<typename KeyType, typename ValueType>
RBTree<KeyType, ValueType>::RBTree()
{
	_head = nullptr;
	_size = 0;
}

template<typename KeyType, typename ValueType>
RBTree<KeyType, ValueType>::RBTree(const KeyType& key, const ValueType& value)
{
	_head = new Node(value, key, nullptr, Colour::Black);
	_size = 1;
}

template<typename KeyType, typename ValueType>
RBTree<KeyType, ValueType>::RBTree(const RBTree& copyTree)
{
	_size = copyTree._size;
	if (_size == 0)
	{
		_head = nullptr;
	}
	else {
		_head = new Node(copyTree._head->value, copyTree._head->key, nullptr, copyTree._head->color);
		recursionCopy(_head, copyTree._head);
	}
}

template<typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::recursionCopy(Node* cur, Node* copy)
{
	if (copy != nullptr) {
		cur.key = copy.key;
		cur.value = copy.value;

		cur.parent = copy.parent;
		cur.left = copy.left;
		cur.right = copy.right;

		cur.colour = copy.colour;
		recursionCopy(cur.left, copy.left);
		recursionCopy(cur.right, copy.right);
	}

}

template<typename KeyType, typename ValueType>
RBTree<KeyType, ValueType>& RBTree<KeyType, ValueType>::operator=(const RBTree& copyTree) {
	if (&this == &copy) {
		return;
	}
	else {
		_size = copyTree._size;
		if (_size == 0)
		{
			_head = nullptr;
		}
		else {
			_head = new Node(copyTree._head->value, copyTree._head->key, nullptr, copyTree._head->color);
			recursionCopy(_head, copyTree._head);
		}
	}
}
template<typename KeyType, typename ValueType>
RBTree<KeyType, ValueType>::~RBTree()
{
	if (_head != nullptr){
		recursionDestruction(_head);
	}
}

template<typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::recursionDestruction(Node* cur) {
	if (cur.left != nullptr) recursionDestruction(cur.left);
	if (cur.right != nullptr) recursionDestruction(cur.right);
	delete cur;
}
template<typename KeyType, typename ValueType>
RBTree<KeyType, ValueType>::Node::~Node()
{} 
template<typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::add(const KeyType& key, const ValueType& value) {
	if (_head == nullptr)
	{
		_head = new Node(value, key, nullptr, Color::Black);
		_size++;
		return;
	}
	else {
		Node* cur = _head;
		while (true) {
			if (key <= cur.key) {
				if (cur.left == nullptr) {
					cur.left = new Node(value, key, cur, Color::Red);
					_size++;
					balance(cur.left);
					return;
				}
				else {
					cur = cur.left;
				}
			}
			else {
				if (cur.right == nullptr) {
					cur.right = new Node(value, key, cur, Color::Red);
					_size++;
					balance(cur.right);
					return;
				}
				else {
					cur = cur.right;
				}
			}
		}
	}
}

template<typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::balance(Node* cur)
{
	first_add_case(cur);
}

template<typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::first_add_case(Node* cur)
{
	if (cur->parent == nullptr)	cur->color = Color::Black;
	else second_add_case(cur);
}

template<typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::second_add_case(Node* cur)
{
	if (cur->parent->color == Color::Red)	third_add_case(cur);
	else return;
}

template<typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::third_add_case(Node* cur)
{
	Node* u = cur->uncle(cur);
	if ((u != nullptr) && (u->color == Color::Red))
	{
		cur->parent->color = Color::Black;
		u->color = Color::Black;
		Node* g = cur->grandpa(cur);
		g->color = Color::Red;
		first_add_case(g);
	}
	else
	{
		fourth_add_case(cur);
	}
}

template<typename KeyType, typename ValueType>
typename RBTree<KeyType, ValueType>::Node* RBTree<KeyType, ValueType>::Node::uncle(Node* cur) const
{
	Node* g = grandpa(cur);
	if (!g)	return nullptr;
	if (cur->parent == g->right)	return g->left;
	else return g->right;
}

template<typename KeyType, typename ValueType>
typename RBTree<KeyType, ValueType>::Node* RBTree<KeyType, ValueType>::Node::grandpa(Node* cur) const
{
	if (!cur || !cur->parent)	return nullptr;
	return cur->parent->parent;
}

template<typename KeyType, typename ValueType>
typename RBTree<KeyType, ValueType>::Node* RBTree<KeyType, ValueType>::Node::sibling(Node* cur) const
{
	if (!cur || !cur->parent)	return nullptr;
	if (cur->parent->right == cur)	return cur->parent->left;
	else return cur->parent->right;
}

template<typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::fourth_add_case(Node* cur)
{
	Node* g = cur->grandpa(cur);
	Node* p = cur->parent;

	if ((cur == cur->parent->right) && (cur->parent == g->left))
	{
		left_rotate(cur->parent);
		cur = cur->left;
	}
	else if ((cur == cur->parent->left) && (cur->parent == g->right))
	{
		right_rotate(cur->parent);
		cur = cur->right;
	}
	fifth_add_case(cur);
}

template<typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::fifth_add_case(Node* cur)
{
	Node* g = g = cur->grandpa(cur);
	cur->parent->color = Color::Black;
	g->color = Color::Red;
	if ((cur == cur->parent->left) && (cur->parent == g->left))
	{
		right_rotate(g);
	}
	else if (cur == cur->parent->right && (cur->parent == g->right))
	{
		left_rotate(g);
	}
}


template<typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::right_rotate(Node* cur)
{
	Node* buf = cur->left;

	if (cur->parent == nullptr)
	{
		_head = buf;
		_head->left = buf->left;
		_head->right = buf->right;
	}
	buf->parent = cur->parent;
	if (buf->parent == _head) _head = buf->parent;
	if (cur->parent != nullptr) {
		if (cur->parent->left == cur)
			cur->parent->left = buf;
		else
			cur->parent->right = buf;
	}

	cur->left = buf->right;
	if (buf->right != nullptr)
		buf->right->parent = cur;

	cur->parent = buf;
	buf->right = cur;

}

template<typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::left_rotate(Node* cur)
{
	Node* buf = cur->right;
	if (cur->parent == nullptr)
	{
		_head = buf;
		_head->left = buf->left;
		_head->right = buf->right;
	}
	buf->parent = cur->parent;

	if (cur->parent != nullptr) {
		if (cur->parent->left == cur)
			cur->parent->left = buf;
		else
			cur->parent->right = buf;
	}

	cur->right = buf->left;
	if (buf->left != nullptr)
		buf->left->parent = cur;

	cur->parent = buf;
	buf->left = cur;

}
