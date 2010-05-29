/*
 * OctreeBuilder.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "OctreeBuilder.hpp"


class OctreeBuilderTester : public OctreeBuilder {
public:
	OctreeBuilderTester(Dataset *dataset) : 
	                    OctreeBuilder(dataset) {}
	static void indent(int times);
	void print();
	static void print(OctreeNode *node);
	void printOffsets();
	static void printRecursive(OctreeNode *node,
	                           int depth,
	                           int maximumDepth);
};


void OctreeBuilderTester::indent(int times) {
	
	for (int i=0; i<times; ++i) {
		cout << "  ";
	}
}


void OctreeBuilderTester::print() {
	
	cout << toString() << endl;
}


void OctreeBuilderTester::print(OctreeNode *node) {
	
	cout << node->toString() << endl;
}


void OctreeBuilderTester::printOffsets() {
	
	for (int i=0; i<getTreeHeight()+1; ++i) {
		cout << "  " << getOffsets()[i] << endl;
	}
}


void OctreeBuilderTester::printRecursive(OctreeNode *node,
                                         int depth,
                                         int maximumDepth) {
	
	if (depth > maximumDepth || node == NULL)
		return;
	
	indent(depth);
	print(node);
	for (int i=0; i<8; ++i) {
		printRecursive(node->getChild(i), depth+1, maximumDepth);
	}
}


int main(int argc,
         char *argv[]) {
	
	Dataset *dataset;
	float threshold;
	OctreeNode *root;
	OctreeBuilderTester *builder;
	string filename;
	
	// Handle arguments
	if (argc == 1) {
		filename = "../../textures/bear.vlb";
		threshold = 0;
	} else if (argc == 3) {
		filename = argv[1];
		threshold = atoi(argv[2]);
	} else {
		cerr << "Usage: " << argv[0] 
		     << " <filename>"
		     << " <threshold>" << endl;
		exit(1);
	}
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "OctreeBuilder" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	try {
	
		// Basics
		dataset = new Dataset(filename);
		builder = new OctreeBuilderTester(dataset);
		builder->setThreshold(threshold);
		builder->print();
		cout << "Offsets: " << endl;
		builder->printOffsets();
		
		// Build
		cout << "\nBuilding: " << endl;
		root = builder->build();
		OctreeBuilderTester::printRecursive(root, 0, 2);
		
		// Total nodes
		cout << "\nTotal Nodes: " << endl;
		cout << "  " << builder->getTotalNodes() << endl;
	}
	catch (Exception &e) {
		cerr << e << endl;
	}
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "OctreeBuilder" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}

