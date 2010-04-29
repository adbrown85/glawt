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


class UniformVector : public Uniform {
	
	public:
		
		UniformVector(const Tag &tag);
		virtual void apply();
		virtual void remove();
		virtual string toString() const;
	
	private:
		
		GLfloat value[4];
		GLint size;
};


#endif
