/*
 * UniformSampler.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef UNIFORMSAMPLER_HPP
#define UNIFORMSAMPLER_HPP
#include "Uniform.hpp"
using namespace std;


/**
 * @ingroup basic
 * @brief Container for GLSL sampler uniform variables.
 */
class UniformSampler : public Uniform {
public:
	UniformSampler(const Tag &tag);
	virtual void associate();
	virtual void apply();
	virtual GLint getValue() const;
	virtual string toString() const;
private:
	GLint value;
};


/** @return texture unit the sampler points to. */
inline GLint UniformSampler::getValue() const {return value;}


#endif
