/*
 * Scene.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef SCENE_HPP
#define SCENE_HPP
#include "common.h"
#include <stack>
#include <vector>
#include "Exception.hpp"
#include "Factory.hpp"
#include "Matrix.hpp"
#include "Node.hpp"
#include "Parser.hpp"
#include "Path.hpp"
#include "Quaternion.hpp"
#include "Selection.hpp"
#include "Vector.hpp"
using namespace std;


/** @brief Collection of nodes opened from a file.
 * @ingroup scene
 */
class Scene {
public:
	Scene();
	~Scene();
	void addAllToSelection();
	void addToSelection(Node *node);
	string getFilename() const;
	Node* getRoot() const;
	Selection& getSelection();
	void open(string filename);
	void prepare();
	void removeAllFromSelection();
	void removeFromSelection(Node *node);
	void print();
	void setRoot(Node *node);
protected:
	void verify(Node *node);
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
inline void Scene::addToSelection(Node *node) {selection.add(node);}

/** @return file the scene was opened from */
inline string Scene::getFilename() const {return filename;}

/** @return top-most node in the scene */
inline Node* Scene::getRoot() const {return root;}

/** @return pointers to all the selected nodes in the scene */
inline Selection& Scene::getSelection() {return selection;}

/** Deselects all the nodes in the scene. */
inline void Scene::removeAllFromSelection() {selection.clear();}

/** Deselects a single node in the scene */
inline void Scene::removeFromSelection(Node *node) {selection.remove(node);}

#endif
