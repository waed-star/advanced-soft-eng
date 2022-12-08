#include <iostream>
#include "Dictionary.h"

int main(int argc, char **argv) {
	Dictionary binaryTree = Dictionary();

	binaryTree.insert(22, "Jane");
	binaryTree.insert(22, "Mary");
	binaryTree.insert(0, "Harold");
	binaryTree.insert(9, "Edward");
	binaryTree.insert(37, "Victoria");
	binaryTree.insert(4, "Matilda");
	binaryTree.insert(26, "Oliver");
	binaryTree.insert(42, "Elizabeth");
	binaryTree.insert(19, "Henry");
	binaryTree.insert(4, "Stephen");
	binaryTree.insert(24, "James");
	binaryTree.insert(-1, "Edward");
	binaryTree.insert(31, "Anne");
	binaryTree.insert(23, "Elizabeth");
	binaryTree.insert(1, "William");
	binaryTree.insert(26, "Charles");

	binaryTree.displayEntries();

	std::cout << "----------------------------" << std::endl;
	std::cout << "------------ Copy ----------------" << std::endl;
	Dictionary copyBinaryTree = Dictionary(binaryTree);
	copyBinaryTree.displayEntries();
	copyBinaryTree.deleteNode(23);
	copyBinaryTree.deleteNode(24);
	copyBinaryTree.deleteNode(1);
	copyBinaryTree.deleteNode(-1);
	std::cout << "----------------------------" << std::endl;
	std::cout << "------------ Copy Tree after delete ----------------" << std::endl;
	copyBinaryTree.displayEntries();

	std::cout << "----------------------------" << std::endl;
	std::cout << "------------ Original tree after deleting nodes in copy tree ----------------" << std::endl;
	binaryTree.displayEntries();

	binaryTree.~Dictionary();

	std::cout << "----------------------------" << std::endl;
	std::cout << "------------ Copy tree after deleting original tree ----------------" << std::endl;
	copyBinaryTree.displayEntries();

	std::cout << "----------------------------" << std::endl;
	std::cout << "------------ Deleting original tree ----------------" << std::endl;
	binaryTree.lookup(22);

	return 0;
}
