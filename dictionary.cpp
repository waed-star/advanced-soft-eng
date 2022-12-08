#include "Dictionary.h"
#include <string>

TreeNode::TreeNode(int k, std::string d, TreeNode* lft = nullptr, TreeNode* rht = nullptr) {
	key = k;
	data = d;
	left = lft;
	right = rht;
}

TreeNode::TreeNode(const TreeNode &n)  {
	key = n.key;
	data = n.data;

	left = n.left != nullptr ? new TreeNode(*n.left) : nullptr;
	right = n.right != nullptr ? new TreeNode(*n.right) : nullptr;
}

TreeNode::~TreeNode() {
  delete left;  // recursively call destructor on left subtree node
  delete right;  // recursively call destructor on right subtree node
  // Note that when left or right is nullptr, delete will do nothing, so that
  // the recursion will be stopped.
}

Dictionary::Dictionary() {
	root = nullptr;
}

Dictionary::Dictionary(const Dictionary &dictToCopy)
    : root(new TreeNode(*dictToCopy.root)) {}

Dictionary::~Dictionary() {
  delete root;
}

Dictionary::Dictionary(Dictionary && dictToMove) {
	root = dictToMove.root;
	dictToMove.root = nullptr;
}

const Dictionary & Dictionary::operator=(const Dictionary & dictToCopy)
{
     if(this != &dictToCopy)
     {
    	  deepDeleteWorker(root);
          root = nullptr;
          TreeNode(*dictToCopy.root);
     }
     return *this;
}

Dictionary& Dictionary::operator=(Dictionary&& dictToCopy) {
    if (this != &dictToCopy) {
    	deepDeleteWorker(root);
        root = dictToCopy.root;
        dictToCopy.root = nullptr;
    }

    return *this;
}

void Dictionary::deepDeleteWorker(TreeNode* curr) {
	if (curr == nullptr)
		return;

	deepDeleteWorker(curr->left);
	deepDeleteWorker(curr->right);

	delete curr;
}


void Dictionary::insert(int k, std::string d) {
	Dictionary::insertWorker(k, d, root);
}

void Dictionary::insertWorker(int k, std::string d, TreeNode* curr) {
	if (root == nullptr) {
		root = new TreeNode(k, d);
		return;
	}


	if(curr->key == k) {
		curr->data = d;
		return;
	}

	if (k < curr->key) {
		if (curr->left == nullptr) {
			curr->left = new TreeNode(k, d);
			return;
		}
		else {
			insertWorker(k, d, curr->left);
		}
	} else {
		if (curr->right == nullptr) {
			curr->right = new TreeNode(k, d);
			return;
		}
		else {
			insertWorker(k, d, curr->right);
		}
	}

	return;
}


bool Dictionary::lookup(int k) {
	return Dictionary::lookupWorker(k, root);
}

bool Dictionary::lookupWorker(int k, TreeNode* curr) {
	// Base case
	if (root == nullptr) return false;


	if(curr->key == k) {
		return true;
	}
	else if (k < curr->key) {
		return lookupWorker(k, curr->left);
	}
	else {
		return lookupWorker(k, curr->right);
	}

	return false;
}

void Dictionary::displayEntries() {
	// (1) call the worker function on the root pointer here
	Dictionary::displayEntriesWorker(root);
}

void Dictionary::displayEntriesWorker(TreeNode* currentNode) {
	if (currentNode == nullptr) return;

	// (A) code for visiting a node during a pre-order traversal goes here

	// (2) recursively call the worker function on the left child pointer here
	Dictionary::displayEntriesWorker(currentNode->left);

	// (B) code for visiting a node during an in-order traversal goes here
	std::cout << currentNode->key << " " << currentNode->data << std::endl;

	// (3) recursively call the worker function on the right child pointer here
	Dictionary::displayEntriesWorker(currentNode->right);

	// (C) code for visiting a node during a post-order traversal goes here
}

void Dictionary::displayTree() {
	Dictionary::displayTreeWorker(root, "	");
}

void Dictionary::displayTreeWorker(TreeNode* n, std::string indent) {
	if (n == nullptr) return;

	std::cout << indent << n->key << " " << n->data << std::endl;
	Dictionary::displayTreeWorker(n->left, indent + "	");
	Dictionary::displayTreeWorker(n->right, indent + "	");
}

TreeNode* Dictionary::minValueNode(TreeNode* root) {
	TreeNode* p = root;
	while (p != nullptr && p->left != nullptr) {
		p = p->left;
	}
	return p;
}


TreeNode* Dictionary::deleteNodeWorker(TreeNode* root, int k) {
	TreeNode* p = root;
	if (p == nullptr)
		return p;

	if (k < p->key) {
		p->left = Dictionary::deleteNodeWorker(p->left, k);
	}
	else if (k > p->key) {
		p->right = Dictionary::deleteNodeWorker(p->right, k);
	}
	else {
		if (p->left == nullptr and p->right == nullptr) {
			delete p;
			p = nullptr;
		}
		else if (p->left == nullptr) {
			TreeNode* t = p->right;
			delete p;
			p = t;
		}
		else if (p->right == nullptr) {
			TreeNode* t = p->left;
			delete p;
			p = t;
		}
		else {
			TreeNode* in = Dictionary::minValueNode(p->right);

			p->key = in->key;
			p->data = in->data;
			p->right = Dictionary::deleteNodeWorker(p->right, in->key);
		}
	}
	return p;
}

void Dictionary::deleteNode(int k) {
	root = Dictionary::deleteNodeWorker(root, k);
}


void Dictionary::rotateRight (TreeNode **root) {

	TreeNode *p = *root;

	if (p == nullptr)
		return;
	if (p->left == nullptr)
		return;

	TreeNode *pA = p->left;

	*root = pA;
	p->left = pA->right;
	pA->right = p;
}

void Dictionary::rotateRightWorker(TreeNode **root, int k) {

	TreeNode* p = *root;
	if (p == nullptr)
		return;

	if (k < p->key) {
		rotateRightWorker(&(p->left), k);
	}
	else if (k > p->key) {
		rotateRightWorker(&(p->right), k);
	}
	else {
		rotateRight(root);
	}
}

void Dictionary::rotateRightOn (int k) {
	rotateRightWorker(&root, k);
}

void Dictionary::rotateLeft (TreeNode **root) {

	TreeNode *p = *root;

	if (p == nullptr)
		return;

	if (p->right == nullptr)
		return;

	TreeNode *pB = p->right;

	*root = pB;
	pB->left = p;
	p->right = pB->right;
}

void Dictionary::rotateLeftWorker (TreeNode **root, int k) {

	TreeNode* p = *root;
	if (p == nullptr)
		return;

	if (k < p->key) {
		rotateLeftWorker(&p->left, k);
	}
	else if (k > p->key) {
		rotateLeftWorker(&p->right, k);
	}
	else {
		rotateLeft(root);
	}
}

void Dictionary::rotateLeftOn (int k) {
	rotateLeftWorker(&root, k);
}
