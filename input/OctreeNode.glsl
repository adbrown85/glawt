/* 
 * OctreeNode.glsl
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef OCTREENODE_GLSL
#define OCTREENODE_GLSL


/**
 * Node of an Octree.
 * 
 * @see OctreeNode_()
 */
struct OctreeNode {
	int key;
	int name;
};


/**
 * Constructor.
 * 
 * @param node
 *     OctreeNode instance.
 * @param key
 *     Index into the array.
 * @param name
 *     Which child the node is.
 */
void OctreeNode_(inout OctreeNode node,
                 in int key,
                 in int name) {
	
	node.key = key;
	node.name = name;
}


#endif
