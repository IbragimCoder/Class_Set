﻿#include <iostream>
#include <vector>

class RBTree
{
private:
	/*class Node
	{
	public:
		bool isRed;
		int val;
		Node* left;
		Node* right;
		Node() :val(0), isRed(true), left(NULL), right(NULL) {}
		Node(int x) : val(x), isRed(true), left(NULL), right(NULL) {}
	};

	Node* root;
	std::vector<Node*> arr;*/
public:
	class Node
	{
	public:
		bool isRed;
		int val;
		Node* left;
		Node* right;
		Node() :val(0), isRed(true), left(NULL), right(NULL) {}
		Node(int x) : val(x), isRed(true), left(NULL), right(NULL) {}
	};

	Node* root;
	std::vector<Node*> arr;
	RBTree() : root(NULL) {}
	RBTree(int v) : root(new Node(v)) {}
	~RBTree()
	{
		if (root != NULL)
		{
			destruct(root);
			delete root;
		}
		arr.clear();
	}

	void destruct(Node* node)
	{
		if (node->left != NULL)
		{
			destruct(node->left);
			delete node->left;
		}
		if (node->right != NULL)
		{
			destruct(node->right);
			delete node->right;
		}
	}

	bool isRed(Node* node)
	{
		if (node == NULL)
		{
			return false;
		}
		else
		{
			return node->isRed;
		}

	}

	void rotateRight(Node*& node)// перевернуть направо
	{
		Node* temp = node->left;
		node->left = temp->right;
		temp->right = node;

		temp->isRed = node->isRed;
		node->isRed = true;
		node = temp;
	}

	void rotateLeft(Node*& node)
	{
		Node* temp = node->right;
		node->right = temp->left;
		temp->left = node;
		temp->isRed = node->isRed;
		node->isRed = true;
		node = temp;
	}

	void flipColor(Node*& node)
	{
		node->isRed = true;
		node->left->isRed = false;
		node->right->isRed = false;
	}

	void buildTree()
	{
		int tempArr[10] = { 3,4,7,1,2,9,8,6,5,10 };
		for (int i = 0; i != 10; i++)
		{
			arr.push_back(new Node(tempArr[i]));
			insert(root, arr[i]);
		}
		display(root);
	}

	void insert(Node*& node, Node*& vNode)
	{
		if (node == NULL)
		{
			node = vNode;
		}

		if (node->val > vNode->val)
		{
			insert(node->left, vNode);
		}
		else if (node->val < vNode->val)
		{
			insert(node->right, vNode);
		}

		if (isRed(node->right) && !isRed(node->left))
		{
			rotateLeft(node);
		}

		if (isRed(node->left) && isRed(node->left->left))
		{
			rotateRight(node);
		}

		if (isRed(node->left) && isRed(node->right))
		{
			flipColor(node);
		}
	}

	void display(Node* node)
	{
		if (node == NULL)
		{
			return;
		}
		display(node->left);

		std::cout << node->val << "  ";
		display(node->right);

	}

};

class Set :public RBTree
{
private:
	RBTree mySet;

public:
	Set(int y, int* tempArr) : RBTree(y)
	{
		mySet.root = new Node(y);
		mySet.arr.push_back(mySet.root);

		for (int i = 0; i < 3; i++)
		{
			Node* newNode = new Node(tempArr[i]);

			mySet.arr.push_back(newNode);
			insert_set(tempArr[i]);
		}
	}


	void insert_set(int tmp)
	{
		Node* newNode = new Node(tmp);

		mySet.arr.push_back(newNode);
		insert(mySet.root, newNode);
	}

	bool contains(int x)
	{
		if (x == mySet.root->val)
		{
			return true;
		}
		for (const auto& t : mySet.arr)
		{
			if (t->val == x)
			{
				return true;
			}
		}

		insert_set(x);
		return false;
	}

	void displaySet()
	{
		if (mySet.root == NULL)
		{
			std::cout << "Set is empty!" << "\n";
			return;
		}

		display(mySet.root);
	}

};

int main()
{


	return 0;
}
