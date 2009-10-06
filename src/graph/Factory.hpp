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
#include <map>
#include <set>
#include <vector>
#include "Box.hpp"
#include "Cull.hpp"
#include "Framebuffer.hpp"
#include "FileUtility.hpp"
#include "Fullscreen.hpp"
#include "Node.hpp"
#include "Parser.hpp"
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
		
		Factory(Node *root,
		        string filename);
		void start();
	
	
	private:
		
		Node *root;
		Parser parser;
		string filename;
		
		Node* create(const Tag &tag);
};


#endif
