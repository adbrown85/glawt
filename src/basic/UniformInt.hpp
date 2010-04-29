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


class UniformInt : public Uniform {
	
	public:
		
		UniformInt(const Tag &tag);
		virtual void apply();
		virtual void remove();
		virtual string toString() const;
	
	private:
		
		GLint value;
};


#endif
