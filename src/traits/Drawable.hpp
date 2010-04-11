/*
 * Drawable.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "Identifiable.hpp"
#include "Tag.hpp"
using namespace std;


/**
 * @interface Drawable
 * @ingroup traits
 * @brief
 *     Interface for something that can be drawn.
 */
class Drawable : public Identifiable {
	
	public :
		
		Drawable(float size=1.0);
		Drawable(const Tag &tag);
		virtual void copySizeOf(const Drawable &other);
		virtual void draw() const = 0;
		virtual void hide();
		virtual bool isVisible() const;
		virtual void show();
		virtual void toggleVisibility();
		virtual string toString() const;
		
		virtual float getSize() const;
		virtual void setSize(float size);
	
	protected:
		
		bool visible;
		float size;
};


inline float Drawable::getSize() const {return size;}
inline void Drawable::setSize(float size) {this->size = size;}


#endif
