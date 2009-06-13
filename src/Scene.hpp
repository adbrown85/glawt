/*
 * Scene.hpp
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#ifndef __SCENE_HPP__
#define __SCENE_HPP__
#define SCENE_DEFAULT_HEIGHT 480
#define SCENE_DEFAULT_WIDTH 640
#define SCENE_DEFAULT_ZOOM -10.0
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <string>
#include <vector>
#include "Item.hpp"
#include "Shader.hpp"
#include "Uniform.hpp"



class Scene {
	
	
	public :
		
		Scene();
		Scene(int width, int height);
		
		void add(Item *item);
		void add(Shader *shader);
		void deselectAll();
		void draw(GLenum mode);
		bool hasSelected();
		void reset();
		void selectAll();
		void print();
		
		int getHeight() const {return height;}
		int getWidth() const {return width;}
		
		std::vector<Item*> items;
		std::vector<Shader*> shaders;
		std::vector<Uniform*> uniforms;
		Vector position, rotation;
	
	
	private :
		
		int height, width;
};


#endif
