#include <iostream>
#include "AVLTree.h"

using namespace std;

int main() {
	AVLTree<int> avlt;

	avlt.AVLTInsert(3);
	avlt.AVLTInsert(1);
	avlt.AVLTInsert(2);
	avlt.AVLTInsert(4);
	avlt.AVLTInsert(5);
	avlt.AVLTInsert(6);

	avlt.AVLTRemove(1);
	avlt.AVLTRemove(2);
	avlt.AVLTRemove(3);

	cout << avlt.AVLTSearch(5)->GetData();

	return 0;
}
