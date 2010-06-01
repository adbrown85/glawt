/*
 * Suppressor.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Suppressor.hpp"


/** Defaults @e enabled to true and @e tally to 0. */
Suppressor::Suppressor() {
	
	enabled = true;
	tally = 0;
}


/** Adds @e item to the items that may be suppressed. */
void Suppressor::add(Suppressable *item) {
	
	items.push_back(item);
}


/** @return Number of items that were suppressed. */
int Suppressor::check() {
	
	list<Suppressable*>::iterator it;
	
	// Didn't suppress anything
	if (!enabled)
		return 0;
	
	// Count how many items were suppressed
	tally = 0;
	for (it=items.begin(); it!=items.end(); ++it) {
		if ((*it)->wasSuppressed()) {
			++tally;
		}
	}
	return tally;
}


/** Prints a message to the log as if it were at the location of @e tag. */
void Suppressor::print(const Tag &tag) {
	
	glog << tag.getLocation();
	glog << "[Suppressor] Suppressed " << tally << " items." << endl;
}


/** Sets suppression of each item. */
void Suppressor::start() {
	
	list<Suppressable*>::iterator it;
	
	for (it=items.begin(); it!=items.end(); ++it) {
		(*it)->setSuppress(enabled);
	}
}




