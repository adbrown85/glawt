/*
 * Application.cpp
 *     Application for visualizing volumes.
 * 
 * Author
 *     Andrew Brown
 */
#include "Application.hpp"



/**
 * Creates a new Application object.
 */
Application::Application() {
	
	// Initialize
	scene = NULL;
}



/**
 * Cleans up memory allocated by the Application.
 */
Application::~Application() {
	
	// Deallocate
	if (scene != NULL)
		delete scene;
	for (int i=0; i<items.size(); i++)
		delete items[i];
	for (int i=0; i<shaders.size(); i++)
		delete shaders[i];
	for (int i=0; i<uniforms.size(); i++)
		delete uniforms[i];
}



/**
 * Loads items from a file.
 * 
 * @param file
 *     Filename of the file with item descriptions.
 */
void Application::handleItems(std::string filename) {
	
	std::ifstream file;
	
	// Load items from the file
	file.open(filename.c_str());
	readItem(file);
	while (file)
		readItem(file);
}



/**
 * Loads a new Shader from a file and stores it.
 * 
 * @param file
 *     Shader's source file.
 * @param type
 *     Type of shader.
 */
void Application::handleShader(std::string filename,
                               GLenum type) {
	
	Shader *shader;
	
	// Load the shader, add it to the list
	shader = new Shader(type);
	shader->load(filename);
	shaders.push_back(shader);
}



/**
 * Loads uniform variables from a file.
 * 
 * @param file
 *     Filename of the file with uniform variable descriptions.
 */
void Application::handleUniforms(std::string filename) {
	
	std::ifstream file;
	
	// Load uniforms from the file
	file.open(filename.c_str());
	readUniform(file);
	while (file)
		readUniform(file);
}



/**
 * Parses the command line arguments.
 * 
 * @param argc
 *     Number of arguments.
 * @param argv
 *     Array of arguments as C-strings.
 */
void Application::parse(int argc,
                        char *argv[]) {
	
	// Handle arguments
	if (argc == 1 || argc % 2 == 0) {
		std::cerr << "Usage: " << argv[0]
		                       << " {-{f|i|u|v} filename} ..." << std::endl;
		std::cerr << "  f Fragment shader" << std::endl;
		std::cerr << "  i Items in scene" << std::endl;
		std::cerr << "  u Uniform variables" << std::endl;
		std::cerr << "  v Vertex shader" << std::endl;
		exit(1);
	}
	for (int i=1; i<argc; i++) {
		if (strcmp(argv[i], "-i") == 0)
			handleItems(argv[++i]);
		if (strcmp(argv[i], "-u") == 0)
			handleUniforms(argv[++i]);
		else if (strcmp(argv[i], "-f") == 0)
			handleShader(argv[++i], GL_FRAGMENT_SHADER);
		else if (strcmp(argv[i], "-v") == 0)
			handleShader(argv[++i], GL_VERTEX_SHADER);
	}
}



/**
 * Prints some information about the scene.
 */
void Application::print() {
	
	// Print files loaded
	std::cout << "Items: " << std::endl;
	for (int i=0; i<items.size(); i++)
		std::cout << "  " << *items[i] << std::endl;
	std::cout << "Shaders: " << std::endl;
	for (int i=0; i<shaders.size(); i++)
		std::cout << "  " << shaders[i]->getFilename() << std::endl;
	std::cout << "Uniforms: " << std::endl;
	for (int i=0; i<uniforms.size(); i++)
		std::cout << "  " << *uniforms[i] << std::endl;
}



/**
 * Reads a single item in from a file.
 * 
 * @param file
 *     Input file stream to read from.
 */
void Application::readItem(std::ifstream &file) {
	
	float size;
	Item *item;
	Vector position;
	std::string style, type;
	
	// Read values
	file >> type
	     >> size
	     >> style
	     >> position.x
	     >> position.y
	     >> position.z;
	if (file && type.compare("Box") == 0) {
		item = new Box(size);
		item->setPosition(position.x, position.y, position.z);
		if (style.compare("2D") == 0)
			item->setStyle(GL_TEXTURE_2D);
		else
			item->setStyle(GL_TEXTURE_3D);
		items.push_back(item);
	}
}



/**
 * Reads a single uniform variable from a file.
 * 
 * @param file
 *     Input file stream to read from.
 */
void Application::readUniform(std::ifstream &file) {
	
	float value;
	std::string name, type;
	Uniform *uniform;
	
	// Read, make, add
	file >> name
	     >> type
	     >> value;
	if (file) {
		uniform = new Uniform(name, type, value);
		uniforms.push_back(uniform);
	}
}



/**
 * Starts the Application.
 */
void Application::start() {
	
	Item *item;
	
	// Create scene
	scene = new Scene("Application", 640, 480);
	
	// Add items and shaders
	for (int i=0; i<items.size(); i++)
		scene->add(items[i]);
	for (int i=0; i<shaders.size(); i++)
		scene->add(shaders[i]);
	for (int i=0; i<uniforms.size(); i++)
		Shader::add(*uniforms[i]);
	
	// Start scene
	scene->start();
}



/**
 * Simple test program.
 */
int main(int argc, char **argv) {
	
	Application application;
	
	// Handle arguments
	application.parse(argc, argv);
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Application" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	application.print();
	application.start();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Application" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}
