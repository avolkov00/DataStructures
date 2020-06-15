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
	};	
public:
	//big five?
	RBTree();
	RBTree(const KeyType& key, const ValueType& value);

	RBTree(const RBTree& copyTree);
	RBTree& operator=(const RBTree& copyTree);

	~RBTree();

	void add(const KeyType& key, const ValueType& value);

	void deleteFirst(const KeyType& key);
	void deleteAll(const KeyType& key);

	ValueType findByKey(const KeyType& key);

	Node* findMaxKey();
	Node* findMinKey();

	size_t size(const RBTree& tree);

	bool isEmpty(const RBTree& tree);

	Node* uncle(Node* cur) const;
	Node* grandpa(Node* cur) const;
	Node* sibling(Node* cur) const;

private:
	void recursionCopy(Node* cur, Node* copy);

	void recursionDestruction(Node* cur);

	void balance(Node* cur);

	void recursionDelete(const KeyType& key,Node* cur);

	void deleteNode(Node* cur);

	void balanceDelete(Node* cur);

	bool recursionInTree(const KeyType& key, Node* cur);

	ValueType recursionFind(const KeyType& key, Node* cur);

	void right_rotate(Node* cur);
	void left_rotate(Node* cur);

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
	_head = new Node(key, value, nullptr, Colour::Black);
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
		_head = new Node(copyTree._head->key, copyTree._head->value, nullptr, copyTree._head->colour);
		recursionCopy(_head, copyTree._head);
	}
}

template<typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::recursionCopy(Node* cur, Node* copy)
{
	if (copy != nullptr) {
		cur->key = copy->key;
		cur->value = copy->value;

		cur->parent = copy->parent;
		cur->left = copy->left;
		cur->right = copy->right;

		cur->colour = copy->colour;
		recursionCopy(cur->left, copy->left);
		recursionCopy(cur->right, copy->right);
	}

}

template<typename KeyType, typename ValueType>
RBTree<KeyType, ValueType>& RBTree<KeyType, ValueType>::operator=(const RBTree& copyTree) {
	if (&this == &copyTree) {
		return;
	}
	else {
		_size = copyTree._size;
		if (_size == 0)
		{
			_head = nullptr;
		}
		else {
			_head = new Node(copyTree._head->key, copyTree._head->value, nullptr, copyTree._head->colour);
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
	if (cur->left != nullptr) recursionDestruction(cur->left);
	if (cur->right != nullptr) recursionDestruction(cur->right);
	delete cur;
}
template<typename KeyType, typename ValueType>
RBTree<KeyType, ValueType>::Node::~Node()
{} 
template<typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::add(const KeyType& key, const ValueType& value) {
	if (_head == nullptr)
	{
		_head = new Node(key, value, nullptr, Colour::Black);
		_size++;
		return;
	}
	else {
		Node* cur = _head;
		while (true) {
			if (key <= cur->key) {
				if (cur->left == nullptr) {
					cur->left = new Node(key, value, cur, Colour::Red);
					_size++;
					balance(cur->left);
					return;
				}
				else {
					cur = cur->left;
				}
			}
			else {
				if (cur->right == nullptr) {
					cur->right = new Node(key, value, cur, Colour::Red);
					_size++;
					balance(cur->right);
					return;
				}
				else {
					cur = cur->right;
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
	if (cur->parent == nullptr)	cur->colour = Colour::Black;
	else second_add_case(cur);
}

template<typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::second_add_case(Node* cur)
{
	if (cur->parent->colour == Colour::Red)	third_add_case(cur);
	else return;
}

template<typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::third_add_case(Node* cur)
{
	Node* u = uncle(cur);
	if ((u != nullptr) && (u->colour == Colour::Red))
	{
		cur->parent->colour = Colour::Black;
		u->colour = Colour::Black;
		Node* g = grandpa(cur);
		g->colour = Colour::Red;
		first_add_case(g);
	}
	else fourth_add_case(cur);
}

template<typename KeyType, typename ValueType>
typename RBTree<KeyType, ValueType>::Node* RBTree<KeyType, ValueType>::uncle(Node* cur) const
{
	Node* g = grandpa(cur);
	if (!g)	return nullptr;
	if (cur->parent == g->right)	return g->left;
	else return g->right;
}

template<typename KeyType, typename ValueType>
typename RBTree<KeyType, ValueType>::Node* RBTree<KeyType, ValueType>::grandpa(Node* cur) const
{
	if (!cur || !cur->parent)	return nullptr;
	return cur->parent->parent;
}

template<typename KeyType, typename ValueType>
typename RBTree<KeyType, ValueType>::Node* RBTree<KeyType, ValueType>::sibling(Node* cur) const
{
	if (!cur || !cur->parent)	return nullptr;
	if (cur->parent->right == cur)	return cur->parent->left;
	else return cur->parent->right;
}

template<typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::fourth_add_case(Node* cur)
{
	Node* g = grandpa(cur);
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
	Node* g = g = grandpa(cur);
	cur->parent->colour = Colour::Black;
	g->colour = Colour::Red;
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

	
	buf->parent = cur->parent;
	if (buf->parent == nullptr) {
		_head = buf;
	}
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

	buf->parent = cur->parent;
	if (buf->parent == nullptr)
	{
		_head = buf;
	}

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

template<typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::deleteFirst(const KeyType& key) {
	recursionDelete(key, _head);
	_size--;
}
template<typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::recursionDelete(const KeyType& key,Node* cur) {
	if (cur == nullptr) return;
	if (key > cur->key)	recursionDelete(key, cur->right);
	if (key < cur->key) recursionDelete(key, cur->left);
	if (key == cur->key) deleteNode(cur);
}

template<typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::deleteNode(Node* cur) {
	if (cur->left == nullptr && cur->right == nullptr)
	{

		balanceDelete(cur);
		if (cur->parent->left == cur) cur->parent->left = nullptr;
		else cur->parent->right = nullptr;
		delete cur;
		return;
	}
	else if (cur->left == nullptr)
	{
		Node* right = cur->right;

		cur->key = right->key;
		cur->value = right->value;

		cur->left = right->left;
		cur->right = right->right;

		balanceDelete(right);

		delete right;
	}
	else if (cur->right == nullptr)
	{
		Node* left = cur->left;

		cur->key = left->key;
		cur->value = left->value;

		cur->left = left->left;
		cur->right = left->right;

		balanceDelete(left);

		delete left;
	}
	else {
		Node* n = cur;
		if (n->right->left == nullptr)
		{
			n->key = n->right->key;
			n->value = n->right->value;

			Node* buf = n->right->right;

			balanceDelete(n->right);

			delete n->right;

			n->right = buf;

			return;
		}
		else
		{
			Node* l = n->right;
			while (l->left != nullptr)
			{
				l = l->left;
			}

			n->key = l->key;
			n->value = l->value;

			deleteNode(l);
		}
	}
}

template<typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::balanceDelete(Node* cur)
{
	if (cur->colour == Colour::Black)
	{
		first_delete_case(cur);
	}
}

template<typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::first_delete_case(Node* cur)
{
	if (cur->parent != nullptr)
	{
		second_delete_case(cur);
	}
}

template<typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::second_delete_case(Node* cur)
{
	Node* s = this->sibling(cur);
	Node* parent = cur->parent;
	if (s->colour == Colour::Red)
	{
		parent->colour = Colour::Red;
		s->colour = Colour::Black;
		if (parent->left == cur) left_rotate(cur->parent);
		else right_rotate(cur->parent);
	}
	third_delete_case(cur);
}

template<typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::third_delete_case(Node* cur)
{
	Node* s = this->sibling(cur);

	if ((cur->parent->colour == Colour::Black) && (s->colour == Colour::Black) && (!s->left || s->left->colour == Colour::Black) && (!s->right || s->right->colour == Colour::Black))
	{
		s->colour = Colour::Red;
		first_delete_case(cur->parent);
	}
	else
	{
		fourth_delete_case(cur);
	}
}

template<typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::fourth_delete_case(Node* cur)
{
	Node* s = this->sibling(cur);
	if (cur->parent->colour == Colour::Red && s->colour == Colour::Black && (!s->left || s->left->colour == Colour::Black) && (!s->right || s->right->colour == Colour::Black))
	{
		s->colour = Colour::Red;
		cur->parent->colour = Colour::Black;
	}
	else 
	{
		fifth_delete_case(cur);
	}
}

template<typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::fifth_delete_case(Node* cur)
{
	Node* s = this->sibling(cur);
	if (s->colour == Colour::Black)
	{
		if (cur->parent->left == cur && (!s->left || s->left->colour == Colour::Red) && (!s->right || s->right->colour == Colour::Black))
		{
			s->colour = Colour::Red;
			s->left->colour = Colour::Black;
			right_rotate(s);
		}
		else if (cur->parent->right == cur && (!s->left || s->left->colour == Colour::Black) && (!s->right || s->right->colour == Colour::Red))
		{
			s->colour = Colour::Red;
			s->right->colour = Colour::Black;
			left_rotate(s);
		}

	}
	sixth_delete_case(cur);
}

template<typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::sixth_delete_case(Node* cur)
{
	Node* s = sibling(cur);
	s->colour = cur->parent->colour;
	cur->parent->colour = Colour::Black;
	if (cur->parent->left == cur)
	{
		s->right->colour = Colour::Black;
		left_rotate(cur->parent);
	}
	else
	{
		s->left->colour = Colour::Black;
		right_rotate(cur->parent);
	}
}

template<typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::deleteAll(const KeyType& key) 
{
	while (recursionInTree(key, _head))
	{
		deleteFirst(key, _head);
		_size--;
	}
}

template<typename KeyType, typename ValueType>
bool RBTree<KeyType, ValueType>::recursionInTree(const KeyType& key, Node* cur)
{
	if (cur == nullptr) return false;
	else if (key == cur->key) return true;
	else if (key < cur->key) return recursionInTree(key, cur->left);
	else if (key >= cur->key) return recursionInTree(key, cur->right);
}

template<typename KeyType, typename ValueType>
ValueType RBTree<KeyType, ValueType>::findByKey(const KeyType& key) {
	return recursionFind(key, _head);
}
template<typename KeyType, typename ValueType>
ValueType RBTree<KeyType, ValueType>::recursionFind(const KeyType& key, Node* cur) {
	if (cur == nullptr) throw std::out_of_range("No such key");
	else if (key == cur->key) return cur->value;
	else if (key < cur->key)  recursionFind(key, cur->left);
	else if (key >= cur->key)  recursionFind(key, cur->right);
}

template<typename KeyType, typename ValueType>
typename RBTree<KeyType, ValueType>::Node* RBTree<KeyType, ValueType>::findMaxKey() {
	Node* buf = _head;
	while (buf->right) buf = buf->right;
	return buf;
}

template<typename KeyType, typename ValueType>
typename RBTree<KeyType, ValueType>::Node* RBTree<KeyType, ValueType>::findMinKey() {
	Node* buf = _head;
	while (buf->left) buf = buf->left;
	return buf;
}

template<typename KeyType, typename ValueType>
size_t RBTree<KeyType, ValueType>::size(const RBTree& tree) {
	return tree._size;
}

template<typename KeyType, typename ValueType>
bool RBTree<KeyType, ValueType>::isEmpty(const RBTree& tree) {
	if (tree._size == 0) return true;
	else return false;
}
