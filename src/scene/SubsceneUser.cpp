/*
 * SubsceneUser.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "SubsceneUser.hpp"


/** Initializes attributes. */
SubsceneUser::SubsceneUser() {
	
	traverser = NULL;
	opened = false;
}


/** Destroys the traverser. */
SubsceneUser::~SubsceneUser() {
	
	if (traverser != NULL) {
		delete traverser;
		traverser = NULL;
	}
}


/** Opens the subscene using @e filename from resources directory.
 * 
 * @throws Exception if already opened.
 */
void SubsceneUser::openSubscene(const string &filename) {
	
	// Check if already opened
	if (opened) {
		throw Exception("[SubsceneUser] Subscene already opened.");
	}
	
	// Open
	subscene.open(Resources::get(filename));
	traverser = new Traverser(&subscene);
	opened = true;
}

