/*
 * Extensions.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLAWT_EXTENSIONS_HPP
#define GLAWT_EXTENSIONS_HPP
#include "glawt_common.h"
#ifdef HAVE_GLUT
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif
#ifdef HAVE_GTK
#include <gdkmm/gl/query.h>
#endif
using namespace std;


/* Functions to load explicitly */
typedef void (*PFNGLBINDFRAGDATALOCATIONGANPROC)(GLuint,GLuint,const char*);
typedef GLint (*PFNGLGETFRAGDATALOCATIONGANPROC)(GLuint,const char*);
extern PFNGLBINDFRAGDATALOCATIONGANPROC glBindFragDataLocationGAN;
extern PFNGLGETFRAGDATALOCATIONGANPROC glGetFragDataLocationGAN;

/** @brief Exception thrown while loading an extension. */
class ExtensionException : public exception {
public:
	ExtensionException() {};
	ExtensionException(const ExtensionException &e) : message(e.getMessage()) {}
	ExtensionException(const string &message) : message(message) {}
	~ExtensionException() throw() {}
	string getMessage() const {return message;}
	const char* what() const throw() {return message.c_str();}
private:
	string message;
};

/** @brief Utility for loading OpenGL extensions.
 * @ingroup core
 */
class Extensions {
public:
	static void load();
protected:
	static void loadGLEW();
	static void loadGLUT();
	static void loadGTK();
};


#endif
