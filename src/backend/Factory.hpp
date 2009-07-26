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
#include "Program.hpp"
#include "Scene.hpp"
#include "Shader.hpp"
#include "Shape.hpp"
#include "Texture.hpp"
#include "Translation.hpp"
#include "Tag.hpp"
#include "Uniform.hpp"
using namespace std;



class Factory {
	
	
	public :
		
		Factory(Scene *scene);
		void process(vector<Tag> &tags);
	
	
	private:
		
		Node *current;
		Scene *scene;
		set<string> containers;
		
		void createProgram(Tag &tag);
		void createShader(Tag &tag);
		void createShape(Tag &tag);
		void createTexture(Tag &tag);
		void createTranslation(Tag &tag);
		void createUniform(Tag &tag);
		
		void initContainers();
		bool isContainer(string name);
};


#endif
