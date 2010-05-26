/*
 * Inspector.hpp
 *
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
#ifndef INSPECTOR_HPP
#define INSPECTOR_HPP
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
	Gtk::TreeView& getTreeView();
	RefPtr<Gtk::TreeStore> getTreeModel();
	Node* getNode() const;
	void setNode(Node *node);
	void update();
	Gtk::CellRendererText* getRenderer(const string &name);
private:
	Gtk::ScrolledWindow scroller;
	AttributeTree tree;
	Gtk::TreeView view;
	Node *node;
};
inline Node* NodeView::getNode() const {return node;}
inline void NodeView::setNode(Node *n) {node = n;}
inline Gtk::TreeView& NodeView::getTreeView() {return view;}
inline RefPtr<Gtk::TreeStore> NodeView::getTreeModel() {return tree.getModel();}


/** Pane showing scene overview and node details. */
class Inspector : public Gtk::VPaned {
public:
	Inspector();
	void onCursorChange();
	void onEditValue(const string& path, const string& text);
	void setScene(Scene *scene);
	void setCanvas(Canvas *canvas);
	void update();
private:
	Scene *scene;
	Canvas *canvas;
	NodeView nodeView;
	SceneView sceneView;
};
inline void Inspector::setScene(Scene *s) {scene = s;}
inline void Inspector::setCanvas(Canvas *c) {canvas = c;}

#endif
