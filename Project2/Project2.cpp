// Project2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "OrgTree.h"
#include <string>
#include <iostream>

using namespace std;
int main()
{
	OrgTree a1;
	a1.addRoot("Software Developer", "Logan Krause");
	a1.addRoot("Human Resources", "Hannah Myers");
	a1.addRoot("Research Assistant", "Corbin McGuire");
	cout << a1.find("Human Resources") << endl;
	a1.hire(a1.getRoot(), "Video Stuff", "Lucas Krause");
	a1.hire(a1.getRoot(), "Video Editing", "Peter Krause");
	//cout << a1.printSubTree(a1.getRoot()) << endl;
	//cout << a1.getSize() << endl;
	//cout << a1.getRoot() << endl;
	//a1.rightSibling(a1.getRoot());
	//a1.leftMostChild(a1.getRoot());
//	a1.hire(a1.find("Human Resources"), "R3C1C1", "R3C1C1");//test find on leaf node and hire to it
	a1.printSubTree(a1.getRoot());
	cout << a1.find("Research Assistant") << endl;
	cout << a1.getSize() << endl;
	a1.fire("Video Editing");
	a1.fire("Human Resources");

	cout << a1.getSize() << endl;
	a1.printSubTree(a1.getRoot());
	//cout << a1.find("Software Developer") << endl;
	//cout << a1.getName(a1.getRoot()) << endl;
	//cout << a1.getTitle(a1.getRoot()) << endl;
	system("pause");
}