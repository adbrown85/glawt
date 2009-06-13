/*
 * Item.hpp
 *     Generic item class.
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#ifndef ITEM_HPP
#define ITEM_HPP
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <sstream>
#include "Vector.hpp"



class Item {
	
	
	public :
		
		Item();
		
		friend std::ostream& operator<<(std::ostream &stream,
		                                const Item& item);
		
		virtual std::string attributes() const;
		virtual void draw() const = 0;
		
		int getID() const {return id;}
		bool isSelected() const {return selected;}
		bool isShown() const {return shown;}
		void setPosition(float x, float y, float z) {position.set(x, y, z);}
		void setSelected(bool selected) {this->selected = selected;}
		void setShown(bool shown) {this->shown = shown;}
		void setStyle(GLenum style) {this->style = style;}
		void toggleSelected() {selected = !selected;}
		void toggleShown() {shown = !shown;}
	
	
	protected : 
		
		bool selected, shown;
		GLenum style;
		static int count;
		std::string type;
		Vector position;
		int id;
};



#endif
