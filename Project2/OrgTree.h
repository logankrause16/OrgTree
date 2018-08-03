#pragma once
#include "stdafx.h"
#define TREENODEPTR TreeNode*
#define TREENULLPTR NULL
#include <string>

using namespace std;

class OrgTree
{

public:

	class TreeNode {
	public:
		string title;
		string name;
		TreeNode *leftChild;
		TreeNode *rightSibling;

		TreeNode() {
			title = "";
			name = "";
			leftChild = TREENULLPTR;
			rightSibling = TREENULLPTR;
		}

		TreeNode(string newTitle, string newName)
		{
			title = newTitle;
			name = newName;
			leftChild = TREENULLPTR;
			rightSibling = TREENULLPTR;
		}
		string getTitle();
		string getName();

	};

	OrgTree();
	void addRoot(string, string);
	int getSize();
	TreeNode* getRoot();
	TREENODEPTR leftMostChild(TREENODEPTR);
	TREENODEPTR rightSibling(TREENODEPTR);
	void printSubTree(TREENODEPTR);
	void Helper(TREENODEPTR, int);
	TREENODEPTR find(string);
	TREENODEPTR findHelper(TREENODEPTR, string);
	bool read(string);
	void write(string);
	string writeHelper(TREENODEPTR);
	TREENODEPTR getParent(string);
	TREENODEPTR getParentHelper(string, TREENODEPTR, TREENODEPTR);
	void hire(TREENODEPTR, string, string);
	bool fire(string);
	~OrgTree();
	void destroyer(TREENODEPTR);
private:
	int treeSize;
	TreeNode* root;
};

