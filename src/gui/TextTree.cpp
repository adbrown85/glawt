/*
 * TextTree.cpp
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
#include "TextTree.hpp"
TextTreeColumns TextTree::columns;


TextTree::TextTree() {
	
	model = Gtk::TreeStore::create(columns);
}


void TextTree::add(const string &text) {
	
	// Add as base or child row
	if (parents.empty()) {
		addBaseRow(text);
	} else {
		addChildRow(text);
	}
}


void TextTree::addBaseRow(const string &text) {
	
	Gtk::TreeModel::Row row;
	
	rowIter = model->append();
	row = *rowIter;
	row[columns.text] = text;
}


void TextTree::addChildRow(const string &text) {
	
	Gtk::TreeModel::Row childRow, parentRow;
	
	parentRow = *(parents.top());
	rowIter = model->append(parentRow.children());
	childRow = *rowIter;
	childRow[columns.text] = text;
}


void TextTree::pop() {
	
	if (parents.empty()) {
		throw "[TextTree] Cannot pop with nothing pushed.";
	}
	
	parents.pop();
	if (!parents.empty()) {
		rowIter = parents.top();
	}
}


void TextTree::print() {
	
	Gtk::TreeModel::Children rows=model->children();
	Gtk::TreeModel::Children::iterator it;
	
	for (it=rows.begin(); it!=rows.end(); ++it) {
		print(*it, 0);
	}
}


void TextTree::print(const Gtk::TreeModel::Row &row,
                     int depth) {
	
	Gtk::TreeModel::Children children=row.children();
	Gtk::TreeModel::Children::iterator it;
	string text;
	
	// Print self
	text = row[columns.text];
	for (int i=0; i<depth; ++i) {
		cout << "  ";
	}
	cout << text << endl;
	
	// Print children
	depth += 1;
	for (it=children.begin(); it!=children.end(); ++it) {
		print(*it, depth);
	}
}


void TextTree::push() {
	
	parents.push(rowIter);
}

