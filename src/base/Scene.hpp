/*
 * Scene.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef SCENE_HPP
#define SCENE_HPP
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "Factory.hpp"
#include "Matrix.hpp"
#include "Node.hpp"
#include "FileUtility.hpp"
#include "Parser.hpp"
#include "Quaternion.hpp"
#include "Selection.hpp"
#include "Vector.hpp"
using namespace std;


/**
 * @ingroup base
 * @brief
 *     Collection of items that also stores selection and camera information.
 */
class Scene {
	
	public:
		
		Node *last, *root;
		Selection selection;
		Vector position;
		
		Scene(int width=512,
		      int height=512);
		virtual ~Scene();
		void addToLast(Node *node);
		void addToRoot(Node *node);
		void backup();
		void install(Factory *factory);
		void open(const string &filename);
		void prepare();
		void print();
		void reset();
		void rotate(float angle,
		            float x,
		            float y,
		            float z);
		void sortByDepth();
		
		string getFilename() const;
		int getHeight() const;
		Node* getRoot() const;
		Matrix getRotationMatrix() const;
		int getWidth() const;
		void setFilename(const string &filename);
		void setRoot(Node *node);
		void setRotation(float angle,
		                 float x,
		                 float y,
		                 float z);
	
	private:
		
		int height, width;
		map<string,Factory*> factories;
		Parser parser;
		Quaternion rotation;
		string filename;
		
		Node* create(const Tag &tag);
		void parse();
};


inline string Scene::getFilename() const {
	return filename;
}

inline int Scene::getHeight() const {
	return height;
}

inline Node* Scene::getRoot() const {
	return root;
}

inline int Scene::getWidth() const {
	return width;
}

inline void Scene::setFilename(const string &filename) {
	this->filename = filename;
}


#endif
