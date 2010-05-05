/*
 * Selection.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef SELECTION_HPP
#define SELECTION_HPP
#include <cstdlib>
#include <iostream>
#include <list>
#include <set>
#include "Identifiable.hpp"
#include "Node.hpp"
#include "Drawable.hpp"
using namespace std;


/**
 * @ingroup graph
 * @brief Collection of selected items.
 */
class Selection {
public:
	typedef set<Drawable*,Identifiable::Comparator>::iterator iterator;
	void add(Drawable *item);
	void addAll(Node *node);
	iterator begin();
	void clear();
	iterator end();
	void remove(Drawable *item);
private:
	set<Drawable*,Identifiable::Comparator> items;
};

/** @return iterator to the beginning of the selection. */
inline Selection::iterator Selection::begin() {return items.begin();}

/** @return iterator to the end of the selection. */
inline Selection::iterator Selection::end() {return items.end();}





#endif
