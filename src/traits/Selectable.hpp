/*
 * Selectable.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef SELECTABLE_HPP
#define SELECTABLE_HPP
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include "Drawable.hpp"
using namespace std;



/**
 * @interface Selectable
 * @ingroup traits
 * @brief
 *     Interface for an object that can be part of a selection.
 */
class Selectable : public Drawable {
	
	
	public :
		
		Selectable(float size=1.0);
		virtual void deselect();
		virtual bool isSelected() const;
		virtual void select();
		virtual void toggleSelected();
		virtual string toString() const;
	
	
	protected:
		
		bool selected;
};


#endif
