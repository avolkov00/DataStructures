#include <iostream>
#include "RBTree.h"

int main()
{
	RBTree<int,int> a;
	RBTree<int, int> b(a);
	a.add(2, 22);
	a.add(1, 11);
	a.add(3, 33);
	a.add(4, 44);
	a.add(5, 55);
	a.deleteFirst(4);
	std::cout << a.findByKey(3);
	std::cout << a.size();
	std::cout << a.isEmpty();
	std::cout << a.findMinKey();



}
