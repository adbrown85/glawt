/*
 * Shader.cpp
 *     Handles loading and installing GLSL shaders.
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#include "Shader.hpp"
std::vector<Uniform> Shader::uniforms;
GLuint Shader::program=0;



/**
 * Creates a Shader and initializes its values.
 * 
 * @param type
 *     Type of the shader.  Either GL_FRAGMENT_SHADER or GL_VERTEX_SHADER.
 */
Shader::Shader(GLenum type) {
	
	// Initialize
	count = 0;
	source = NULL;
	this->type = type;
}



/**
 * Cleans up the memory allocated by the Shader object.
 */
Shader::~Shader() {
	
	// Clean up
	if (source != NULL)
		delete[] source;
}



/**
 * Adds a uniform variable to the shader program.
 * 
 * @param uniform
 *     Uniform variable.
 */
void Shader::add(Uniform uniform) {
	
	// Add
	uniforms.push_back(uniform);
}



/**
 * Compiles the shader.  Prints the log and exits if unsuccessful.
 */
void Shader::compile() {
	
	GLint compiled=0;
	
	// Create and compile shader
	name = glCreateShader(type);
	glShaderSource(name, count, source, NULL);
	glCompileShader(name);
	
	// Attach shader to program if successful
	log(name);
	glGetShaderiv(name, GL_COMPILE_STATUS, &compiled);
	if (compiled) {
		if (program == 0)
			program = glCreateProgram();
		glAttachShader(program, name);
	}
	else
		exit(1);
}



/**
 * Returns a copy of the source's filename.
 */
std::string Shader::getFilename() {
	
	return filename;
}



/**
 * Attaches the shader to the program.  Links the program and uses it.  Prints 
 * the log and exits if unsuccessful.  Also sets any uniform variables stored 
 * in the uniforms vector.
 */
void Shader::link() {
	
	GLint linked=0;
	
	// Link program
	glLinkProgram(program);
	
	// Use program if successful
	log(program);
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if (linked == GL_TRUE)
		glUseProgram(program);
	else
		exit(1);
	
	// Set initial uniform variables
	for (int i=0; i<uniforms.size(); i++)
		setUniform(uniforms[i]);
}



/**
 * Loads the file specified by filename into the Shader's source array.
 * 
 * @param filename
 *     Path to the file.
 */
void Shader::load(std::string filename) {
	
	std::ifstream inFile;
	std::string line;
	
	// Initialize
	this->filename = filename;
	if (source != NULL) {
		delete[] source;
		source = NULL;
	}
	
	// Load file into source array
	inFile.open(filename.c_str());
	getline(inFile, line);
	while (inFile) {
		lines.push_back(line);
		getline(inFile, line);
	}
	count = lines.size();
	source = new const char*[count];
	for (int i=0; i<count; i++)
		source[i] = lines[i].c_str();
}



/**
 * Prints the log.
 * 
 * @param name
 *     Name of the shader or program object to print the log for.
 */
void Shader::log(GLuint name) {
	
	GLchar *log;
	GLint length=0, returned=0;
	
	// Get length
	if (glIsProgram(name))
		glGetProgramiv(name, GL_INFO_LOG_LENGTH, &length);
	else
		glGetShaderiv(name, GL_INFO_LOG_LENGTH, &length);
	
	// Print the log
	log = new GLchar[length+1];
	if (glIsProgram(name))
		glGetProgramInfoLog(name, length, &returned, log);
	else
		glGetShaderInfoLog(name, length, &returned, log);
	log[returned] = '\0';
	if (strlen(log) != 0)
		std::cerr << log << std::endl;
	
	// Finish
	delete[] log;
}



/**
 * Prints the file stored in the source array.
 */
void Shader::print() const {
	
	// Print
	for (int i=0; i<count; i++)
		std::cout << source[i] << std::endl;
}



/**
 * Sets a uniform variable in a shader program.  Needs to be called after the 
 * program is linked.
 * 
 * @param name
 *     Name of the uniform variable.
 * @param value
 *     Value for the variable.
 */
void Shader::setUniform(std::string name,
                        int type,
                        GLfloat value) {
	
	GLint location;
	
	// Look up location, set value
	location = glGetUniformLocation(program, name.c_str());
	if (location != -1) {
		switch (type) {
			case UNIFORM_FLOAT :
				glUniform1f(location, value);
				break;
			case UNIFORM_INT :
				glUniform1i(location, value);
				break;
		}
	}
}



/**
 * Sets a uniform variable in a shader program.  Needs to be called after the 
 * program is linked.
 * 
 * @param uniform
 *     Uniform variable.
 */
void Shader::setUniform(const Uniform& uniform) {
	
	// Set uniform
	setUniform(uniform.getName(),
	           uniform.getType(),
	           uniform.getValue());
}



/**
 * Simple test program.
 */
/*
void display(void) {
	
	// Initialize
	glClear(GL_COLOR_BUFFER_BIT);
	glTranslatef(0.0, 0.0, -2);
	
	// Draw
	glBegin(GL_QUADS); {
		glTexCoord2f(1.0, 1.0);
		glVertex3f( 1.0,  1.0, 0.0);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(-1.0,  1.0, 0.0);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-1.0, -1.0, 0.0);
		glTexCoord2f(1.0, 0.0);
		glVertex3f( 1.0, -1.0, 0.0);
	} glEnd();
	
	// Finish
	glFlush();
}
int main(int argc, char **argv) {
	
	using namespace std;
	Shader shader(GL_FRAGMENT_SHADER);
	string filename;
	
	// Handle arguments
	if (argc == 1) {
		cerr << "Usage: " << argv[0] 
		                  << " <filename>" << endl;
		return 1;
	}
	filename = argv[1];
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Shader" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	shader.load(filename);
	shader.print();
	
	// Display
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Shader Test");
	glViewport(0, 0, 640, 480);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, 1.33, 0.1, 1000);
	
	// Install
	shader.compile();
	shader.install();
	
	// Activate
	glutDisplayFunc(display);
	glutMainLoop();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Shader" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}
*/
