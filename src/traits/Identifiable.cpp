/*
 * Identifiable.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Identifiable.hpp"
int Identifiable::count=0;
map<int,Identifiable*> Identifiable::ids;



/**
 * Increments the counter and stores it as this identifiable 
 * object's unique ID number.
 */
Identifiable::Identifiable() {
	
	id = ++count;
	// ids[id] = this;
}



/**
 * Finds an identifiable object by its unique ID number.
 * 
 * @return
 *     Pointer to the object.
 */
Identifiable* Identifiable::findByID(int id) {
	
	map<int,Identifiable*>::iterator ii;
	
	// Find
	ii = ids.find(id);
	if (ii != ids.end())
		return ii->second;
	else
		return NULL;
}



/**
 * Returns a unique identifier to the object.
 */
int Identifiable::getID() const {
	
	return id;
}



ostream& operator<<(ostream& stream,
                    const Identifiable& item) {
	
	stream << "id=" << item.id;
	return stream;
}
