/*
 * UniformInt.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef UNIFORMINT_HPP
#define UNIFORMINT_HPP
#include "Uniform.hpp"
using namespace std;


/** @brief Container for GLSL integer uniform variables.
 * @ingroup basic
 */
class UniformInt : public Uniform {
public:
	UniformInt(const Tag &tag);
	virtual void apply();
	virtual void setValue(GLint value);
	virtual string toString() const;
private:
	GLint value;
};

inline void UniformInt::setValue(GLint value) {this->value = value;}


#endif
