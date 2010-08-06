/*
 * Inspector.hpp
 *
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
#ifndef INSPECTOR_HPP
#define INSPECTOR_HPP
#include "common.h"
#ifdef HAVE_GTK
#include <gtkmm.h>
#include "NodeTree.hpp"
#include "AttributeTree.hpp"
#include "Scene.hpp"
#include "NodeEvent.hpp"
#include "Transformation.hpp"
#include "UniformFloatArray.hpp"
using namespace std;


/* Tree view made up of the nodes in the scene. */
class SceneView : public Gtk::Frame {
public:
	SceneView();
	Gtk::TreeView& getTreeView();
	RefPtr<Gtk::TreeStore> getTreeModel();
	void onRowChange(const Gtk::TreeModel::Path&, Gtk::TreeViewColumn*);
	void onRowCollapsed(const Gtk::TreeModel::iterator&,
	                    const Gtk::TreeModel::Path&);
	void setNode(Node *node);
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
inline RefPtr<Gtk::TreeStore> SceneView::getTreeModel(){return tree.getModel();}


/* Tree view to examine a single node. */
class NodeView : public Gtk::Frame {
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


/** @brief Pane showing scene overview and node details.
 * @ingroup gui
 */
class Inspector : public Gtk::Frame, public NodeListener {
public:
	Inspector();
	void onEditValue(const string& path, const string& text);
	void setScene(Scene *scene);
	void setCanvas(Canvas *canvas);
	void update();
	virtual void onNodeEvent(NodeEvent &event);
	void onNodeSelectionChange();
private:
	Scene *scene;
	Canvas *canvas;
	NodeView nodeView;
	SceneView sceneView;
	Gtk::VPaned pane;
	list<Transformation*> transforms;
};
inline void Inspector::setScene(Scene *s) {scene = s;}
inline void Inspector::setCanvas(Canvas *c) {canvas = c;}

#endif // HAVE_GTK
#endif
