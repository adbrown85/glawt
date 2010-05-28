/*
 * TextTree.hpp
 *
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
#ifndef TEXTTREE_HPP
#define TEXTTREE_HPP
#include "common.h"
#include <stack>
#include <gtkmm.h>
using namespace std;


/* Columns of the tree */
class TextTreeColumns : public Gtk::TreeModelColumnRecord {
public:
	TextTreeColumns() {add(text);}
	Gtk::TreeModelColumn<string> text;
};


/** @brief Hierarchy of text.
 * @ingroup frontend
 */
class TextTree {
public:
	static TextTreeColumns columns;
public:
	TextTree();
	void add(const string &text);
	Glib::RefPtr<Gtk::TreeStore> getModel() const {return model;}
	void pop();
	void print();
	void push();
protected:
	void addBaseRow(const string &text);
	void addChildRow(const string &text);
	void print(const Gtk::TreeModel::Row &row, int depth);
private:
	Glib::RefPtr<Gtk::TreeStore> model;
	stack<Gtk::TreeModel::iterator> parents;
	Gtk::TreeModel::iterator rowIter;
};


#endif
