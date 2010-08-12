/*
 * UniformFloatArray.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "UniformFloatArray.hpp"


/** Initialize attributes.
 * 
 * @throws NodeException if value for @e as attribute not recognized.
 */
UniformFloatArray::UniformFloatArray(const Tag &tag) : Uniform(tag) {
	
	// Retrieve from tag
	tag.get("as", as, true, true);
	tag.get("of", of, true, false);
	
	// Other attributes
	values = NULL;
	count = 0;
	calculator = NULL;
	
	// Calculation
	calculation = Calculator::getCalculationFor(as);
	if (calculation == Calculation::NONE) {
		NodeException e(tag);
		e << "[UniformFloatArray] Value for 'as' not recognized.";
		throw e;
	}
}


/** Destroys the values array. */
UniformFloatArray::~UniformFloatArray() {
	
	if (values != NULL)
		delete[] values;
	if (calculator != NULL)
		delete calculator;
}


/** Calculates and then sets the values in the program. */
void UniformFloatArray::apply() {
	
	// Check if not in program
	if (!hasLocation())
		return;
	
	// Set values in program
	calculator->setCanvas(getCanvas());
	calculator->run(calculation, count, values);
	glUniform1fv(getLocation(), count, values);
	fireEvent(NodeEvent(this, NodeEvent::MODIFY));
}


/** Makes connections to other nodes. */
void UniformFloatArray::associate() {
	
	Uniform::associate();
	
	// Find group and shapes
	findGroup();
	findShapes();
	
	// Create calculator
	if (calculator == NULL) {
		calculator = new Calculator(shapes);
	}
}


/** Finds the group named by @e of.
 * 
 * @throws NodeException if group cannot be found.
 */
void UniformFloatArray::findGroup() {
	
	// Find group
	group = Group::find(this, of);
	if (group == NULL) {
		NodeException e(tag);
		e << "[UniformFloatArray] Could not find group.";
		throw e;
	}
}


/** Finds all the shapes in the group. */
void UniformFloatArray::findShapes() {
	
	Node *node;
	Node::iterator it;
	queue<Node*> Q;
	Shape *shape;
	
	// Search for shapes in the group
	Q.push(group);
	while (!Q.empty()) {
		node = Q.front();
		shape = dynamic_cast<Shape*>(node);
		if (shape != NULL)
			shapes.insert(shape);
		for (it=node->begin(); it!=node->end(); ++it)
			Q.push((*it));
		Q.pop();
	}
}


/** Allocates the values array.
 * 
 * @throws NodeException if the size of the array cannot be determined.
 */
void UniformFloatArray::finalize() {
	
	Uniform::finalize();
	
	map<string,UniformInfo> catalog;
	map<string,UniformInfo>::iterator it;
	
	// Check if already finalized
	if (values != NULL)
		return;
	
	// Find out how big the array is
	catalog = Uniform::getUniformsFor(getProgram());
	it = catalog.find(getName());
	if (it != catalog.end()) {
		count = it->second.count;
	} else {
		NodeException e(tag);
		e << "[UniformFloatArray] Could not get size of array.";
		throw e;
	}
	
	// Allocate
	values = new GLfloat[count];
}


/** Searches a subtree for UniformFloatArray nodes. */
set<UniformFloatArray*> UniformFloatArray::search(Node *node) {
	
	Node::iterator it;
	queue<Node*> Q;
	UniformFloatArray *ufa;
	set<UniformFloatArray*> ufas;
	
	Q.push(node);
	while (!Q.empty()) {
		node = Q.front();
		ufa = dynamic_cast<UniformFloatArray*>(node);
		if (ufa != NULL)
			ufas.insert(ufa);
		for (it=node->begin(); it!=node->end(); ++it)
			Q.push((*it));
		Q.pop();
	}
	return ufas;
}


/** @return String made from the node's attributes. */
string UniformFloatArray::toString() const {
	
	ostringstream stream;
	
	stream << Uniform::toString();
	if (!as.empty())
		stream << " as='" << as << "'";
	if (!of.empty())
		stream << " of='" << of << "'";
	stream << " count='" << count << "'"
	       << " shapes='" << shapes.size() << "'";
	for (int i=0; i<count; ++i)
		stream << " values[" << i << "]='" << values[i] << "'";
	return stream.str();
}

