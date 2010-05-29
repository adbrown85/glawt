/*
 * Selection.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef SELECTION_HPP
#define SELECTION_HPP
#include "common.h"
#include <set>
#include "Identifiable.hpp"
#include "Node.hpp"
#include "NodeEvent.hpp"
using namespace std;


/** @brief Collection of selected items.
 * @ingroup scene
 */
class Selection {
public:
	typedef set<Drawable*,Identifiable::Comparator>::iterator iterator;
	void add(Drawable *item);
	void addAll(Node *node);
	void addListener(NodeListener *listener);
	iterator begin();
	void clear();
	void fireEvent();
	iterator end();
	void remove(Drawable *item);
private:
	set<Drawable*,Identifiable::Comparator> items;
	NodeNotifier notifier;
	Drawable *active;
};

/** @return iterator to the beginning of the selection. */
inline Selection::iterator Selection::begin() {return items.begin();}

/** @return iterator to the end of the selection. */
inline Selection::iterator Selection::end() {return items.end();}





#endif
