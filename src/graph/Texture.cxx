/*
 * Texture.cxx
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include <sstream>
#include "Texture.hpp"
#include "Scene.hpp"


class FakeTexture : public Texture {
	public:
		FakeTexture(string name,
		            string filename) : Texture(name,filename) {}
		FakeTexture(const Tag &tag) : Texture(tag) {}
	protected:
		void initType() {type = GL_TEXTURE_2D;}
};


/**
 * Unit test for Texture.
 */
int main() {
	
	ostringstream name;
	Scene scene;
	Tag tag;
	Texture *texture;
	
	// Test tag
	cout << "\nTesting tag..." << endl;
	tag.attributes["name"] = "foo";
	tag.attributes["file"] = "glsl/bar.frag";
	texture = new FakeTexture(tag);
	texture->print();
	
	// Create textures
	cout << "\nCreating textures..." << endl;
	for (int i=0; i<4; ++i) {
		name.str("");
		name << "crate" << i+1;
		texture = new FakeTexture(name.str(), "../../input/crate.jpg");
		scene.addToLast(texture);
	}
	
	// Prepare nodes
	cout << "\nPreparing nodes..." << endl;
	scene.prepare();
	scene.print();
}

