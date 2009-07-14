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
#include "Matrix.hpp"
#include "Node.hpp"
#include "Quaternion.hpp"
#include "Shape.hpp"
#include "Vector.hpp"
using std::cout;
using std::endl;
using std::vector;



/**
 * @brief
 *     Collection of items that also stores selection and camera information.
 * @ingroup graph
 */
class Scene {
	
	
	public :
		
		Scene();
		Scene(int width, int height);
		
		void reset();
		void rotate(float angle, float x, float y, float z);
		void print();
		
		int getHeight() const {return height;}
		Matrix getRotationMatrix() const;
		int getWidth() const {return width;}
		void setRotation(float angle, float x, float y, float z);
		
		Node rootNode;
		Vector position;
	
	
	private :
		
		int height, width;
		Quaternion rotation;
};


#endif
