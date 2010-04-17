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


class UniformSampler : public Uniform {
	
	public :
		
		UniformSampler(const Tag &tag);
		virtual void associate();
		virtual void apply();
		virtual void remove();
		virtual string toString() const;
	
	private:
		
		GLint value;
};


#endif
