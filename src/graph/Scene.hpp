/*
 * Scene.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef SCENE_HPP
#define SCENE_HPP
#include "common.h"
#include <map>
#include <queue>
#include <stack>
#include <vector>
#include "Exception.hpp"
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
 * @brief Collection of nodes opened from a file.
 */
class Scene {
public:
	Scene();
	~Scene();
	void addAllToSelection();
	void addToSelection(Drawable *drawable);
	string getFilename() const;
	Node* getRoot() const;
	Selection& getSelection();
	void open(string filename);
	void prepare();
	void removeAllFromSelection();
	void removeFromSelection(Drawable *drawable);
	void print();
	void setRoot(Node *node);
protected:
	void associate(Node *node);
	void finalize(Node *node);
private:
	Node *root;
	Selection selection;
	string filename;
};

/** Selects all the nodes in the scene. */
inline void Scene::addAllToSelection() {selection.addAll(root);}

/** Selects a single item in the scene. */
inline void Scene::addToSelection(Drawable *d) {selection.add(d);}

/** @return file the scene was opened from */
inline string Scene::getFilename() const {return filename;}

/** @return top-most node in the scene */
inline Node* Scene::getRoot() const {return root;}

/** @return pointers to all the selected nodes in the scene */
inline Selection& Scene::getSelection() {return selection;}

/** Deselects all the nodes in the scene. */
inline void Scene::removeAllFromSelection() {selection.clear();}

/** Deselects a single node in the scene */
inline void Scene::removeFromSelection(Drawable *d) {selection.remove(d);}

#endif
