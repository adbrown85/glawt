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
 * @ingroup graph
 * @brief
 *     Collection of nodes opened from a file.
 */
class Scene {
	
	public:
		
		Scene(const string &filename="");
		~Scene();
		void addAllToSelection();
		void addToSelection(Selectable *selectable);
		void open(const string &filename);
		void prepare();
		void print();
		void removeAllFromSelection();
		void removeFromSelection(Selectable *selectable);
		
		string getFilename() const;
		Node* getRoot() const;
		Selection getSelection() const;
		void setFilename(const string &filename);
		void setRoot(Node *node);
	
	private:
		
		Node *root;
		Selection selection;
		string filename;
};


inline void Scene::addAllToSelection() {
	selection.addAll(root);
}

inline void Scene::addToSelection(Selectable *selectable) {
	selection.add(selectable);
}

inline string Scene::getFilename() const {
	return filename;
}

inline Node* Scene::getRoot() const {
	return root;
}

inline Selection Scene::getSelection() const {
	return selection;
}

inline void Scene::setFilename(const string &filename) {
	this->filename = filename;
}

inline void Scene::removeAllFromSelection() {
	selection.clear();
}

inline void Scene::removeFromSelection(Selectable *selectable) {
	selection.remove(selectable);
}

#endif
