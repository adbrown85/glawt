/*
 * NodeInterfaces.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef NODEINTERFACES_HPP
#define NODEINTERFACES_HPP
#include "common.h"
#include "Node.hpp"
#include "Canvas.hpp"
using namespace std;


/** @brief %Node that can be applied, and then removed.
 * @interface Applicable
 * @ingroup scene
 */
class Applicable {
public:
	virtual void apply() = 0;
	virtual void remove() = 0;
};


/** @brief %Node that can be attached to another node.
 * @interface Attachable
 * @ingroup scene
 */
class Attachable : public Node {
public:
	Attachable(const Tag &tag) : Node(tag) {}
	virtual void attach() = 0;
	virtual void setIndex(GLint index) = 0;
	virtual void setLocation(GLuint location) = 0;
};


/* Upper and lower boundaries of an object. */
struct Extent {
	Vector upper, lower, diagonal;
	int label, index;
};


/** @brief %Node that can be positioned and sized.
 * @interface Transformable
 * @ingroup scene
 */
class Transformable {
public:
	virtual Extent getExtent() = 0;
	virtual Vector getPosition() = 0;
	virtual Matrix getTransformation() = 0;
	virtual Matrix getTransformationInverse() = 0;
};


/** @brief %Node that can be drawn and identified on screen.
 * @interface Drawable
 * @ingroup scene
 */
class Drawable : public Identifiable {
public:
	virtual void draw() const = 0;
	virtual bool isExcluded() const = 0;
	virtual bool isSelectable() const = 0;
	virtual bool isSelected() const = 0;
	virtual bool isVisible() const = 0;
	virtual void setExcluded(bool excluded) = 0;
	virtual void setSelected(bool selected) = 0;
	virtual void setVisible(bool visible) = 0;
	virtual void toggleSelected() = 0;
	virtual void toggleVisible() = 0;
};


/** @brief %Node that depends on the view to perform its operation.
 * @interface Dependent
 * @ingroup scene
 */
class Dependent {
public:
	Dependent();
	virtual void setCanvas(Canvas *canvas);
protected:
	Canvas* getCanvas() const;
private:
	Canvas *canvas;
};
inline Dependent::Dependent() {canvas = NULL;}
inline Canvas* Dependent::getCanvas() const {return canvas;}
inline void Dependent::setCanvas(Canvas *c) {canvas = c;}


/** @brief %Node that can have its exceptions suppressed.
 * @interface Suppressable
 * @ingroup scene
 */
class Suppressable {
public:
	Suppressable();
	virtual bool isSuppressed() const;
	virtual void setSuppress(bool suppress);
	virtual bool wasSuppressed() const = 0;
private:
	bool suppress;
};
inline Suppressable::Suppressable() {suppress = false;}
inline bool Suppressable::isSuppressed() const {return suppress;}
inline void Suppressable::setSuppress(bool s) {suppress = true;}


/** @brief %Node with a name.
 * @interface Nameable
 * @ingroup scene
 */
class Nameable {
public:
	Nameable() {}
	Nameable(const Tag &tag);
	virtual string getName() const;
	virtual bool hasName() const;
	virtual void setName(const string &name);
	virtual string toString() const;
	static Node* search(Node *node, const string &name);
private:
	string name;
};
inline string Nameable::getName() const {return name;}
inline bool Nameable::hasName() const {return !name.empty();}
inline void Nameable::setName(const string &n) {name = n;}


/** @brief %Node loaded from a file.
 * @interface Fileable
 * @ingroup scene
 */
class Fileable {
public:
	Fileable() {}
	Fileable(const Tag &tag);
	virtual string getFilename() const;
	virtual bool hasFilename() const;
	virtual void setFilename(const string &name);
	virtual string toString() const;
private:
	string filename;
};
inline string Fileable::getFilename() const {return filename;}
inline bool Fileable::hasFilename() const {return !filename.empty();}
inline void Fileable::setFilename(const string &f) {filename = f;}


#endif
