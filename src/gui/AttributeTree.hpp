/*
 * AttributeTree.hpp
 *
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
#ifndef ATTRIBUTETREE_HPP
#define ATTRIBUTETREE_HPP
#include "common.h"
#include <stack>
#include <gtkmm.h>
#include "Text.hpp"
using namespace std;
using Glib::RefPtr;


/* Columns of the tree */
class AttributeTreeColumns : public Gtk::TreeModelColumnRecord {
public:
	AttributeTreeColumns() {add(key); add(value);}
	Gtk::TreeModelColumn<string> key;
	Gtk::TreeModelColumn<string> value;
};


/** @brief Hierarchy of text.
 * @ingroup frontend
 */
class AttributeTree {
public:
	static AttributeTreeColumns columns;
public:
	AttributeTree();
	void append(const string &key, const string &value);
	RefPtr<Gtk::TreeStore> getModel() const {return model;}
	void pop();
	void print();
	void push();
protected:
	void print(const Gtk::TreeModel::Row &row, int depth);
private:
	RefPtr<Gtk::TreeStore> model;
	stack<Gtk::TreeModel::iterator> parents;
	Gtk::TreeModel::iterator current;
};


#endif
