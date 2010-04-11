/*
 * OctreeNode.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "OctreeNode.hpp"


void print(OctreeNode &node) {
	
	cout << node.toString() << endl;
}


int main(int argc,
         char *argv[]) {
	
	OctreeNode node, *child;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "OctreeNode" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Empty
	cout << "Empty: " << endl;
	print(node);
	node.setEmpty(true);
	print(node);
	node.setEmpty(false);
	print(node);
	
	// Children
	cout << "\nChildren: " << endl;
	node.setChild(0, new OctreeNode());
	node.setChild(1, new OctreeNode());
	for (int i=0; i<8; ++i) {
		child = node.getChild(i);
		if (child != NULL) {
			print(*child);
		}
	}
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "OctreeNode" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}

