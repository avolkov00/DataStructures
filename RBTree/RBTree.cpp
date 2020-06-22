#include <iostream>
#include "RBTree.h"

int main()
{
	RBTree<int,int> a;
	for (int i = 1; i < 16; i++) {
		a.add(5, 100 * i);
	}
	for (int i = 20; i < 26; i++) {
		a.add(6, 100 * i);
	}
	a.deleteAll(5);
	a.deleteAll(6);
	std::cout << a.size();
}
