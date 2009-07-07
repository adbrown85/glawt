/*
 * Item.hpp
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#ifndef ITEM_HPP
#define ITEM_HPP
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include "Identifiable.hpp"
#include "Node.hpp"
#include "Vector.hpp"
using std::map;
using std::pair;
using std::string;



/**
 * @brief
 *     Base class for an object in the scene.
 * @ingroup graph
 */
class Item : public Identifiable, public Node  {
	
	
	public :
		
		Item();
		
		friend std::ostream& operator<<(std::ostream &stream,
		                                const Item &item);
		
		virtual string attributes() const;
		virtual void copy(const Item &item);
		
		static Item* find(int id);
		
		string getCategory() const {return cat;}
		int getID() const {return id;}
		Vector getPosition() const {return position;}
		float getSize() const {return size;}
		string getType() const {return type;}
		bool isSelected() const {return selected;}
		bool isShown() const {return shown;}
		void setID(int id) {this->id = id;}
		Item& setPosition(float x, float y, float z) {
			position.set(x, y, z, 1.0);
			return *this;
		}
		void setSelected(bool selected) {this->selected = selected;}
		void setShown(bool shown) {this->shown = shown;}
		void setStyle(GLenum style) {this->style = style;}
		void toggleSelected() {selected = !selected;}
		void toggleShown() {shown = !shown;}
	
	
	protected : 
		
		bool selected, shown;
		float size;
		GLenum style;
		int id;
		string cat;
		Vector position, rotation;
		
		static int count;
		static map<int,Item*> ids;
};
typedef std::set<Item,Identifiable::Comparator> ItemSet;
typedef std::set<Item*,Identifiable::Comparator> ItemPtrSet;


#endif
