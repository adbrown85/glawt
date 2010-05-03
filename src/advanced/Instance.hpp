/*
 * Instance.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef INSTANCE_HPP
#define INSTANCE_HPP
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <queue>
#include <GL/glut.h>
#include "Group.hpp"
#include "Applicable.hpp"
#include "Tag.hpp"
#include "Uniform.hpp"
using namespace std;


/**
 * @ingroup advanced
 * @brief Redraws all the nodes of a group with different characteristics.
 */
class Instance : public Applicable {
public:
	Instance(const Tag &tag);
	virtual void apply();
	virtual bool areChildrenDestroyable() const;
	virtual bool areChildrenPrintable() const;
	virtual bool areChildrenFinalizedAfter() const;
	virtual void associate();
	virtual void finalize();
	virtual void remove();
	virtual string toString() const;
private:
	Group *group;
	string of;
	map<Uniform*,int> locations;
};


inline bool Instance::areChildrenFinalizedAfter() const {return false;}
inline bool Instance::areChildrenDestroyable() const {return false;}
inline bool Instance::areChildrenPrintable() const {return false;}


#endif
