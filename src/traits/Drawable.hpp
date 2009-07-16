/*
 * Drawable.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __DRAWABLE_HPP__
#define __DRAWABLE_HPP__
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include "Identifiable.hpp"
using std::ostream;
using std::string;



/**
 * @interface Drawable
 * @ingroup traits
 * @brief
 *     Interface for something that can be drawn.
 */
class Drawable : public Identifiable {
	
	
	public :
		
		Drawable();
		virtual void copySizeOf(const Drawable &other);
		virtual void draw() const /* = 0 */ {;}
		virtual void hide();
		virtual bool isVisible() const;
		virtual void show();
		virtual void toggleVisibility();
		
		virtual float getSize() {return size;}
		virtual void setSize(float size) {this->size = size;}
		
		friend ostream& operator<<(ostream &stream,
		                           const Drawable &item);
	
	
	protected:
		
		bool visible;
		float size;
};


#endif
