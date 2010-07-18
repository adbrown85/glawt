/*
 * NodeTree.cpp
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
#include "NodeTree.hpp"
#ifdef HAVE_GTK
NodeTreeColumns NodeTree::columns;


NodeTree::NodeTree() {
	
	model = Gtk::TreeStore::create(columns);
}


void NodeTree::append(Node *node) {
	
	// Add as base or child row
	if (parents.empty()) {
		current = model->append();
	} else {
		current = model->append((parents.top())->children());
	}
	(*current)[columns.address] = reinterpret_cast<int>(node);
	(*current)[columns.name] = node->getClassName();
}


void NodeTree::pop() {
	
	if (parents.empty()) {
		throw "[NodeTree] Cannot pop with nothing pushed.";
	}
	
	parents.pop();
	if (!parents.empty()) {
		current = parents.top();
	}
}


void NodeTree::print() {
	
	Gtk::TreeModel::Children rows=model->children();
	Gtk::TreeModel::Children::iterator it;
	
	for (it=rows.begin(); it!=rows.end(); ++it) {
		print(*it, 0);
	}
}


void NodeTree::print(const Gtk::TreeModel::Row &row, int depth) {
	
	Gtk::TreeModel::Children children=row.children();
	Gtk::TreeModel::Children::iterator it;
	Node *node;
	int address;
	string name;
	
	// Print self
	address = row[columns.address];
	name = row[columns.name];
	node = reinterpret_cast<Node*>(address);
	for (int i=0; i<depth; ++i)
		cout << "  ";
	cout << node->getClassName() << endl;
	
	// Print children
	depth += 1;
	for (it=children.begin(); it!=children.end(); ++it) {
		print(*it, depth);
	}
}


void NodeTree::push() {
	
	parents.push(current);
}


Gtk::TreeModel::iterator NodeTree::search(Node *node) {
	
	Gtk::TreeModel::Children rows=model->children();
	Gtk::TreeModel::Children::iterator it;
	Gtk::TreeModel::iterator result;
	
	for (it=rows.begin(); it!=rows.end(); ++it) {
		result = search(node, it, rows.end());
		if (result) {
			return result;
		}
	}
	return rows.end();
}


Gtk::TreeModel::iterator NodeTree::search(Node *node,
                                          Gtk::TreeModel::iterator row,
                                          Gtk::TreeModel::iterator pEnd) {
	
	Gtk::TreeModel::Children rows=row->children();
	Gtk::TreeModel::iterator result;
	Gtk::TreeModel::Children::iterator it;
	int address;
	
	// Check self
	address = (*row)[columns.address];
	if (address == reinterpret_cast<int>(node)) {
		return row;
	}
	
	// Check children
	for (it=rows.begin(); it!=rows.end(); ++it) {
		result = search(node, it, rows.end());
		if (result) {
			return result;
		}
	}
	return pEnd;
}


#endif // HAVE_GTK

