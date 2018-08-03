#include "stdafx.h"
#include "OrgTree.h"
#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#define TREENODEPTR OrgTree::TreeNode*

using namespace std;
// Private variables for the class
OrgTree::OrgTree()
{
	treeSize = 0;
	root = TREENULLPTR;
}
// Returns Title of a node
string OrgTree::TreeNode::getTitle() 
{
	return title;
}
// Returns Name of a node
string OrgTree::TreeNode::getName() 
{
	return name;
}

// Creates new root and assigns the old root as a child
// Time Complexity: 1
void OrgTree::addRoot(string title, string name)
{
	cout << "IN THE ADD ROOT METHOD" << endl;
	TreeNode *newRoot = new TreeNode(title, name);

	if (!root) {
		cout << "Root didn't exist" << endl;
		root = newRoot;
		treeSize++;
		cout << "Added Root" << endl;
	}
	else
	{
		cout << "Adding new Parent Root" << endl;
		newRoot->leftChild = root;
		root = newRoot;
		treeSize++;
	}
}
// Returns size of tree
// Time Complexity: 1
int OrgTree::getSize()
{
	return treeSize;
}
// Returns root of the tree
// Time Complexity: 1
TREENODEPTR OrgTree::getRoot()
{
	return root;
}
// Returns leftmost child of a node
// Time Complexity: 1
TREENODEPTR OrgTree::leftMostChild(TREENODEPTR node)
{
	TreeNode *current = node;
	if (current->leftChild == nullptr) // Maybe??
	{
		return TREENULLPTR;
	}
	else
	{
		return current->leftChild;
	}

}
// Returns right sibling of a node
// Time Complexity: 1
TREENODEPTR OrgTree::rightSibling(TREENODEPTR node)
{
	if (node->rightSibling == TREENULLPTR)
	{
		return TREENULLPTR;
	}
	else
	{
		return node->rightSibling;
	}
}
// Returns the subtree when given a starting point, or subTreeRoot
// Time Complexity: n
void OrgTree::printSubTree(TREENODEPTR subTreeRoot)
{
	if (subTreeRoot->leftChild == nullptr)
	{
		cout << "No other nodes in Sub-Tree" << endl;
	}
	else
	{
		cout << subTreeRoot->getTitle() + " " + subTreeRoot->getName() << endl;
		//Helper(leftMostChild(subTreeRoot), 1);
		if (leftMostChild(subTreeRoot))
			Helper(leftMostChild(subTreeRoot), 1);
	}
}

// Creates the Indentation for the print sub tree method
// Time Complexity: n
void OrgTree::Helper(TREENODEPTR subTreeRoot, int indent)
{
	for (int i = 0; i < indent; i++)
	{
		printf("\t");
	}
	cout << subTreeRoot->getTitle() + " " + subTreeRoot->getName() << endl;
	if (leftMostChild(subTreeRoot) != nullptr)
	{
		Helper(leftMostChild(subTreeRoot), indent + 1);
	}
	if (rightSibling(subTreeRoot) != nullptr)
	{
		Helper(rightSibling(subTreeRoot), indent);
	}
}
// Given a title, find the Node
// Time Complexity: n
TREENODEPTR OrgTree::find(string title)
{
	cout << "In the Find method" << endl;
	if (title.compare(root->getTitle()) == 0)
	{
		cout << "Returned Root" << endl;
		return root;
	}

	if (leftMostChild(root) != nullptr)
	{
		return findHelper(leftMostChild(root), title);
	}
	else
	{
		return TREENULLPTR;
	}
}
// Helps the find method and creates the indintation
// Time Complexity: n
TREENODEPTR OrgTree::findHelper(TREENODEPTR node, string title)
{
	TreeNode *current = TREENULLPTR;
	if (title.compare(node->getTitle()) == 0)
	{
		cout << "Found Title" << endl;
		return node;
	}
	if (leftMostChild(node) != nullptr)
	{
		cout << "Checking Left Child. It is not null" << endl;
		current = findHelper(leftMostChild(node), title);
	}
	if ((rightSibling(node) && !current))
	{
		cout << "Checking Right Sibling. It is Not null" << endl;
		current = findHelper(rightSibling(node), title);
	}
	return current;
}
// Reads the text file
// Time Complexity: n
bool OrgTree::read(string filename)
{
	ifstream file;
	file.open(filename);
	stack<string> st;
	string title;
	string name;
	getline(file, title, ',');
	getline(file, name, '\n');
	addRoot(title, name);
	st.push(title);
	while (file.peek() != EOF && !st.empty()) 
	{
		if (file.peek() == ')') 
		{
			string tester;
			getline(file, tester);
			st.pop();
		}
		else 
		{
			getline(file, title, ',');
			getline(file, name, '\n');
			hire(find(st.top()), title, name);
			st.push(title);
		}
	}
	file.close();
	return true;
}
// Writes the tree to a .txt file
// Time Complexity: n
void OrgTree::write(string fileName)
{
	ofstream output;
	output.open(fileName);
	output << writeHelper(root) << endl;
	output.close();
}
// Creates the paranthesis in the method
// Time COmplexity: n
string OrgTree::writeHelper(TREENODEPTR current) {
	if (current) {
		string line = current->getTitle() + " " + current->getName() + "\n";
		line += writeHelper(current->leftChild);
		line += ")\n";
		line += writeHelper(current->rightSibling);
		return line;
	}	
	else
	{
		return "";
	}
}

// Where Node is the parent of the new node being added.
// Time Complexity: n
void OrgTree::hire(TREENODEPTR parent, string newTitle, string newName)
{
	TreeNode *newEmployee = new TreeNode(newTitle, newName);
	TreeNode *current;

	if (find(parent->getTitle()) == TREENULLPTR) {
		cout << "Parent Doesn't Exist" << endl;
	}
	if (parent->leftChild == nullptr) 
	{
		parent->leftChild = newEmployee;
		treeSize++;
	}
	else if (leftMostChild(parent) != nullptr) 
	{
		current = parent->leftChild;
		while (current->rightSibling != nullptr) 
		{
			current = current->rightSibling;
		}
		current->rightSibling = newEmployee;
		treeSize++;
	}
}
// Rturens the parent of the node it is passed
// Time Complexity: n
TREENODEPTR OrgTree::getParent(string title) 
{

	if (title.compare(root->getTitle()) == 0) 
	{
		return TREENULLPTR;
	}
	if (leftMostChild(root)) 
	{
		return getParentHelper(title, leftMostChild(root), root);
	}
	else
	{
		return TREENULLPTR;
	}
	
}
// Helps get the parent of the given node
// Time Complexity: n
TREENODEPTR OrgTree::getParentHelper(string title, TREENODEPTR child, TREENODEPTR tmp) 
{
	TreeNode *parent = TREENULLPTR;
	if (title.compare(child->getTitle()) == 0)
	{
		return tmp;
	}
	if (leftMostChild(child)) 
	{
		parent = getParentHelper(title, leftMostChild(child), child);
	}
	if (rightSibling(child) && !parent) 
	{
		parent = getParentHelper(title, rightSibling(child), tmp);
	}
	return parent;
}
// Fires an employee. Then takes the children from the fired Employee (if any)
// and makes them right siblings of the parent.
// Time Complexity: n
bool OrgTree::fire(string formertitle)
{
	TreeNode *superParent = getParent(formertitle);
	TreeNode *rightMostSibling = TREENULLPTR;
	TreeNode *leftSibling = TREENULLPTR;
	TreeNode *fire = find(formertitle); // Node we will delete

	// Checks to make sure the node is not the Root
	if (formertitle.compare(root->getTitle()) == 0)
	{
		return false;
	}
	// Checks to make sure the node exists
	if (fire == TREENULLPTR)
	{
		return false;
	}
	// If Soon to be Deleted Node doesn't have children
	if (fire == superParent->leftChild)
	{
		if (fire->rightSibling)
		{
			rightMostSibling = fire->rightSibling;
			while (rightMostSibling->rightSibling != TREENULLPTR)
			{
				rightMostSibling = rightMostSibling->rightSibling;
			}
			superParent->leftChild = fire->rightSibling;
			rightMostSibling->rightSibling = fire->leftChild;
		}
		else
		{
			superParent->leftChild = fire->leftChild;
		}
		delete fire;
		treeSize--;
		return true;
	}
	else
	{
		leftSibling = superParent->leftChild;
		while (fire != leftSibling->rightSibling)
		{
			leftSibling = leftSibling->rightSibling;
		}

		rightMostSibling = fire->rightSibling;
		if (rightMostSibling == TREENULLPTR)
		{
			rightMostSibling = leftSibling;
		}
		else
		{
			while (rightMostSibling->rightSibling != TREENULLPTR) 
			{
				rightMostSibling = rightMostSibling->rightSibling;
			}
		}

		leftSibling->rightSibling = rightMostSibling;
		rightMostSibling->rightSibling = fire->leftChild;

		delete fire;
		treeSize--;
		return true;
	}

	return false;
	
}
// Destructor
// Time Complexity: n
OrgTree::~OrgTree()
{
	destroyer(root);
}
// Destorys tree
// Time Complexity: n
void OrgTree::destroyer(TREENODEPTR node) 
{
	if (node->leftChild)
		destroyer(node->leftChild);
	if (node->rightSibling)
		destroyer(node->rightSibling);
	delete node;
}