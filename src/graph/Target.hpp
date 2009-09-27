/*
 * Target.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TARGET_HPP
#define TARGET_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include "Node.hpp"
#include "Framebuffer.hpp"
#include "Texture2D.hpp"
using namespace std;



class Target : public Node {
	
	
	public :
		
		Target();
	
	
	protected:
		
		void associate();
		void finalize();
	
	
	private:
		
		GLuint framebufferHandle, textureHandle, unit;
		int width, height;
		string link;
};


#endif
