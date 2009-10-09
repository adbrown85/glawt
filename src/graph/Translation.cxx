/*
 * Translation.cxx
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include <ctime>
#include "Translation.hpp"



/**
 * Fake leaf node that computes its depth from the matrix.
 */
class FakeLeaf : public Node {
	public :
		FakeLeaf() : Node() {
			className = "Leaf";
		}
		virtual void computeDepth(Matrix &matrix) {
			depth = matrix(2,3);
		}
};




/**
 * Unit test for Translation.
 */
int main() {
	
	FakeLeaf leafs[4];
	float randomNum;
	Matrix rotMatrix;
	Node root;
	Tag tag;
	Translation *translation, trans[4];
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Translation" << endl;
	cout << "****************************************" << endl;
	
	// Test tag
	cout << "\nTesting tag..." << endl;
	tag.attributes["x"] = "10.0";
	tag.attributes["y"] = "20.0";
	tag.attributes["z"] = "30.0";
	translation = new Translation(tag);
	translation->print();
	
	// Build tree
	cout << "\nBuilding tree..." << endl;
	for (int i=0; i<4; ++i) {
		root.addChild(&trans[i]);
		trans[i].addChild(&leafs[i]);
	}
	root.printTree();
	
	// Randomize
	cout << "\nRandomizing translations..." << endl;
	srand(time(NULL));
	for (int i=0; i<4; ++i) {
		randomNum = rand() % 10;
		trans[i].set(randomNum, randomNum, randomNum);
	}
	root.printTree();
	
	// Sort by depth
	cout << "\nSorting by depth..." << endl;
	root.sortByDepth(rotMatrix);
	root.printTree();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Translation" << endl;
	cout << "****************************************" << endl;
}