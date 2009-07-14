/*
 * Selectable.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __SELECTABLE_HPP__
#define __SELECTABLE_HPP__
#include <cstdlib>
#include <iostream>
#include <string>
#include "Drawable.hpp"
using std::ostream;
using std::string;



/**
 * @interface Selectable
 * @ingroup traits
 * @brief
 *     Interface for an object that can be part of a selection.
 */
class Selectable : public Drawable {
	
	
	public :
		
		Selectable();
		friend ostream& operator<<(ostream &stream,
		                           const Selectable &item);
		
		virtual void deselect();
		virtual bool isSelected() const;
		virtual void select();
		virtual void toggleSelected();
	
	
	protected:
		
		bool selected;
};


#endif
