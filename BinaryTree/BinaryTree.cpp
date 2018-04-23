#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

struct Tree
{
	struct Node
	{
		int data;
		Node* left;
		Node* right;

		Node(int data, Node* left = nullptr, Node* right = nullptr)
		{
			this->data = data;
			this->left = left;
			this->right = right;
		}
	};

	int Size;
	Node* root;

	Tree()
	{
		Size = 0;
		root = nullptr;
	}

	void AddNode(int data)
	{
		if (root == nullptr)
		{
			root = new Node(data);
		}
		else
		{
			Node* current = this->root;
			while (true)
			{
				if (data < current->data)
				{
					if (current->left == nullptr)
					{
						current->left = new Node(data);
						break;
					}
					else
					{
						current = current->left;
					}
				}
				else if (data > current->data)
				{
					if (current->right == nullptr)
					{
						current->right = new Node(data);
						break;
					}
					else
					{
						current = current->right;
					}
				}
				else
				{
					break;
				}
			}
		}
		Size++;
	}

	Node* FindMaxElement(Node* root)
	{
		if (root == NULL) return NULL;
		while (root->right != NULL)
		{
			root = root->right;
		}
		return root;
	}

	Node* DeleteNode(Node* root, int data)
	{
		if (root == NULL) return root;
		else if (data < root->data && root->left != nullptr)
			root->left = DeleteNode(root->left, data);
		else if (data > root->data && root->right != nullptr)
			root->right = DeleteNode(root->right, data);
		else if (data == root->data)
		{
			//no child
			if (root->right == NULL && root->left == NULL)
			{
				delete root;
				root = NULL;
				Size--;
			}
			//one child 
			else if (root->right == NULL)
			{
				Node* temp = root;
				root = root->left;
				delete temp;
				Size--;
			}
			else if (root->left == NULL)
			{
				Node* temp = root;
				root = root->right;
				delete temp;
				Size--;
			}
			//two child
			else
			{
				Node* temp = FindMaxElement(root->left);
				root->data = temp->data;
				root->left = DeleteNode(root->left, temp->data);
			}
		}
		return root;
	}

	void PrintTree(Node* node, int indent = 0)
	{
		if (node != NULL) {
			if (node->right) {
				PrintTree(node->right, indent + 4);
			}
			if (indent) {
				std::cout << std::setw(indent) << ' ';
			}
			if (node->right) std::cout << " /\n" << std::setw(indent) << ' ';
			std::cout << node->data << "\n ";
			if (node->left) {
				std::cout << std::setw(indent) << ' ' << " \\\n";
				PrintTree(node->left, indent + 4);
			}
		}
	}
};

Tree CreateTree(int length);
int* GetRandomNumbers(int min, int max, int size);

int main()
{
	srand(time(NULL));
	Tree tree;
	bool InProcess = true;
	while (InProcess)
	{
		int count;
		int value;
		cout << "Enter 1 if you want to add element in the tree" << endl;
		cout << "Enter 2 if you want to delete element in the tree" << endl;
		cout << "Enter 3 if you want to print the tree" << endl;
		cout << "Enter 4 if you want to create a tree with a random values" << endl;
		cout << "Enter 0 if you want to exit" << endl;
		cin >> count;
		switch (count)
		{
		case 1:
		{
			cout << "Enter value you want to add: " << endl;
			cin >> value;
			tree.AddNode(value);
			break;
		}
		case 2:
		{
			cout << "Enter value you want to delete: " << endl;
			cin >> value;
			tree.DeleteNode(tree.root, value);
			break;
		}
		case 3:
		{
			tree.PrintTree(tree.root);
			break;
		}
		case 4:
		{
			cout << "Enter number of nodes in the tree: " << endl;
			cin >> value;
			tree = CreateTree(value);
			break;
		}
		case 0:
		{
			InProcess = false;
			break;
		}
		default:
			break;
		}
	}
	return 0;
}

Tree CreateTree(int length)
{
	Tree tree;
	int *arr = GetRandomNumbers(-99, 99, length);
	for (int i = 0; i < length; i++)
	{
		tree.AddNode(arr[i]);
	}
	return tree;
}

int* GetRandomNumbers(int min, int max, int size)
{
	int *arr = new int[size];
	int currentSize = 1;
	for (int i = 0; i < size; i++)
	{
		bool alreadyInArray = false;
		int num = rand() % (max - min + 1) + min;
		for (int i = 0; i < currentSize; i++)
		{
			if (num == arr[i])
			{
				alreadyInArray = true;
				break;
			}
		}
		if (!alreadyInArray)
		{
			currentSize++;
			arr[i] = num;
		}
		else
		{
			i--;
		}
	}
	return arr;
}

