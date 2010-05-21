/*
 * SimpleDrawable.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef SIMPLEDRAWABLE_HPP
#define SIMPLEDRAWABLE_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include "Node.hpp"
using namespace std;


/**
 * @ingroup graph
 * @brief Base class for a node that can be drawn on screen.
 */
class SimpleDrawable : public Drawable {
public:
	SimpleDrawable(const Tag &tag);
	virtual void draw() const = 0;
	virtual bool isSelectable() const;
	virtual bool isSelected() const;
	virtual bool isVisible() const;
	virtual void setSelected(bool selected);
	virtual void setVisible(bool visible);
	virtual void toggleSelected();
	virtual void toggleVisible();
	virtual string toString() const;
protected:
	bool selectable, selected, visible;
};

inline bool SimpleDrawable::isSelectable() const {return selectable;}
inline bool SimpleDrawable::isSelected() const {return selected;}
inline bool SimpleDrawable::isVisible() const {return visible;}
inline void SimpleDrawable::setSelected(bool sel) {this->selected = sel;}
inline void SimpleDrawable::setVisible(bool vis) {this->visible = vis;}
inline void SimpleDrawable::toggleSelected() {selected = !selected;}
inline void SimpleDrawable::toggleVisible() {visible = !visible;}



#endif