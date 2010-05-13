/*
 * NodeNotifier.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "NodeNotifier.hpp"


class FakeNodeListener : public NodeListener {
public:
	FakeNodeListener(const string &name) {this->name = name;}
	virtual void onNodeEvent(NodeEvent &event);
private:
	string name;
};


void FakeNodeListener::onNodeEvent(NodeEvent &event) {
	
	cout << "  " << name << ":"
	     << " " << event.getType() 
	     << " " << event.getSource() << endl;
}


class NodeNotifierTest {
public:
	void setUp();
	void testFireEvent();
private:
	Node *node;
	NodeNotifier notifier;
};


void NodeNotifierTest::setUp() {
	
	Tag tag;
	
	cout << "Setting up..." << endl;
	
	// Node
	tag.setName("FakeNode");
	node = new Node(tag);
	cout << "  Node address: " << node << endl;
	
	// Listeners
	notifier.addListener(new FakeNodeListener("final"), NodeEvent::FINALIZE);
	notifier.addListener(new FakeNodeListener("assoc"), NodeEvent::ASSOCIATE);
	notifier.addListener(new FakeNodeListener("modif"), NodeEvent::MODIFY);
}


void NodeNotifierTest::testFireEvent() {
	
	cout << "\nFiring events..." << endl;
	
	notifier.fireEvent(NodeEvent(node, NodeEvent::FINALIZE)); 
	notifier.fireEvent(NodeEvent(node, NodeEvent::ASSOCIATE)); 
	notifier.fireEvent(NodeEvent(node, NodeEvent::MODIFY)); 
}


int main(int argc,
         char *argv[]) {
	
	NodeNotifierTest test;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "NodeNotifier" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	test.setUp();
	test.testFireEvent();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "NodeNotifier" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}

