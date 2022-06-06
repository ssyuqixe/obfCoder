#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

struct node_bst {
	node_bst* parent;
	node_bst* left;
	node_bst* right;
	double key;
	size_t index;
};

class bst {
private:
	size_t counter;

public:
	node_bst* root;
	bst() 
	{
		root = nullptr; 
		counter = 0;
	};

	void Add(double key);
	node_bst* Search(double key);
	void Delete(node_bst*& node);
	void preorder(node_bst*& node);
	node_bst* find_min(node_bst* node);
	void DeleteAll();


};



int main()
{
	std::ifstream in("tree.txt");
	bst* tree = new bst();

	double a = 0;
	if (in.is_open()) {
		bool firstLine = true;
		std::string item;
		while (in >> a)
		{
			tree->Add(a);
		}
		in.close();
	}
	else {
		std::cout << "Nie mozna otworzyc pliku" << std::endl;
		return 0;
	}

	tree->preorder(tree->root);
	tree->DeleteAll();

	return 0;
}

void bst::Add(double key) {
	node_bst* previous = nullptr;
	node_bst* p = root;
	while (p) {
		if (p->key == key) return;
		previous = p;
		(p->key < key) ? p = p->right : p = p->left;
	}
	node_bst* new_node = new node_bst();
	new_node->key = key;
	new_node->left = nullptr;
	new_node->right = nullptr;
	new_node->index = counter++;
	if (!previous) {
		root = new_node;
		return;
	}
	(previous->key < key) ? previous->right = new_node : previous->left = new_node;
	new_node->parent = previous;


}

node_bst* bst::Search(double key)
{
	bool found = false;
	node_bst* p = root;

	while ((p) && !found)
	{
		if (p->key == key)
		{
			found = true;
		}
		else if (p->key < key) 
	
		{
			p = p->right;
		}
		else 
		{
			p = p->left;
		}
	}

	return p;
}

void bst::Delete(node_bst*& node)
{
	if (!node) return;
	node_bst* temp = node;


	if (node->parent && (node->left || node->right)) {

		if (!node->left) {

			node->right->parent = node->parent;
			if (node->parent->left == node)
				node->parent->left = node->right;

			else
				node->parent->right = node->right;
			delete temp;
			counter--;
			return;
		}
		else if (!node->right) {

			node->left->parent = node->parent;
			if (node->parent->left == node)
				node->parent->left = node->left;
			else
				node->parent->right = node->left;
			delete temp;
			counter--;
			return;
		}
	}

	else if (!node->left && !node->right) {

		if (node != root)
			(node->parent->left == node) ? node->parent->left = nullptr : node->parent->right = nullptr;
		else
			root = nullptr;
		delete temp;
		counter--;
		return;
	}

	temp = find_min(node->right);
	if (node && temp) {
		double temp2 = node->key;
		node->key = temp->key;
		temp->key = temp2;
	}
	Delete(temp);
}

node_bst* bst::find_min(node_bst* node)
{
	while (node->left) node = node->left;
	return node;
}

void bst::preorder(node_bst*& node)
{
	if (node) {
		std::cout << "(" << node->index << ": [p: ";
		(node->parent) ? std::cout << node->parent->index : std::cout << "NULL";
		std::cout << ", l: ";
		(node->left && node->left->index) ? std::cout << node->left->index : std::cout << "NULL";
		std::cout << ", r: ";
		(node->right && node->right->index) ? std::cout << node->right->index : std::cout << "NULL";
		std::cout << "], data: " << node->key << " ) , " << std::endl;

		preorder(node->left);
		preorder(node->right);
	}
}


void bst::DeleteAll()
{

	while (root && (root->right || root->left)) {
		if (root->right)
			Delete(root->right);
		if (root->left)
			Delete(root->left);
	}

	delete root;
	root = nullptr;

	return;
}