/*
 * Application.hpp
 *     Application for visualizing volumes.
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#include <cstdlib>
#include <fstream>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "Box.hpp"
#include "Scene.hpp"
#include "Shader.hpp"
#include "Uniform.hpp"
#include "Vector.hpp"



class Application {
	
	
	public :
		
		Application();
		~Application();
		
		void parse(int argc,
		           char *argv[]);
		void print();
		void start();
	
	
	private :
		
		Scene *scene;
		std::vector<Item*> items;
		std::vector<Shader*> shaders;
		std::vector<Uniform*> uniforms;
		
		void handleItems(std::string filename);
		void handleShader(std::string filename,
		                  GLenum type);
		void handleUniforms(std::string filename);
		void readItem(std::ifstream &file);
		void readUniform(std::ifstream &file);
};


#endif
