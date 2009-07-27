/*
 * Factory.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Factory.hpp"



/**
 * Makes a Factory that will create items in a certain scene.
 * 
 * @param scene
 *	 Pointer to a Scene object.
 */
Factory::Factory(Scene *scene) {
	
	// Initialize
	this->scene = scene;
	initContainers();
}



/**
 * Creates a shader program and adds it to the scene.
 */
void Factory::createProgram(Tag &tag) {
	
	Program *program;
	
	// Create
	program = new Program();
	
	// Add to scene
	current->addChild(program);
	current = program;
}



/**
 * Creates a shader and adds it to the scene.
 */
void Factory::createShader(Tag &tag) {
	
	Shader *shader;
	string filename, type;
	
	// Create
	tag.get("type", type);
	tag.get("file", filename);
	shader = new Shader(type, filename);
	
	// Add to scene
	current->addChild(shader);
}



/**
 * Creates a shape and adds it to the scene.
 */
void Factory::createShape(Tag &tag) {
	
	float size;
	Shape *shape;
	string type;
	
	// Create
	tag.get("size", size);
	tag.get("type", type);
	if (type.compare("Box") == 0)
		shape = new Box(size);
	else
		throw "Shape type not supported.";
	
	// Add to scene
	current->addChild(shape);
}



/**
 * Creates a Texture and adds it to the scene.
 */
void Factory::createTexture(Tag &tag) {
	
	string filename, name, type;
	Texture *texture;
	
	// Create
	tag.get("file", filename);
	tag.get("type", type);
	tag.get("name", name, false);
	if (type[0] == '2')
		texture = new Texture2D(filename, name);
	else if (type[0] == '3')
		texture = new Texture2D(filename, name);
	else
		throw "Gander,Factory: Texture type not supported.";
	
	// Add to scene
	current->addChild(texture);
	current = texture;
}



/**
 * Creates a Translation and adds it to the scene.
 */
void Factory::createTranslation(Tag &tag) {
	
	float x, y, z;
	Translation *translation;
	
	// Create
	tag.get("x", x);
	tag.get("y", y);
	tag.get("z", z);
	translation = new Translation(x, y, z);
	
	// Add to scene
	current->addChild(translation);
	current = translation;
}



/**
 * Creates a Uniform variable and adds it to the scene.
 */
void Factory::createUniform(Tag &tag) {
	
	float value;
	string link, name, type;
	Uniform *uniform;
	
	// Create
	tag.get("type", type);
	tag.get("name", name);
	tag.get("value", value, false);
	tag.get("link", link, false);
	uniform = new Uniform(type, name, value, link);
	
	// Add to scene
	current->addChild(uniform);
	current = uniform;
}



/**
 * Creates items from XML tags.
 * 
 * @param tags
 *	 Reference to a collection of tags.
 */
void Factory::process(vector<Tag> &tags) {
	
	vector<Tag>::iterator ti;
	
	// Initialize current node
	current = &(scene->rootNode);
	
	// Look through tags
	for (ti=tags.begin(); ti!=tags.end(); ++ti) {
		
		// Step back on closing container tags
		if (ti->closing && isContainer(ti->name))
			current = current->getParent();
		
		// Create items
		else if (ti->name.compare("translate") == 0)
			createTranslation(*ti);
		else if (ti->name.compare("shape") == 0)
			createShape(*ti);
		else if (ti->name.compare("texture") == 0)
			createTexture(*ti);
		else if (ti->name.compare("program") == 0)
			createProgram(*ti);
		else if (ti->name.compare("shader") == 0)
			createShader(*ti);
		else if (ti->name.compare("uniform") == 0)
			createUniform(*ti);
	}
}



/**
 * Initializes which tags should be considered containers.
 */
void Factory::initContainers() {
	
	// Add each to set
	containers.insert("program");
	containers.insert("texture");
	containers.insert("translate");
	containers.insert("uniform");
}



/**
 * Checks if the name of a tag indicates it should be a container.
 */
bool Factory::isContainer(string name) {
	
	set<string>::const_iterator si;
	
	// Look in containers set
	si = containers.find(name);
	return si != containers.end();
}

