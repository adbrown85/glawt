/*
 * NodeTree.hpp
 *
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
#ifndef NODETREE_HPP
#define NODETREE_HPP
#include "common.h"
#ifdef HAVE_GTK
#include <stack>
#include <gtkmm.h>
#include "Node.hpp"
using namespace std;
using Glib::RefPtr;


/* Columns of the tree */
class NodeTreeColumns : public Gtk::TreeModelColumnRecord {
public:
	NodeTreeColumns() {add(address); add(name);}
	Gtk::TreeModelColumn<int> address;
	Gtk::TreeModelColumn<string> name;
};


/** @brief Hierarchy of nodes.
 * @ingroup gui
 */
class NodeTree {
public:
	static NodeTreeColumns columns;
public:
	NodeTree();
	void append(Node *node);
	RefPtr<Gtk::TreeStore> getModel() const;
	void pop();
	void print();
	void push();
	Gtk::TreeModel::iterator search(Node *node);
	Gtk::TreeModel::iterator search(Node *node,
	                                Gtk::TreeModel::iterator row,
	                                Gtk::TreeModel::iterator pEnd);
protected:
	void print(const Gtk::TreeModel::Row &row, int depth);
private:
	RefPtr<Gtk::TreeStore> model;
	stack<Gtk::TreeModel::iterator> parents;
	Gtk::TreeModel::iterator current;
};
inline RefPtr<Gtk::TreeStore> NodeTree::getModel() const {return model;}


#endif // HAVE_GTK
#endif
