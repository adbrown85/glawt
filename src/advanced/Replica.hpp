/*
 * Replica.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef REPLICA_HPP
#define REPLICA_HPP
#include "common.h"
#include "Clone.hpp"
using namespace std;


/** @brief Smart instance of a group capable of making some changes.
 * @ingroup advanced
 */
class Replica : public Clone {
public:
	Replica(const Tag &tag);
	virtual void apply();
	virtual void associate();
	virtual void remove();
	virtual string toString() const;
protected:
	void applyExclusions();
	void findExclusions();
	void removeExclusions();
private:
	string exclude;
	map<string,Shape*> exclusions;
};


#endif
