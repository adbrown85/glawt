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
#include "Node.hpp"
#include "Tag.hpp"
using namespace std;


/**
 * @ingroup graph
 * @brief %Node that can be drawn and identified on screen.
 */
class Drawable : public Node,
                 public Identifiable {
public:
	Drawable(const Tag &tag);
	virtual void draw() const = 0;
	virtual float getSize() const;
	virtual bool isVisible() const;
	virtual bool isSelected() const;
	virtual void setSelected(bool selected);
	virtual void setSize(float size);
	virtual void setVisible(bool visible);
	virtual void toggleSelected();
	virtual void toggleVisible();
	virtual string toString() const;
protected:
	bool selected, visible;
	float size;
};


inline float Drawable::getSize() const {return size;}
inline bool Drawable::isSelected() const {return selected;}
inline bool Drawable::isVisible() const {return visible;}
inline void Drawable::setSelected(bool selected) {this->selected = selected;}
inline void Drawable::setSize(float size) {this->size = size;}
inline void Drawable::setVisible(bool visible) {this->visible = visible;}
inline void Drawable::toggleSelected() {selected = !selected;}
inline void Drawable::toggleVisible() {visible = !visible;}



#endif
