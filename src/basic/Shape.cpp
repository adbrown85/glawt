/*
 * Shape.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Shape.hpp"
map<string,GLuint> Shape::buffers;


/** Creates a shape from an XML tag.
 * 
 * @param tag XML tag with attributes for SimpleDrawable.
 * @param traits Structure of shape parameters.
 */
Shape::Shape(const Tag &tag, ShapeTraits traits) : SimpleDrawable(tag) {
	
	list<string>::iterator it;
	VertexAttribute va;
	
	// Copy traits
	this->count = traits.count;
	this->limit = traits.count;
	this->mode = traits.mode;
	this->usage = traits.usage;
	
	// Retrieve from tag
	tag.get("name", name, false, false);
	if (!tag.get("defaults", defaults, false)) {
		defaults = true;
	}
	
	// Other attributes
	this->generated = false;
	
	// Store vertex attributes
	block = count * 3 * sizeof(GLfloat);
	for (it=traits.attributes.begin(); it!=traits.attributes.end(); ++it) {
		va.name = *it;
		va.number = distance(traits.attributes.begin(), it);
		va.offset = va.number * block;
		attributes.push_back(va);
		offsets[va.name] = va.offset;
	}
}


/** Finds a program to bind the shape's vertex attributes to.
 * 
 * @throws NodeException if a program cannot be found.
 */
void Shape::associate() {
	
	SimpleDrawable::associate();
	
	// Find program
	program = Scout<Program>::locate(parent);
	if (program == NULL) {
		NodeException e(tag);
		e << "[Shape] No shader program found to bind attributes to.";
		throw e;
	}
}


void Shape::checkForDefaultUniforms() {
	
	int tally;
	map<string,UniformInfo> uniforms;
	map<string,UniformInfo>::iterator it;
	ostringstream stream;
	Node *node;
	
	// Try to add missing default uniforms
	tally = 0;
	uniforms = Uniform::getUniformsFor(program);
	for (it=uniforms.begin(); it!=uniforms.end(); ++it) {
		if (UniformMatrix::isDefault(it->first, it->second.type)) {
			if (!UniformMatrix::hasChild(this, it->first)) {
				stream.str("");
				stream << "uniform type='mat4' name='" << it->first << "'";
				node = Factory::create(stream.str());
				addChild(node);
				node->associate();
				++tally;
			}
		}
	}
	
	// Confirm
	if (tally > 0) {
		glog << tag.getLocation();
		glog << " [Shape] Added " << tally << " default uniforms." << endl;
	}
}


/** Renders the entire shape. */
void Shape::draw() const {
	
	draw(0, limit);
}


/** Renders part of the shape. */
void Shape::draw(int first, int number) const {
	
	list<VertexAttribute>::const_iterator it;
	
	// Enable buffer and attributes
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	for (it=attributes.begin(); it!=attributes.end(); ++it) {
		glEnableVertexAttribArray(it->location);
		glVertexAttribPointer(it->location,                 // index
		                      3,                            // size
		                      GL_FLOAT,                     // type
		                      false,                        // normalized
		                      0,                            // stride
		                      (void*)it->offset);           // pointer
	}
	
	// Draw
	glDrawArrays(mode, first, number);
	
	// Disable buffer and attributes
	for (it=attributes.begin(); it!=attributes.end(); ++it) {
		glDisableVertexAttribArray(it->location);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


/** Loads the vertex data into the vertex buffer so it's ready to render. */
void Shape::finalize() {
	
	list<VertexAttribute>::iterator it;
	
	// Initialize buffer
	if (usage == GL_STATIC_DRAW && isBufferStored(getClassName())) {
		buffer = buffers.find(getClassName())->second;
	} else {
		generate();
	}
	
	// Get locations of attributes in program
	for (it=attributes.begin(); it!=attributes.end(); ) {
		it->location = glGetAttribLocation(program->getHandle(),
		                                   it->name.c_str());
		if (it->location == -1)
			it = attributes.erase(it);
		else
			++it;
	}
	
	// Check for defaults
	if (defaults) {
		checkForDefaultUniforms();
	}
}


/** Generates the vertex buffer for the shape. */
void Shape::generate() {
	
	// Check if already generated
	if (generated)
		return;
	
	// Create and bind
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	
	// Allocate and fill
	glBufferData(GL_ARRAY_BUFFER,                       // target
	             block * attributes.size(),             // size
	             NULL,                                  // data
	             usage);                                // usage
	updateBuffer();
	
	// Store for static shapes
	if (usage == GL_STATIC_DRAW) {
		buffers[getClassName()] = buffer;
	}
	
	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	// Finish
	generated = true;
}


/** @return Number of bytes into the vertex buffer for a vertex attribute. */
GLuint Shape::getOffset(const string &name) const {
	
	map<string,GLuint>::const_iterator it;
	
	it = offsets.find(name);
	if (it != offsets.end()) {
		return it->second;
	} else {
		NodeException e(tag);
		e << "[Shape] Unrecognized vertex attribute name '" << name << "'.";
		throw e;
	}
}


/** Checks if a buffer already exists for a concrete shape. */
bool Shape::isBufferStored(const string &className) {
	
	map<string,GLuint>::iterator it;
	
	it = buffers.find(className);
	return it != buffers.end();
}


/** Sets data in the buffer according to its vertex attribute name.
 * 
 * @param name Name of the vertex attribute
 * @param data Array of values of length <i>count</i>
 */
void Shape::setBufferData(const string &name, GLfloat data[][3]) {
	
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferSubData(GL_ARRAY_BUFFER,                        // target
	                getOffset(name),                        // offset
	                block,                                  // size
	                data);                                  // data
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


/** @return String comprised of the object's attributes. */
string Shape::toString() const {
	
	ostringstream stream;
	
	stream << SimpleDrawable::toString();
	stream << " buffer='" << buffer << "'";
	if (!name.empty()) {
		stream << " name='" << name << "'";
	}
	return stream.str();
}

