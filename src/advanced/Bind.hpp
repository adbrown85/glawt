/*
 * Bind.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef BIND_HPP
#define BIND_HPP
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include "Node.hpp"                     // Base class
#include "Attachment.hpp"               // Look up attachment location
#include "Program.hpp"                  // Bind location in current program
using namespace std;


/**
 * @ingroup advanced
 * @brief Binds a fragment shader output variable to location in a framebuffer.
 * 
 * <b>XML Name</b>
 *   - bind
 * 
 * <b>XML attributes</b>
 * <table border="1" cellpadding="2">
 * <tr>
 *   <td><i>name</i></td>
 *   <td>Name of the output variable in the fragment shader.</td>
 * </tr>
 * <tr>
 *   <td><i>to</i></td>
 *   <td>Name of the attachment to link to.</td>
 * </tr>
 * </table>
 */
class Bind : public Node {
public:
	Bind(const Tag &tag);
	virtual string toString() const;
protected:
	virtual void associate();
	virtual void finalize();
private:
	string name, to;
	GLint index;
	Program *program;
	Attachment *attachment;
};


#endif
