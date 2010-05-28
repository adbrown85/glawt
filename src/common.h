/*
 * common.h
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef COMMON_H
#define COMMON_H

// Common includes
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <GL/glew.h>
#include <GL/gl.h>

// Configuration file
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

// Common defines
#define GL_GLEXT_PROTOTYPES
#define ILUT_USE_OPENGL

#endif
