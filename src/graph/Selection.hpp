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
#include <set>
#include "Identifiable.hpp"
#include "Node.hpp"
#include "Selectable.hpp"
using namespace std;


/**
 * @ingroup base
 * @brief
 *     Collection of selected items.
 */
class Selection {
	
	public :
		
		typedef set<Selectable*,Identifiable::Comparator>::iterator iterator;
		
		void add(Selectable *item);
		void addAll(Node *node);
		iterator begin();
		void clear();
		iterator end();
		void remove(Selectable *item);
		
		set<Selectable*,Identifiable::Comparator> items;
};


#endif
