/*
 * Texture.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <sstream>
#include "Texture.hpp"
#include "Scene.hpp"


class FakeTexture : public Texture {
public:
	FakeTexture(const Tag &tag) : Texture(GL_TEXTURE_2D, tag) {}
protected:
	void initType() {type = GL_TEXTURE_2D;}
};


Node* create(const Tag &tag) {
	return new FakeTexture(tag);
}


/**
 * Unit test for Texture.
 */
int main() {
	
	Scene scene;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Texture" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Open scene
	Factory::install("texture", &create);
	scene.open("Texture.xml");
	scene.prepare();
	scene.print();
	
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

