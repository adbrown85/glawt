/*
 * BooleanAnd.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef BOOLEANAND_HPP
#define BOOLEANAND_HPP
#include "common.h"
#include "Boolean.hpp"
#include "UniformSampler.hpp"
#include "Factory.hpp"
using namespace std;


/**
 * @ingroup advanced
 * @brief %Boolean AND operation of two shapes.
 * 
 * <b>XML Name</b>
 *   - @e boolean
 * 
 * <b>XML Attributes</b>
 * <table border="1" cellpadding="2">
 * <tr>
 *   <td><i>operation</i></td>
 *   <td>AND</td>
 * </tr>
 * <tr>
 *   <td><i>of</i></td>
 *   <td>Name of a group to get shapes from</td>
 * </tr>
 * <tr>
 *   <td><i>selectable</i></td>
 *   <td>If resulting polygons should be selectable</td>
 * </tr>
 * </table>
 * 
 * <b>XML Example</b>
 *   - &lt;boolean operation="AND" of="cubes" selectable="false" /&gt;
 * 
 * <b>Vertex Attributes</b>
 * <table border="1" cellpadding="2">
 * <tr>
 *   <td><i>MCVertex</i></td>
 *   <td>Point at the vertex.</td>
 * </tr>
 * <tr>
 *   <td><i>MCNormal</i></td>
 *   <td>Normal at the vertex.</td>
 * </tr>
 * <tr>
 *   <td><i>TexCoord0</i></td>
 *   <td>%Texture coordinates of the first shape.</td>
 * </tr>
 * <tr>
 *   <td><i>TexCoord1</i></td>
 *   <td>%Texture coordinates of the second shape.</td>
 * </tr>
 * </table>
 * 
 * In addition, @e %BooleanAnd will copy the uniforms of shapes in the group it 
 * is linked to, appending the index of the shape in the group to the end of 
 * the uniform's name.  For instance, if the first shape in the group has a 
 * uniform named @e Color, the resulting uniform under @e %BooleanAnd will be 
 * @e Color0.  Note however that it will only copy the uniforms that are 
 * children of the shape, not ones that are siblings.
 * 
 * If the user wishes the resulting polygons to be in the same place as the 
 * shapes they were generated from, the user should not perform any 
 * transformations on the boolean, as the points are outputted in modelview 
 * space.  The user should be sure to provide a uniform specifying the 
 * modelview projection matrix however.
 */
class BooleanAnd : public Boolean {
public:
	BooleanAnd(const Tag &tag) : Boolean(tag,getTraits()) {}
	virtual void associate();
	static ShapeTraits getTraits();
protected:
	virtual void calculateTangible();
	virtual void findUniforms();
	virtual void updateBufferPoints();
	virtual void updateBufferCoords();
private:
	GLfloat points[24][3], coords[2][24][3];
};


#endif
