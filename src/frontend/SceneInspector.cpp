/*
 * SceneInspector.cpp
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
#include "SceneInspector.hpp"


/** Sets up the view inside a scrolled window. */
SceneView::SceneView() {
	
	// Fields
	scene = NULL;
	
	// Create the view
	view.set_model(tree.getModel());
	view.append_column("Nodes", tree.columns.name);
	
	// Add the view with scroll bars
	scroller.add(view);
	scroller.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	scroller.set_size_request(250, 350);
	
	// Pack
	pack_start(scroller);
}


/** Adds all the scene's nodes to the view. */
void SceneView::update() {
	
	// Validate
	if (scene == NULL) {
		throw Exception("[SceneView] Scene has not been set.");
	}
	
	// Build the tree
	build(scene->getRoot());
	view.expand_all();
}


/** Adds a node and its children to the scene overview. */
void SceneView::build(Node *node) {
	
	Node::iterator it;
	
	// Add this node
	tree.append(node);
	
	// Add children
	tree.push();
	for (it=node->begin(); it!=node->end(); ++it)
		build(*it);
	tree.pop();
}


/** Sets up the view inside a scrolled window. */
NodeView::NodeView() {
	
	// Fields
	node = NULL;
	
	// Create the view
	view.set_model(tree.getModel());
	view.append_column("Attributes", tree.columns.text);
	view.set_grid_lines(Gtk::TREE_VIEW_GRID_LINES_HORIZONTAL);
	
	// Create the scroller
	scroller.add(view);
	scroller.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	scroller.set_size_request(250, 150);
	
	// Pack
	pack_start(scroller);
}


/** Adds all the node's attributes to the view. */
void NodeView::update() {
	
	Tag tag;
	Tag::iterator it;
	
	// Validate
	if (node == NULL) {
		throw Exception("[NodeView] Node has not been set.");
	}
	
	// Initialize
	this->node = node;
	tree.getModel()->clear();
	
	// Build the list
	tag = Parser::create(node->toString());
	for (it=tag.begin(); it!=tag.end(); ++it) {
		tree.add(it->first + "='" + it->second + "'");
	}
	view.expand_all();
}


SceneInspector::SceneInspector() {
	
	// Add parts
	add1(sceneView);
	add2(nodeView);
	
	// Connect signals
	sceneView.getTreeView().signal_row_activated().connect(
		sigc::mem_fun(*this,&SceneInspector::onRowChange)
	); sceneView.getTreeView().signal_cursor_changed().connect(
		sigc::mem_fun(*this,&SceneInspector::onCursorChange)
	);
}


void SceneInspector::update() {
	
	// Update both of the views
	sceneView.setScene(scene);
	sceneView.update();
	nodeView.setNode(scene->getRoot());
	nodeView.update();
}


void SceneInspector::onRowChange(const Gtk::TreeModel::Path& path,
                                 Gtk::TreeViewColumn* column) {
	
	Gtk::TreeView *tv=&(sceneView.getTreeView());
	
	if (tv->row_expanded(path)) {
		tv->collapse_row(path);
	} else {
		tv->expand_row(path, true);
	}
}


void SceneInspector::onCursorChange() {
	
	Glib::RefPtr<Gtk::TreeSelection> selection;
	Gtk::TreeModel::iterator it;
	int address;
	Node *node;
	
	selection = sceneView.getTreeView().get_selection();
	it = selection->get_selected();
	if (it) {
		address = (*it)[NodeTree::columns.address];
		node = reinterpret_cast<Node*>(address);
		nodeView.setNode(node);
		nodeView.update();
	}
}

