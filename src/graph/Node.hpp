/*
 * Node.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef NODE_HPP
#define NODE_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <typeinfo>
#include <vector>
#include "NodeException.hpp"
#include "Identifiable.hpp"
#include "Tag.hpp"
#include "Text.hpp"
#include "Canvas.hpp"
using namespace std;


/**
 * @ingroup graph
 * @brief Basic element of the scene graph.
 */
class Node {
public:
	typedef vector<Node*>::iterator iterator;
	Node(const Tag &tag);
	virtual ~Node() {};
	void addChild(Node *child);
	virtual bool areChildrenDestroyable() const;
	virtual bool areChildrenPreparable() const;
	virtual bool areChildrenPrintable() const;
	virtual bool areChildrenSelectable() const;
	virtual bool areChildrenTraversable() const;
	virtual void associate() {}
	virtual void associateAfter() {}
	iterator begin();
	static bool compare(Node *A, Node *B);
	static void destroy(Node *node);
	void erase(iterator it);
	iterator end();
	virtual void finalize() {}
	virtual void finalizeAfter() {}
	static Node* findRoot(Node *node);
	vector<Node*> getChildren() const;
	string getClassName() const;
	float getDepth() const;
	Node* getParent() const;
	Tag getTag() const;
	bool hasChildren() const;
	friend ostream& operator<<(ostream &stream, const Node &node);
	virtual bool setAttribute(pair<string,string> attribute);
	void setDepth(float depth);
	void setParent(Node *parent);
	virtual string toString() const;
protected:
	float depth;
	Node *parent;
	Tag tag;
	vector<Node*> children;
};

inline bool Node::areChildrenDestroyable() const {return true;}
inline bool Node::areChildrenPreparable() const {return true;}
inline bool Node::areChildrenPrintable() const {return true;}
inline bool Node::areChildrenSelectable() const {return true;}
inline bool Node::areChildrenTraversable() const {return true;}
inline Node::iterator Node::begin() {return children.begin();}
inline Node::iterator Node::end() {return children.end();}
inline void Node::erase(Node::iterator it) {children.erase(it);}
inline vector<Node*> Node::getChildren() const {return children;}
inline float Node::getDepth() const {return depth;}
inline Node* Node::getParent() const {return parent;}
inline Tag Node::getTag() const {return tag;}
inline bool Node::hasChildren() const {return !children.empty();}
inline bool Node::setAttribute(pair<string,string> a) {return false;}
inline void Node::setDepth(float depth) {this->depth = depth;}
inline void Node::setParent(Node *parent) {this->parent = parent;}


/**
 * @interface Applicable
 * @ingroup graph
 * @brief %Node that can be applied, and then removed.
 */
class Applicable : public Node {
public:
	Applicable(const Tag &tag) : Node(tag) {}
	virtual void apply() = 0;
	virtual void remove() = 0;
};


/**
 * @interface Attachable
 * @ingroup graph
 * @brief %Node that can be attached to another node.
 */
class Attachable : public Node {
public:
	Attachable(const Tag &tag) : Node(tag) {}
	virtual void attach() = 0;
	virtual void setIndex(GLint index) = 0;
	virtual void setLocation(GLuint location) = 0;
};


/**
 * @interface Drawable
 * @ingroup graph
 * @brief %Node that can be drawn and identified on screen.
 */
class Drawable : public Node,
                 public Identifiable {
public:
	Drawable(const Tag &tag) : Node(tag) {}
	virtual void draw() const = 0;
	virtual bool isSelectable() const = 0;
	virtual bool isSelected() const = 0;
	virtual bool isVisible() const = 0;
	virtual void setSelected(bool selected) = 0;
	virtual void setVisible(bool visible) = 0;
	virtual void toggleSelected() = 0;
	virtual void toggleVisible() = 0;
};


/**
 * @interface Dependent
 * @ingroup graph
 * @brief %Node that depends on the view to perform its operation.
 */
class Dependent {
public:
	virtual void setCanvas(Canvas *canvas) = 0;
};

#endif
