#pragma once
#include<iostream>
#include<iomanip>
#include<algorithm>
#include<ctime>
#define COUNT 10 

struct Node
{
	int data, height;
	Node* left;
	Node* right;
};

Node* newNode(int key)
{
	Node* newNode = new Node;
	newNode->data = key;
	newNode->left = newNode->right = nullptr;
	newNode->height = 0;
	return newNode;
}
int findHeight(Node* root)
{
	if (root != nullptr)
	{
		return root->height;
	}
	else
		return -1;
}

Node* smallRightRevolve(Node*& root)
{
	Node* temp;
	temp = root->left;
	root->left = temp->right;
	temp->right = root;

	// recalculate heights for temp and root
	root->height = std::max(findHeight(root->left), findHeight(root->right)) + 1;
	temp->height = std::max(findHeight(temp->left), root->height) + 1;

	return temp;
}
Node* smallLeftRevolve(Node*& root)
{
	Node* temp;
	temp = root->right;
	root->right = temp->left;
	temp->left = root;

	// recalculate heights for temp and root
	root->height = std::max(findHeight(root->left), findHeight(root->right)) + 1;
	temp->height = std::max(findHeight(temp->right), root->height) + 1;

	return temp;
}
Node* bigRightRevolve(Node*& root)
{
	root->left = smallLeftRevolve(root->left);// small revolve for left kid
	return smallRightRevolve(root);// return small revolve for root
}

Node* bigLeftRevolve(Node*& root)
{
	root->right = smallRightRevolve(root->right);
	return smallLeftRevolve(root);
}

Node* insert(Node* root, int key)
{
	if (root == nullptr)
		root = newNode(key);
	else if (key < root->data)
	{
		root->left = insert(root->left, key);// change top to the left
		if (findHeight(root->left) - findHeight(root->right) == 2)
		{
			if (key < root->left->data)
				root = smallRightRevolve(root);
			else root = bigRightRevolve(root);
		}
	}
	else if (key >= root->data)
	{
		root->right = insert(root->right, key);
		if (findHeight(root->right) - findHeight(root->left) == 2)
		{
			if (key > root->right->data)
				root = smallLeftRevolve(root);
			else root = bigLeftRevolve(root);
		}
	}
	root->height = std::max(findHeight(root->left), findHeight(root->right)) + 1;// recalculate height

	return root;
}

Node* search(Node* root, int key)
{
	if (root == nullptr || root->data == key)
		return root;

	if (key > root->data)
		return search(root->right, key);
	else return search(root->left, key);
}
Node* findMinLeft(Node* root)
{
	Node* temp = root;
	while (temp && temp->left)
		temp = temp->left;
	return temp;
}
Node* deleteNode(Node* root, int key)
{
	if (root == nullptr)
		return root;

	// if key is bigger go on right tree, if smaller - left tree
	if (key > root->data)
		root->right = deleteNode(root->right, key);// reassign root
	else if (key < root->data)
		root->left = deleteNode(root->left, key);
	  // if there are kids
	else
	{
		// node has no kids or has one of them
		if (root->left == nullptr)
		{
			Node* temp = root->right;
			delete root;
			return temp;
		}
		if (root->right == nullptr)
		{
			Node* temp = root->left;
			delete root;
			return temp;
		}
		// if node has both kids
		Node* temp = findMinLeft(root->right);
		root->data = temp->data;
		root->right = deleteNode(root->right, temp->data);// delete foremost right node
	}

	root->height = std::max(findHeight(root->left), findHeight(root->right)) + 1;// recalculate height
	if (findHeight(root->right) - findHeight(root->left) == 2)// check if revolve is needed
	{
		if (findHeight(root->right->right) - findHeight(root->right->left) == 1)
			return root = smallLeftRevolve(root);
		else
			return root = bigLeftRevolve(root);
	}
	else if (findHeight(root->left) - findHeight(root->right) == 2)
	{
		if (findHeight(root->left->left) - findHeight(root->left->right) == 1)
			return root = smallRightRevolve(root);
		else
			return root = bigRightRevolve(root);
	}
	return root;
}

void printTree(Node* tree)
{
	if (tree == nullptr)
		return;

	printTree(tree->left);
	std::cout << tree->data << " ";
	printTree(tree->right);
}
void printAwesomeTree(Node* root, int space)// source https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
{
	// Base case  
	if (root == nullptr)
		return;

	// Increase distance between levels  
	space += COUNT;

	// Process right child first  
	printAwesomeTree(root->right, space);
	// Print current node after space  
  // count  
	std::cout << std::endl;
	for (int i = COUNT; i < space; i++)
		std::cout << " ";
	std::cout << root->data << "\n";

	// Process left child  
	printAwesomeTree(root->left, space);
}