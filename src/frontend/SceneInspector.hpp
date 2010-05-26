/*
 * SceneInspector.hpp
 *
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
#ifndef SCENEINSPECTOR_HPP
#define SCENEINSPECTOR_HPP
#include <cstdlib>
#include <iostream>
#include <gtkmm.h>
#include <map>
#include <string>
#include "NodeTree.hpp"
#include "AttributeTree.hpp"
#include "Scene.hpp"
using namespace std;


/** Tree view made up of the nodes in the scene. */
class SceneView : public Gtk::VBox {
public:
	SceneView();
	Gtk::TreeView& getTreeView();
	void onRowChange(const Gtk::TreeModel::Path&, Gtk::TreeViewColumn*);
	void setScene(Scene *scene);
	void update();
protected:
	void build(Node *node);
private:
	Gtk::ScrolledWindow scroller;
	NodeTree tree;
	Gtk::TreeView view;
	Scene *scene;
};
inline void SceneView::setScene(Scene *s) {scene = s;}
inline Gtk::TreeView& SceneView::getTreeView() {return view;}


/** Tree view to examine a single node. */
class NodeView : public Gtk::VBox {
public:
	NodeView();
	void setNode(Node *node);
	void update();
private:
	Gtk::ScrolledWindow scroller;
	AttributeTree tree;
	Gtk::TreeView view;
	Node *node;
};
inline void NodeView::setNode(Node *n) {node = n;}


/** Pane showing scene overview and node details. */
class SceneInspector : public Gtk::VPaned {
public:
	SceneInspector();
	void onCursorChange();
	void setScene(Scene *scene);
	void update();
private:
	Scene *scene;
	NodeView nodeView;
	SceneView sceneView;
};
inline void SceneInspector::setScene(Scene *s) {scene = s;}

#endif
