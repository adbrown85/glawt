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
void Application::handleItems(string filename) {
	
	ifstream file;
	
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
void Application::handleShader(string filename,
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
void Application::handleUniforms(string filename) {
	
	ifstream file;
	
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
		cerr << "Usage: " << argv[0]
		                       << " {-{f|i|u|v} filename} ..." << endl;
		cerr << "  f Fragment shader" << endl;
		cerr << "  i Items in scene" << endl;
		cerr << "  u Uniform variables" << endl;
		cerr << "  v Vertex shader" << endl;
		exit(1);
	}
	for (int i=1; i<argc; i++) {
		if (strcmp(argv[i], "-i") == 0)
			handleItems(argv[++i]);
		else if (strcmp(argv[i], "-u") == 0)
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
	cout << "Items: " << endl;
	for (int i=0; i<items.size(); i++)
		cout << "  " << *items[i] << endl;
	cout << "Shaders: " << endl;
	for (int i=0; i<shaders.size(); i++)
		cout << "  " << shaders[i]->getFilename() << endl;
	cout << "Uniforms: " << endl;
	for (int i=0; i<uniforms.size(); i++)
		cout << "  " << *uniforms[i] << endl;
}



/**
 * Reads a single item in from a file.
 * 
 * @param file
 *     Input file stream to read from.
 */
void Application::readItem(ifstream &file) {
	
	float size;
	Item *item;
	Vector position;
	string style, type;
	
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
void Application::readUniform(ifstream &file) {
	
	float value;
	string name, type;
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
	
	// Create scene and controls
	scene = new Scene(640, 480);
	Interpreter interpreter(scene);
	Keyboard keyboard(&interpreter);
	Menu menu(&interpreter);
	Mouse mouse(&interpreter);
	
	// Add items and shaders
	interpreter.run(Command::OPEN, "some-file.txt");
	for (int i=0; i<items.size(); i++)
		scene->add(items[i]);
	for (int i=0; i<shaders.size(); i++)
		scene->add(shaders[i]);
	for (int i=0; i<uniforms.size(); i++)
		Shader::add(*uniforms[i]);
	
	// Install controls and start display
	Display::install(&menu);
	Display::install(&keyboard);
	Display::install(&mouse);
	Display::start("Display Test Program", scene);
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
