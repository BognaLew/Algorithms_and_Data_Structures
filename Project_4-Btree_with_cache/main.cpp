#include <iostream>
using namespace std;

struct node {
	bool isLeaf = true;
	int numberOfkeys = 0;
	int* keys;
	node** children;
};

struct BTree {
	node* root = nullptr;
	int t = 0;
};

bool checkIfKeyIsInNode(int key, node* n) {
	for (int i = 0; i < n->numberOfkeys; i++) {
		if (n->keys[i] == key) {
			return true;
		}
	}
	return false;
}

bool isKeyInTree(int key, BTree* tree) {
	node* tmp = tree->root;
	while (!tmp->isLeaf) {
		if (checkIfKeyIsInNode(key, tmp)) {
			return true;
		}

		int i = tmp->numberOfkeys - 1;
		while (i >= 0 && key < tmp->keys[i]) {
			i--;
		}
		tmp = tmp->children[i + 1];
	}
	
	if (checkIfKeyIsInNode(key, tmp)) {
		return true;
	}

	return false;
}

void printNode(node* n) {
	for (int i = 0; i < n->numberOfkeys; i++) {
		if (!n->isLeaf) {
			printNode(n->children[i]);
		}
		cout << n->keys[i] << " ";
	}
	if (!n->isLeaf) {
		printNode(n->children[n->numberOfkeys]);
	}
}

void splitNode(BTree* tree, node* nodeToSplit, node* parent, int number) {
	node* newNode = new node;
	newNode->isLeaf = nodeToSplit->isLeaf;
	newNode->keys = new int[2*tree->t - 1];
	newNode->children = new node * [2 * tree->t];
	newNode->numberOfkeys = tree->t - 1;
	nodeToSplit->numberOfkeys = tree->t - 1;
	for (int i = parent->numberOfkeys; i >= number; i--) {
		parent->keys[i] = parent->keys[i - 1];
	}
	for (int i = parent->numberOfkeys + 1; i > number; i--) {
		parent->children[i] = parent->children[i - 1];
	}
	parent->keys[number - 1] = nodeToSplit->keys[tree->t - 1];
	parent->children[number] = newNode;
	parent->numberOfkeys++;

	for (int i = 0; i < tree->t - 1; i++) {
		newNode->keys[i] = nodeToSplit->keys[i + tree->t];
	}

	for (int i = 0; i < tree->t; i++) {
		newNode->children[i] = nodeToSplit->children[i + tree->t];
	}
}

void insertValue(node* tmp, int key) {
	int i = tmp->numberOfkeys - 1;
	while (i >= 0 && key < tmp->keys[i]) {
		tmp->keys[i + 1] = tmp->keys[i];
		i--;
	}
	tmp->keys[i + 1] = key;
	tmp->numberOfkeys++;
}

node* chooseChild(node* n, int key) {
	int i = n->numberOfkeys - 1;
	while (i >= 0 && key < n->keys[i]) {
		i--;
	}
	return n->children[i + 1];
}

void insertNotFullRoot(int key, node* n, node* parent, BTree* tree) {
	if (n->numberOfkeys == 2 * tree->t - 1) {
		int number = 1;
		node* t = parent->children[number - 1];
		while (t != n) {
			number++;
			t = parent->children[number - 1];
		}
		splitNode(tree, n, parent, number);
		n = chooseChild(parent, key);
	}
	if (!n->isLeaf) {
		node* child = chooseChild(n, key);
		insertNotFullRoot(key, child, n, tree);
	}else {
		insertValue(n, key);
	}
	
}

void insertKey(int key, BTree* tree) {
	if (tree->root == nullptr) {
		tree->root = new node;
		tree->root->keys = new int[2*tree->t - 1];
		tree->root->children = new node*[2 * tree->t];
		tree->root->keys[0] = key;
		tree->root->numberOfkeys++;
	}else if(tree->root->numberOfkeys == 2*tree->t-1){
		node* newRoot = new node;
		newRoot->isLeaf = false;
		newRoot->children = new node * [2 * tree->t];
		newRoot->keys = new int[2 * tree->t - 1];
		newRoot->children[0] = tree->root;
		splitNode(tree, tree->root, newRoot, 1);
		tree->root = newRoot;
		node* child = chooseChild(newRoot, key);
		insertNotFullRoot(key, child, newRoot, tree);
	}else {
		if (tree->root->isLeaf) {
			insertValue(tree->root, key);
		}else {
			node* child = chooseChild(tree->root, key);
			insertNotFullRoot(key, child, tree->root, tree);
		}
	}
}

void saveNode(node* n) {
	cout << "( ";
	for (int i = 0; i < n->numberOfkeys; i++) {
		if (!n->isLeaf) {
			saveNode(n->children[i]);
		}
		cout << n->keys[i] << " ";
	}
	if (!n->isLeaf) {
		saveNode(n->children[n->numberOfkeys]);
	}
	cout << ") ";
}

void ster(BTree* tree) {
	char komenda;
	int key;
	while (true) {
		cin >> komenda;
		if (komenda == 'X') {
			return;
		}else if (komenda == 'A') {
			cin >> key;
			insertKey(key, tree);
		}else if (komenda == '?') {
			cin >> key;
			if (isKeyInTree(key, tree)) {
				cout << key << " +\n";
			}else {
				cout << key << " -\n";
			}
		}else if (komenda == '#') {
			cin.ignore();
		}else if (komenda == 'P') {
			printNode(tree->root);
			cout << endl;
		}else if (komenda == 'S') {
			cout << tree->t << endl;
			saveNode(tree->root);
			cout << endl;
		}
	}
}

void readNode(node* n, int t) {
	int key;
	while (true) {
		if (!(cin >> key)) {
			char znak;
			cin.clear();
			cin >> znak;
			cin.ignore(1);
			if (znak == '(') {
				node* newNode = new node;
				newNode->isLeaf = true;
				newNode->keys = new int[2 * t - 1];
				newNode->children = new node * [2 * t];
				readNode(newNode, t);
				n->isLeaf = false;
				n->children[n->numberOfkeys] = newNode;
			}else if (znak == ')') {
				return;
			}
		}else {
			n->keys[n->numberOfkeys] = key;
			n->numberOfkeys++;
		}
	}
}

int main() {
	char komenda;
	cin >> komenda;
	if (komenda == 'X') {
		return 0;
	}
	else if (komenda != 'I' && komenda != 'L') {
		while (komenda != 'I' && komenda != 'L') {
			cin >> komenda;
			if (komenda == 'X') {
				return 0;
			}
		}
	}
	
	BTree* tree = new BTree;
	int t;
	cin >> t;
	tree->t = t;

	if (komenda == 'L') {
		tree->root = new node;
		tree->root->keys = new int[2 * tree->t - 1];
		tree->root->children = new node * [2 * tree->t];
		char znak;
		cin >> znak;
		readNode(tree->root, tree->t);
	}

	ster(tree);

	delete tree->root;
	delete tree;

	return 0;
}