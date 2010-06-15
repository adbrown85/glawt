/*
 * BasicFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef BASICFACTORY_HPP
#define BASICFACTORY_HPP
#include "common.h"
#include "Factory.hpp"
#include "NodeException.hpp"
#include "Box.hpp"
#include "Cube.hpp"
#include "Cone.hpp"
#include "Disk.hpp"
#include "Group.hpp"
#include "Light.hpp"
#include "Line.hpp"
#include "Program.hpp"
#include "Rotate.hpp"
#include "Scale.hpp"
#include "Shader.hpp"
#include "Square.hpp"
#include "Texture2D.hpp"
#include "Texture3D.hpp"
#include "Translate.hpp"
#include "UniformInt.hpp"
#include "UniformFloat.hpp"
#include "UniformMatrix.hpp"
#include "UniformSampler.hpp"
#include "UniformVector.hpp"
#include "Wireframe.hpp"
using namespace std;


/**
 * @ingroup basic
 * @brief %Factory for creating nodes used by most files.
 */
class BasicFactory {
public:
	static void install();
	static Node* createBox(const Tag &tag);
	static Node* createCone(const Tag &tag);
	static Node* createCube(const Tag &tag);
	static Node* createDisk(const Tag &tag);
	static Node* createGroup(const Tag &tag);
	static Node* createLight(const Tag &tag);
	static Node* createLine(const Tag &tag);
	static Node* createProgram(const Tag &tag);
	static Node* createRotate(const Tag &tag);
	static Node* createScale(const Tag &tag);
	static Node* createShader(const Tag &tag);
	static Node* createSquare(const Tag &tag);
	static Node* createTexture(const Tag &tag);
	static Node* createTranslate(const Tag &tag);
	static Node* createUniform(const Tag &tag);
	static Node* createWireframe(const Tag &tag);
private:
	enum kind_t {INT, FLOAT, MATRIX, SAMPLER, VECTOR};
	static bool installed;
	static map<string,kind_t> kinds;
};


#endif
