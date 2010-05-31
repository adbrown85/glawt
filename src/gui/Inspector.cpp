/*
 * Inspector.cpp
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
#include "Inspector.hpp"
#ifdef HAVE_GTK


/** Sets up the view inside a scrolled window. */
SceneView::SceneView() {
	
	// Fields
	scene = NULL;
	
	// Create the view
	view.set_model(tree.getModel());
	view.append_column("Nodes", tree.columns.name);
	view.set_search_column(tree.columns.name);
	
	// Add the view with scroll bars
	scroller.add(view);
	scroller.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	
	// Connect signals
	view.signal_row_activated().connect(
		sigc::mem_fun(*this,&SceneView::onRowChange)
	); view.signal_row_collapsed().connect(
		sigc::mem_fun(*this,&SceneView::onRowCollapsed)
	);
	
	// Pack
	add(scroller);
	set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
	set_border_width(1);
}


/** Adds all the scene's nodes to the view. */
void SceneView::update() {
	
	Node::iterator it;
	Node *root;
	
	// Validate
	if (scene == NULL) {
		throw Exception("[SceneView] Scene has not been set.");
	}
	
	// Build the tree
	root = scene->getRoot();
	for (it=root->begin(); it!=root->end(); ++it)
		build(*it);
	view.expand_all();
}


/** Adds a node and its children to the scene overview. */
void SceneView::build(Node *node) {
	
	Node::iterator it;
	
	// Add this node
	tree.append(node);
	
	// Add children
	if (node->areChildrenPrintable()) {
		tree.push();
		for (it=node->begin(); it!=node->end(); ++it)
			build(*it);
		tree.pop();
	}
}


/** Collapses or expands the entire subtree on a double click. */
void SceneView::onRowChange(const Gtk::TreeModel::Path& path,
                            Gtk::TreeViewColumn* column) {
	
	
	if (view.row_expanded(path)) {
		view.collapse_row(path);
	} else {
		view.expand_row(path, true);
	}
}


/** Selects the row if the previously selected row was under it. */
void SceneView::onRowCollapsed(const Gtk::TreeModel::iterator& rowIter,
                               const Gtk::TreeModel::Path& rowPath) {
	
	Gtk::TreeModel::iterator selIter;
	
	selIter = view.get_selection()->get_selected();
	if (!selIter) {
		view.get_selection()->select(rowIter);
	}
}


void SceneView::setNode(Node *node) {
	
	Gtk::TreeModel::iterator row;
	
	row = tree.search(node);
	if (row) {
		view.get_selection()->select(row);
		view.scroll_to_row(getTreeModel()->get_path(row));
	}
}


/** Sets up the view inside a scrolled window. */
NodeView::NodeView() {
	
	// Fields
	node = NULL;
	
	// Create the view
	view.set_model(tree.getModel());
	view.append_column("Key", tree.columns.key);
	view.append_column("Value", tree.columns.value);
	view.set_grid_lines(Gtk::TREE_VIEW_GRID_LINES_HORIZONTAL);
	
	// Create the scroller
	scroller.add(view);
	scroller.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	scroller.set_size_request(-1, 150);
	
	// Pack
	add(scroller);
	set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
	set_border_width(1);
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
	try {
		tag = Parser::create(node->toString());
		for (it=tag.begin(); it!=tag.end(); ++it) {
			tree.append(it->first, it->second);
		}
	} catch (Exception &e) {
		glog << "[Inspector] Could not load attributes." << endl;
	}
	view.expand_all();
}


Gtk::CellRendererText* NodeView::getRenderer(const string &name) {
	
	Gtk::CellRenderer *renderer;
	
	if (Text::toLower(name) == "key") {
		renderer = view.get_column_cell_renderer(0);
	} else {
		renderer = view.get_column_cell_renderer(1);
	}
	return (Gtk::CellRendererText*)renderer;
}


Inspector::Inspector() {
	
	Gtk::CellRendererText *renderer;
	
	// Fields
	scene = NULL;
	canvas = NULL;
	
	// Pack
	pane.pack1(sceneView);
	pane.pack2(nodeView, Gtk::SHRINK);
	add(pane);
	set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
	set_border_width(2);
	set_size_request(250, -1);
	
	// Update attributes when node changes
	sceneView.getTreeView().get_selection()->signal_changed().connect(
		sigc::mem_fun(*this,&Inspector::onNodeSelectionChange)
	);
	
	// Make attribute value renderer editable
	renderer = nodeView.getRenderer("value");
	renderer->property_editable() = true;
	renderer->signal_edited().connect(
		sigc::mem_fun(*this, &Inspector::onEditValue)
	);
}


void Inspector::onEditValue(const string& path, const string& text) {
	
	Gtk::TreeModel::iterator it;
	string key, val;
	
	// Figure out what attribute it was
	it = nodeView.getTreeModel()->get_iter(path);
	key = (*it)[AttributeTree::columns.key];
	val = (*it)[AttributeTree::columns.value];
	
	// Check if user even changed it
	if (text == val) {
		return;
	}
	
	// Try to change it
	if (nodeView.getNode()->setAttribute(pair<string,string>(key,text))) {
		nodeView.update();
		if (canvas != NULL) {
			canvas->refresh();
		}
	} else {
		glog << "[Inspector] New value was not accepted by node." << endl;
	}
}


void Inspector::onNodeEvent(NodeEvent &event) {
	
	if (event.getSource() == nodeView.getNode()) {
		nodeView.update();
	} else {
		sceneView.setNode(event.getSource());
	}
}


/** Updates the attribute view if the selected node changes. */
void Inspector::onNodeSelectionChange() {
	
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


void Inspector::update() {
	
	list<Transformation*>::iterator it;
	
	// Validate
	if (scene == NULL) {
		throw Exception("[Inspector] No scene was loaded.");
	} if (canvas == NULL) {
		glog << "[Inspector] No canvas specified to refresh." << endl;
	}
	
	// Update scene view
	sceneView.setScene(scene);
	sceneView.update();
	
	// Listen to transform changes
	transforms = Transformation::search(scene->getRoot());
	for (it=transforms.begin(); it!=transforms.end(); ++it) {
		(*it)->addListener(this);
	}
	
	// Listen to scene selection changes
	scene->getSelection().addListener(this);
}


#endif  // HAVE_GTK
