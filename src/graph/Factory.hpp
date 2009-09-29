/*
 * Factory.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef FACTORY_HPP
#define FACTORY_HPP
#include <cstdlib>
#include <iostream>
#include <set>
#include <vector>
#include "Box.hpp"
#include "Framebuffer.hpp"
#include "Fullscreen.hpp"
#include "Node.hpp"
#include "Program.hpp"
#include "Scene.hpp"
#include "Shader.hpp"
#include "Square.hpp"
#include "Texture2D.hpp"
#include "Texture3D.hpp"
#include "Translation.hpp"
#include "Tag.hpp"
#include "Target.hpp"
#include "Uniform.hpp"
using namespace std;



/**
 * @brief
 *     Creates items from XML tags and adds them to the scene.
 * @ingroup backend
 */
class Factory {
	
	
	public:
		
		Factory(Node *root);
		void process(const vector<Tag> &tags);
	
	
	private:
		
		Node *root;
		
		Node* create(const Tag &tag);
		Node* createTexture(const Tag &tag);
};


#endif
