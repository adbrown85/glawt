/*
 * SimpleDrawable.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef SIMPLEDRAWABLE_HPP
#define SIMPLEDRAWABLE_HPP
#include "common.h"
#include "Node.hpp"
#include "SimpleTransformable.hpp"
using namespace std;


/** @brief Base class for a node that can be drawn on screen.
 * @ingroup basic
 */
class SimpleDrawable : public SimpleTransformable,
                       public Drawable {
public:
	SimpleDrawable(const Tag &tag);
	virtual void draw() const = 0;
	virtual bool isExcluded() const;
	virtual bool isSelectable() const;
	virtual bool isSelected() const;
	virtual bool isVisible() const;
	virtual void setExcluded(bool excluded);
	virtual void setSelected(bool selected);
	virtual void setVisible(bool visible);
	virtual void toggleSelected();
	virtual void toggleVisible();
	virtual string toString() const;
protected:
	bool excluded, selectable, selected, visible;
};

inline bool SimpleDrawable::isExcluded() const {return excluded;}
inline bool SimpleDrawable::isSelectable() const {return selectable;}
inline bool SimpleDrawable::isSelected() const {return selected;}
inline bool SimpleDrawable::isVisible() const {return visible;}
inline void SimpleDrawable::setExcluded(bool exc) {this->excluded = exc;}
inline void SimpleDrawable::setSelected(bool sel) {this->selected = sel;}
inline void SimpleDrawable::setVisible(bool vis) {this->visible = vis;}
inline void SimpleDrawable::toggleSelected() {selected = !selected;}
inline void SimpleDrawable::toggleVisible() {visible = !visible;}



#endif
