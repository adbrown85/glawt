/*
 * BooleanXor.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef BOOLEANXOR_HPP
#define BOOLEANXOR_HPP
#include "common.h"
#include <algorithm>                    // For 'swap'
#include "Boolean.hpp"
#define BOOLEAN_XOR_COUNT 336
using namespace std;


/** @brief Exclusive OR boolean operator for two shapes.
 * 
 * <b>Vertex Attributes</b>
 *   - MCVertex
 *   - MCNormal
 *   - TexCoord0
 * 
 * @ingroup advanced
 */
class BooleanXor : public Boolean, public Dependent {
public:
	BooleanXor(const Tag &tag);
	virtual void draw() const;
	static ShapeTraits getTraits();
	virtual string toString() const;
protected:
	void addPiece(list<Extent> &pieces, const Extent &piece);
	virtual void calculate();
	virtual void calculateTangible();
	void drawWhenNotOverlapped(Matrix &rotation) const;
	void drawWhenOverlapped(Matrix &rotation) const;
	void explode(const Extent &piece, int d, list<Extent> &pieces);
	pair<Extent,Extent> knife(const Extent &extent, float at, int on);
	virtual void updateBufferPoints();
	virtual void updateBufferNormals();
	virtual void updateBufferCoords();
private:
	enum {ALL,BEHIND,BESIDE,FORWARD};
private:
	GLfloat points[BOOLEAN_XOR_COUNT][3], coords[BOOLEAN_XOR_COUNT][3];
	int only;
	list<Extent> pieces;
};

/** Assumed to be always visible (for now). */
inline void BooleanXor::calculateTangible() {tangible = true;}


#endif
