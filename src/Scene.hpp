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
#include "Quaternion.hpp"
#include "Shader.hpp"
#include "Uniform.hpp"
using std::vector;



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
		Item* getItem(int id) const;
		int getWidth() const {return width;}
		
		Vector position, rotation;
		vector<Item*> items;
		vector<Shader*> shaders;
		vector<Uniform*> uniforms;
	
	
	private :
		
		int height, width;
};


#endif
