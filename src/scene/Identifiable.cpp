/*
 * Identifiable.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Identifiable.hpp"
unsigned int Identifiable::count=0;
vector<Identifiable*> Identifiable::ids;


/** Increments counter and stores it as this object's unique ID number. */
Identifiable::Identifiable() {
	
	// Make sure zero position is NULL
	if (count == 0)
		ids.push_back(NULL);
	
	// Store IDs
	id = ++count;
	ids.push_back(this);
}


/** Finds an identifiable object by its unique ID number.
 * 
 * @return Pointer to the object (NULL if not found).
 */
Identifiable* Identifiable::findByID(unsigned int id) {
	
	// Find
	if (id <= count)
		return ids[id];
	else
		return NULL;
}


/** Forms a string from the object's attributes. */
string Identifiable::toString() const {
	
	stringstream stream;
	
	// Make string
	stream << "id='" << id << "'";
	return stream.str();
}

