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
 * 
 * Base class for textures of various dimensions.
 * 
 * @see Texture2D
 * @see Texture3D
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
		
		virtual string getFilename() const;
		virtual GLuint getHandle() const;
		virtual string getName() const;
		virtual GLenum getType() const;
		virtual int getUnit() const;
		
		static int getNumberOfActiveUnits();
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


/**
 * @return Path to the file this texture was loaded from.
 */
inline string Texture::getFilename() const {return filename;}


/**
 * @return OpenGL's unique identifier for this texture.
 */
inline GLuint Texture::getHandle() const {return handle;}


/**
 * @return User's unique identifier for this texture.
 */
inline string Texture::getName() const {return name;}


/**
 * @return Type of the texture.
 * 
 * @note Should be one of:
 *   @li @c GL_TEXTURE_1D
 *   @li @c GL_TEXTURE_2D
 *   @li @c GL_TEXTURE_3D
 */
inline GLenum Texture::getType() const {return type;}


/**
 * @return Texture unit holding the texture.
 * 
 * @note Intended to be added to @c GL_TEXTURE0 to be used with OpenGL.
 */
inline int Texture::getUnit() const {return unit;}


/**
 * @return Number of texture units being used.
 */
inline int Texture::getNumberOfActiveUnits() {return active_units.size();}


#endif
