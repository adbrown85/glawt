/* 
 * OctreeNode.glsl
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef OCTREENODE_GLSL
#define OCTREENODE_GLSL
#define NULL -1


/**
 * Node of an Octree.
 * 
 * @see OctreeNode_(int,int)
 */
struct OctreeNode {
	int key;
	int name;
};


/**
 * Default constructor.
 * 
 * @return node with NULL for key and name.
 */
OctreeNode OctreeNode_() {
	
	OctreeNode node;
	
	node.key = NULL;
	node.name = NULL;
	return node;
}


/**
 * Constructor.
 * 
 * @param key Index into the array
 * @param name Which child the node is
 */
OctreeNode OctreeNode_(in int key,
                       in int name) {
	
	OctreeNode node;
	
	node.key = key;
	node.name = name;
	return node;
}


#endif
