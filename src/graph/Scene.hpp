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
#include "Factory.hpp"
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
		
		Node *last, root;
		Selection selection;
		Vector position;
		
		Scene(int width=512,
		      int height=512);
		void addToLast(Node *node);
		void addToRoot(Node *node);
		void backup();
		void prepare();
		void open(string filename);
		void print();
		void reset();
		void rotate(float angle,
		            float x,
		            float y,
		            float z);
		void sortByDepth();
		
		string getFilename() const;
		int getHeight() const;
		Matrix getRotationMatrix() const;
		int getWidth() const;
		void setFilename(const string &filename);
		void setRotation(float angle,
		                 float x,
		                 float y,
		                 float z);
	
	private :
		
		int height, width;
		string filename;
		Quaternion rotation;
		
		void destroy(Node *node);
};


inline string Scene::getFilename() const {
	return filename;
}

inline int Scene::getHeight() const {
	return height;
}

inline int Scene::getWidth() const {
	return width;
}

inline void Scene::setFilename(const string &filename) {
	this->filename = filename;
}


#endif
