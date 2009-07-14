/*
 * Selection.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __SELECTION_HPP__
#define __SELECTION_HPP__
#include <cstdlib>
#include <iostream>
#include <set>
#include "Identifiable.hpp"
#include "Selectable.hpp"
using std::set;



/**
 * @ingroup graph
 * @brief
 *     Collection of selected items.
 */
class Selection {
	
	
	public :
		
		typedef set<Selectable*,Identifiable::Comparator>::iterator iterator;
		
		void add(Selectable *item);
		iterator begin();
		iterator end();
		void remove(Selectable *item);
		
		set<Selectable*,Identifiable::Comparator> items;
};


#endif
