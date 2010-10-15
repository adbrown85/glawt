/*
 * Box.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Box.hpp"


/** Initializes the coordinates in the vertex buffer.
 * 
 * The following 2D texture coordinates are stored in an array as follows.
 * 
 * <pre>
 *      01-----11      2-------3
 *      |       |      |       |
 *      |       |      |       |
 *      00-----10      0-------1
 * </pre>
 * 
 * They are applied to the vertices in the vertex buffer as depicted in the 
 * following diagram.  Numbers on the left are the indices of the vertices, 
 * while numbers on the right correspond to the positions in the texture 
 * coordinate array above.
 * 
 * <pre>
 *            INDICES                COORDINATES
 *              +-------+              +-------+
 *             /|      /|             /|      /|
 *            1-------0 |            2-------3 |
 *     FRONT  | +-----|-+            | +-----|-+
 *            |/      |/             |/      |/ 
 *            2-------3              0-------1  
 *     
 *              4-------5              3-------2
 *             /|      /|             /|      /|
 *            +-------+ |            +-------+ |
 *     BACK   | 7-----|-6            | 1-----|-0
 *            |/      |/             |/      |/ 
 *            +-------+              +-------+  
 * 
 *              9-------+              2-------+
 *             /|      /|             /|      /|
 *            8-------+ |            3-------+ |
 *     LEFT   | 10----|-+            | 0-----|-+
 *            |/      |/             |/      |/ 
 *            11------+              1-------+  
 * 
 *              +------12              +-------3
 *             /|      /|             /|      /|
 *            +------13 |            +-------2 |
 *     RIGHT  | +-----|15            | +-----|-1
 *            |/      |/             |/      |/ 
 *            +------14              +-------0  
 * 
 *              17-----16              2-------3
 *             /|      /|             /|      /|
 *            18-----19 |            0-------1 |
 *     TOP    | +-----|-+            | +-----|-+
 *            |/      |/             |/      |/ 
 *            +-------+              +-------+  
 * 
 *              +-------+              +-------+
 *             /|      /|             /|      /|
 *            +-------+ |            +-------+ |
 *     BOTTOM | 22----|23            | 0-----|-1
 *            |/      |/             |/      |/ 
 *            21-----20              2-------3  
 * </pre>
 */
void Box::updateBufferCoords() {
	
	GLfloat C[4][3] = {{0.0, 0.0, 0.0},
	                   {1.0, 0.0, 0.0},
	                   {0.0, 1.0, 0.0},
	                   {1.0, 1.0, 0.0}};
	GLfloat coords[24][3];
	GLubyte indices[4][6] = {{ 2,  6, 10, 14, 18, 22},  // 0  (0.0, 0.0)
	                         { 3,  7, 11, 15, 19, 23},  // 1  (1.0, 0.0)
	                         { 1,  5,  9, 13, 17, 21},  // 2  (0.0, 1.0)
	                         { 0,  4,  8, 12, 16, 20}}; // 3  (1.0, 1.0)
	
	// Copy each coordinate to its corresponding indices
	int index;
	for (int c=0; c<4; ++c) {
		for (int j=0; j<6; ++j) {
			index = indices[c][j];
			for (int k=0; k<3; ++k)
				coords[index][k] = C[c][k];
		}
	}
	
	// Send to buffer
	setBufferData("TexCoord0", coords);
}

