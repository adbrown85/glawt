/*
 * UniformFloat.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef UNIFORMFLOAT_HPP
#define UNIFORMFLOAT_HPP
#include "Uniform.hpp"
using namespace std;


class UniformFloat : public Uniform {
	
	public:
		
		UniformFloat(const Tag &tag);
		virtual void apply();
		virtual void remove();
		virtual string toString() const;
	
	private:
		
		GLfloat value;
};


#endif
