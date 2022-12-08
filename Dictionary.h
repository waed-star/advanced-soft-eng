#include <iostream>
#include <string>

struct TreeNode {
	int key;
	std::string data;
	TreeNode* left;
	TreeNode* right;
	~TreeNode();
	TreeNode(const TreeNode &); // Copy Constructor
	TreeNode(int, std::string, TreeNode*, TreeNode*);
};

class Dictionary {
	private:
		TreeNode* root;
		void displayEntriesWorker(TreeNode*);
		void displayTreeWorker(TreeNode*, std::string);
		bool lookupWorker(int, TreeNode*);
		void insertWorker(int, std::string, TreeNode*);
		TreeNode* minValueNode(TreeNode*);
		TreeNode* deleteNodeWorker(TreeNode*, int);
		void rotateLeft(TreeNode**);
		void rotateRight(TreeNode**);
		void rotateLeftWorker(TreeNode**, int);
		void rotateRightWorker(TreeNode**, int);

	public:
		Dictionary();
		~Dictionary();
		Dictionary(const Dictionary &); // Copy Constructor
		const Dictionary & operator=(const Dictionary &); // Copy assignment operator
		Dictionary(Dictionary &&); // Move Constructor
		Dictionary & operator=(Dictionary &&);  // Move assignment operator
		void deepDeleteWorker(TreeNode*);
		void insert(int, std::string);
		void displayEntries();
		void displayTree();
		bool lookup(int);
		void deleteNode(int);
		void rotateLeftOn(int);
		void rotateRightOn(int);
};
