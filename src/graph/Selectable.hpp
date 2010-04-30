/*
 * Selectable.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef SELECTABLE_HPP
#define SELECTABLE_HPP
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include "Drawable.hpp"
#include "Tag.hpp"
#include "Selectable.hpp"
using namespace std;


/**
 * @interface Selectable
 * @ingroup graph
 * @brief
 *     Interface for an object that can be part of a selection.
 */
class Selectable : public Drawable {
	
	public:
		
		Selectable(const string &className,
		           float size=1.0);
		Selectable(const string &className,
		           const Tag &tag);
		virtual void deselect();
		virtual bool isSelected() const;
		virtual void select();
		virtual void toggleSelected();
		virtual string toString() const;
	
	protected:
		
		bool selected;
};


#endif
