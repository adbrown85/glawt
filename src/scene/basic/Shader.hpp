/*
 * Shader.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef SHADER_HPP
#define SHADER_HPP
#include "common.h"
#include "Node.hpp"
#include "NodeInterfaces.hpp"
#include "Program.hpp"
#include "Scout.hpp"
#include "ShaderFactory.hpp"
using namespace std;


/** @brief GLSL shader with loading and compiling capabilities.
 * 
 * <b>XML Name</b>
 *   - shader
 * 
 * <b>XML attributes</b>
 * <table border="1" cellpadding="2">
 * <tr>
 *   <td><i>type</i></td>
 *   <td>Either <i>fragment</i> or <i>vertex</i></td>
 * </tr>
 * <tr>
 *   <td><i>file</i></td>
 *   <td>Path to the file containing source code for the shader</td>
 * </tr>
 * </table>
 * 
 * <b>XML example</b>
 * <pre>
 *   &lt;program>
 *     &lt;shader file="color.vert" />
 *     &lt;shader file="color.frag" />
 *   &lt;/program>
 * </pre>
 * 
 * @ingroup basic
 */
class Shader : public Node, public Fileable {
public:
	Shader(const Tag &tag);
	virtual void associate();
	virtual string toString() const;
public:    // Accessors
	GLuint getHandle() const;
	string getType() const;
protected: // Helpers
	void guessType();
private:
	GLuint handle;
	string type;
};

/** @return Internal OpenGL identifier for the shader. */
inline GLuint Shader::getHandle() const {return handle;}

/** @return Either "fragment" or "vertex". */
inline string Shader::getType() const {return type;}


#endif
