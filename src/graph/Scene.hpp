/*
 * Scene.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef SCENE_HPP
#define SCENE_HPP
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <string>
#include <vector>
#include "Matrix.hpp"
#include "Node.hpp"
#include "Quaternion.hpp"
#include "Selection.hpp"
#include "Vector.hpp"
using namespace std;



/**
 * @ingroup graph
 * @brief
 *     Collection of items that also stores selection and camera information.
 */
class Scene {
	
	
	public :
		
		Node rootNode;
		Selection selection;
		Vector position;
		
		Scene();
		Scene(int width, int height);
		void add(Node *node);
		void prepare();
		void print();
		void reset();
		void rotate(float angle, float x, float y, float z);
		void sortByDepth();
		
		string getFilename() const {return filename;}
		int getHeight() const {return height;}
		Matrix getRotationMatrix() const;
		int getWidth() const {return width;}
		void setFilename(string filename) {this->filename = filename;}
		void setRotation(float angle, float x, float y, float z);
	
	
	private :
		
		int height, width;
		string filename;
		Quaternion rotation;
};


#endif
