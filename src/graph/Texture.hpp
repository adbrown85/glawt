/*
 * Texture.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include <cassert>
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <typeinfo>
#include "Applicable.hpp"
#include "Node.hpp"
#include "Tag.hpp"
using namespace std;


/**
 * @ingroup graph
 * @brief
 *     OpenGL texture node.
 */
class Texture : public Node,
                public Applicable {
	
	public:
		
		Texture(string name,
		        string filename="");
		Texture(const Tag &tag);
		virtual void apply();
		virtual void associate();
		virtual void remove();
		virtual string toString() const;
		
		virtual string getFilename() const {return filename;}
		virtual GLuint getHandle() {return handle;}
		virtual string getName() const {return name;}
		virtual GLenum getType() const {return type;}
		virtual int getUnit() const {return unit;}
		
		static int getNumberOfActiveUnits() {return active_units.size();}
		static void pause();
		static void restart();
	
	protected:
		
		GLenum type;
		GLuint handle;
		int unit;
		string filename, name;
		
		static vector<GLenum> active_units;
		
		virtual void init();
		virtual void initType() = 0;
};


#endif
