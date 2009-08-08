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
	Translation trans[4];
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Translation" << endl;
	cout << "****************************************" << endl;
	
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
