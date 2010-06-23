/*
 * AttributeTree.cpp
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
#include "AttributeTree.hpp"
AttributeTreeColumns AttributeTree::columns;


AttributeTree::AttributeTree() {
	
	model = Gtk::TreeStore::create(columns);
}


void AttributeTree::append(const string &key, const string &value) {
	
	// Add as base or child row
	if (parents.empty()) {
		current = model->append();
	} else {
		current = model->append((parents.top())->children());
	}
	(*current)[columns.key] = key;
	(*current)[columns.value] = value;
}


void AttributeTree::pop() {
	
	if (parents.empty()) {
		throw "[AttributeTree] Cannot pop with nothing pushed.";
	}
	
	parents.pop();
	if (!parents.empty()) {
		current = parents.top();
	}
}


void AttributeTree::print() {
	
	Gtk::TreeModel::Children rows=model->children();
	Gtk::TreeModel::Children::iterator it;
	
	for (it=rows.begin(); it!=rows.end(); ++it) {
		print(*it, 0);
	}
}


void AttributeTree::print(const Gtk::TreeModel::Row &row, int depth) {
	
	Gtk::TreeModel::Children children=row.children();
	Gtk::TreeModel::Children::iterator it;
	string key, value;
	
	// Print self
	key = row[columns.key];
	value = row[columns.value];
	cout << Text::indent(depth) << key << " " << value << endl;
	
	// Print children
	depth += 1;
	for (it=children.begin(); it!=children.end(); ++it) {
		print(*it, depth);
	}
}


void AttributeTree::push() {
	
	parents.push(current);
}

