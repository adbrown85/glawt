/*
 * Depth.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef DEPTH_HPP
#define DEPTH_HPP
#include "common.h"
#include "Node.hpp"
using namespace std;


/** @brief Modifies the depth function.
 * 
 * <b>XML Name</b>
 *   - depth
 * 
 * <b>XML attributes</b>
 * <table border="1" cellpadding="2">
 * <tr>
 *   <td><i>mode</i></td>
 *   <td>Comparison to determine if incoming fragment passes depth test.</td>
 * </tr>
 * </table>
 * 
 * <b><i>mode</i> values</b>
 *   - never
 *   - less
 *   - equal
 *   - lequal
 *   - greater
 *   - notequal
 *   - gequal
 *   - always
 * 
 * <b>OpenGL Functions</b>
 *   - glDepthFunc
 *   - glClearDepth
 *   - glClear
 * 
 * <b>Example</b>
 * <pre>
 *   &lt;depth mode="gequal">
 *     &lt;cube />
 *   &lt;/depth>
 * </pre>
 * 
 * @ingroup advanced
 */
class Depth : public Node, public Applicable {
public:
	Depth(const Tag &tag);
	virtual void apply();
	virtual void remove();
	virtual string toString() const;
private:
	GLenum mode;
	float clear;
};


#endif
