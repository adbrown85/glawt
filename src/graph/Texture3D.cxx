/*
 * Texture3D.cxx
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Texture3D.hpp"
using namespace std;



/**
 * Unit test for Texture3D.
 */
int main(int argc,
         char *argv[]) {
	
	Texture3D *texture;
	
	// Test
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Texture3D" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Create texture
	texture = new Texture3D("input/volume.txt");
	texture->associate();
	
	// Attributes
	cerr << "Attributes:" << endl;
	texture->print();
	
	// Slices
	cerr << "\nSlices:" << endl;
	for (int i=0; i<texture->getWidth(); ++i) {
		texture->printSlice(i);
		cerr << endl;
	}
	
	// Test
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Texture3D" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}
