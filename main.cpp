#include"AVLTree.h"

int main()
{
	//srand(time(0));
	Node* tree = nullptr;
	for (size_t i = 0; i < 15; i++)
	{
		tree = insert(tree, rand()%15);
	}
	printAwesomeTree(tree, 0);

	/*deleteNode(tree, 7);
	deleteNode(tree, 14);
	deleteNode(tree, 13);


	printAwesomeTree(tree, 0);*/

	return 0;
}