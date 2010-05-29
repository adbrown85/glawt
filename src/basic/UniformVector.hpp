/*
 * UniformVector.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef UNIFORMVECTOR_HPP
#define UNIFORMVECTOR_HPP
#include "Uniform.hpp"
using namespace std;


/** @brief Container for GLSL vector uniform variables.
 * @ingroup basic
 */
class UniformVector : public Uniform {
public:
	UniformVector(const Tag &tag);
	virtual void apply();
	virtual string toString() const;
private:
	GLfloat value[4];
	GLint size;
};


#endif
