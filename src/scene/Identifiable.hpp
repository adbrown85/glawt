/*
 * Identifiable.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef IDENTIFIABLE_HPP
#define IDENTIFIABLE_HPP
#include "common.h"
#include <vector>
using namespace std;


/** @brief Interface for an object that has a unique ID number.
 * @interface Identifiable
 * @ingroup scene
 */
class Identifiable {
public:
	Identifiable();
	static Identifiable* findByID(unsigned int id);
	virtual unsigned int getID() const;
	string toString() const;
	
	class Comparator {
	public :
		bool operator()(const Identifiable &a,
		                const Identifiable &b);
		bool operator()(const Identifiable *a,
		                const Identifiable *b);
	};
private:
	unsigned int id;
	static unsigned int count;
	static vector<Identifiable*> ids;
};


/** Returns a unique identifier to the object. */
inline unsigned int Identifiable::getID() const {return id;}


inline bool Identifiable::Comparator::operator()(const Identifiable &a,
                                                 const Identifiable &b) {
	
	return a.getID() < b.getID();
}
inline bool Identifiable::Comparator::operator()(const Identifiable *a,
                                                 const Identifiable *b) {
	
	return a->getID() < b->getID();
}


#endif
