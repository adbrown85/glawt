/*
 * Identifiable.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Identifiable.hpp"
unsigned int Identifiable::count=0;
vector<Identifiable*> Identifiable::ids;



/**
 * Increments the counter and stores it as this identifiable 
 * object's unique ID number.
 */
Identifiable::Identifiable() {
	
	id = count++;
	ids.push_back(this);
}



/**
 * Finds an identifiable object by its unique ID number.
 * 
 * @return
 *     Pointer to the object.
 */
Identifiable* Identifiable::findByID(unsigned int id) {
	
	// Find
	if (id < ids.size())
		return ids[id];
	else
		return NULL;
}



/**
 * Returns a unique identifier to the object.
 */
unsigned int Identifiable::getID() const {
	
	return id;
}



ostream& operator<<(ostream& stream,
                    const Identifiable& item) {
	
	stream << "id=" << item.id;
	return stream;
}
