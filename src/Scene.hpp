/*
 * Scene.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __SCENE_HPP__
#define __SCENE_HPP__
#define SCENE_DEFAULT_HEIGHT 480
#define SCENE_DEFAULT_WIDTH 640
#define SCENE_DEFAULT_ZOOM -10.0
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "Item.hpp"
#include "Matrix.hpp"
#include "Node.hpp"
#include "Quaternion.hpp"
#include "Shader.hpp"
#include "Uniform.hpp"
#include "Vector.hpp"
using std::cout;
using std::endl;
using std::vector;



/**
 * @brief
 *     Collection of items that also stores selection and camera information.
 */
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
		void rotate(float angle, float x, float y, float z);
		void selectAll();
		void print();
		
		int getHeight() const {return height;}
		Item* getItem(int id) const;
		Matrix getRotationMatrix() const;
		int getWidth() const {return width;}
		void setRotation(float angle, float x, float y, float z);
		
		Node rootNode;
		Vector position;
		vector<Item*> items;
		vector<Shader*> shaders;
		vector<Uniform*> uniforms;
	
	
	private :
		
		int height, width;
		Quaternion rotation;
};


#endif
