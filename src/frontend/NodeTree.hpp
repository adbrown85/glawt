/*
 * NodeTree.hpp
 *
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
#ifndef NODETREE_HPP
#define NODETREE_HPP
#include "common.h"
#include <stack>
#include <gtkmm.h>
#include "Node.hpp"
using namespace std;


/* Columns of the tree */
class NodeTreeColumns : public Gtk::TreeModelColumnRecord {
public:
	NodeTreeColumns() {add(address); add(name);}
	Gtk::TreeModelColumn<int> address;
	Gtk::TreeModelColumn<string> name;
};


/** @brief Hierarchy of text.
 * @ingroup frontend
 */
class NodeTree {
public:
	static NodeTreeColumns columns;
public:
	NodeTree();
	void append(Node *node);
	Glib::RefPtr<Gtk::TreeStore> getModel() const;
	void pop();
	void print();
	void push();
	Gtk::TreeModel::iterator search(Node *node);
	Gtk::TreeModel::iterator search(Node *node,
	                                Gtk::TreeModel::iterator row,
	                                Gtk::TreeModel::iterator pEnd);
protected:
	void appendBaseRow(Node *node);
	void appendChildRow(Node *node);
	void print(const Gtk::TreeModel::Row &row, int depth);
private:
	Glib::RefPtr<Gtk::TreeStore> model;
	stack<Gtk::TreeModel::iterator> parents;
	Gtk::TreeModel::iterator current;
};
inline Glib::RefPtr<Gtk::TreeStore> NodeTree::getModel() const {return model;}


#endif
