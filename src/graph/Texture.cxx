/*
 * Texture.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <sstream>
#include "Texture.hpp"


class FakeTexture : public Texture {
	public:
		FakeTexture(string name,
		            string filename) : Texture(GL_TEXTURE_2D, name,filename) {}
		FakeTexture(const Tag &tag) : Texture(GL_TEXTURE_2D, tag) {}
	protected:
		void initType() {type = GL_TEXTURE_2D;}
};


/**
 * Unit test for Texture.
 */
int main() {
	
	ostringstream name;
	Node *root, *last;
	Tag tag;
	Texture *texture;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Texture" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test tag
	cout << "\nTesting tag..." << endl;
	tag.setAttribute("name", "foo");
	tag.setAttribute("file", "glsl/bar.frag");
	texture = new FakeTexture(tag);
	texture->print();
	
	// Create textures
	cout << "\nCreating textures..." << endl;
	root = new Node();
	last = root;
	for (int i=0; i<4; ++i) {
		name.str("");
		name << "crate" << i+1;
		texture = new FakeTexture(name.str(), "../../input/crate.jpg");
		last->addChild(texture);
		last = texture;
	}
	
	// Prepare nodes
	cout << "\nPreparing nodes..." << endl;
	root->associateTree();
	root->finalizeTree();
	root->printTree();
	
	// Print types (,,32879)
	cout << "\nPrinting types..." << endl;
	cout << "  GL_TEXTURE_1D: " << GL_TEXTURE_1D << endl;
	cout << "  GL_TEXTURE_2D: " << GL_TEXTURE_2D << endl;
	cout << "  GL_TEXTURE_3D: " << GL_TEXTURE_3D << endl;
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Texture" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}

