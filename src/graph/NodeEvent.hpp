/*
 * NodeEvent.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef NODEEVENT_HPP
#define NODEEVENT_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include "Node.hpp"
using namespace std;


/**
 * @ingroup graph
 * @brief Event occurred in a node.
 */
class NodeEvent {
public:
	enum {ASSOCIATE,FINALIZE,MODIFY};
	NodeEvent(Node *source, int type);
	Node* getSource() const;
	int getType() const;
private:
	Node *source;
	int type;
};

inline NodeEvent::NodeEvent(Node *s, int t) : source(s), type(t) {}
inline Node* NodeEvent::getSource() const {return source;}
inline int NodeEvent::getType() const {return type;}


#endif
