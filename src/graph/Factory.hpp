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
#include "Ambient.hpp"
#include "Box.hpp"
#include "BoxVBO.hpp"
#include "Cull.hpp"
#include "Diffuse.hpp"
#include "Framebuffer.hpp"
#include "FileUtility.hpp"
#include "Fullscreen.hpp"
#include "Light.hpp"
#include "Node.hpp"
#include "Octree.hpp"
#include "Parser.hpp"
#include "Position.hpp"
#include "Program.hpp"
#include "Scene.hpp"
#include "Shader.hpp"
#include "Specular.hpp"
#include "Square.hpp"
#include "Texture2D.hpp"
#include "Texture3D.hpp"
#include "Translation.hpp"
#include "Tag.hpp"
#include "Target.hpp"
#include "Uniform.hpp"
using namespace std;


/**
 * @ingroup graph
 * @brief
 *     Creates items from XML tags and adds them to the scene.
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
