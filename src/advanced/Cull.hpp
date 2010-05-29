/*
 * Cull.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef CULL_HPP
#define CULL_HPP
#include "common.h"
#include "Node.hpp"
using namespace std;


/** @brief Removes back or front-facing polygons.
 * @ingroup advanced
 */
class Cull : public Applicable {
public:
	Cull(const Tag &tag);
	void apply();
	void remove();
	string toString() const;
private:
	bool enabled;
	GLenum faces;
	string facesString;
};


#endif
