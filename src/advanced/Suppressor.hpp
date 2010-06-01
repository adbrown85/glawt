/*
 * Suppressor.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef SUPPRESSOR_HPP
#define SUPPRESSOR_HPP
#include "common.h"
#include "Node.hpp"
#include "Log.hpp"
using namespace std;


/** @brief Utility for suppressing exceptions of other nodes.
 * @ingroup advanced
 */
class Suppressor {
public:
	Suppressor();
	void add(Suppressable *item);
	int check();
	bool isEnabled() const;
	void print(const Tag &tag);
	void setEnabled(bool enabled);
	void start();
private:
	bool enabled;
	int tally;
	list<Suppressable*> items;
};
inline bool Suppressor::isEnabled() const {return enabled;}
inline void Suppressor::setEnabled(bool e) {enabled = e;}



#endif
