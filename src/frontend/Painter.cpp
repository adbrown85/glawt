/*
 * Painter.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Painter.hpp"
Outline Painter::outline(1.0);



/**
 * Paints all the items in a scene.
 * 
 * @param scene
 *     Collection of items and camera information.
 * @param manipulators
 *     User interface widgets used to manipulate selected items.
 */
void Painter::paint(Scene &scene,
                    vector<Manipulator*> &manipulators,
                    GLenum renderMode) {
	
	float rotationMatrixArray[16];
	Matrix rotationMatrix;
	
	// Initialize
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// Transform
	glTranslatef(scene.position.x,
	             scene.position.y,
	             scene.position.z);
	rotationMatrix = scene.getRotationMatrix();
	rotationMatrix.getArray(rotationMatrixArray);
	glMultMatrixf(rotationMatrixArray);
	
	// Draw
	paintNode(&scene.rootNode, manipulators, renderMode);
}



/**
 * Recursively paints a node.  Automatically takes care of performing 
 * different actions depending on what type of interfaces the node supports.
 * 
 * @param node
 *     Pointer to the Node to paint.  Generally should be a scene's root node.
 * @param manipulators
 *     User interface widgets used to manipulate selected items.
 */
void Painter::paintNode(Node *node,
                        vector<Manipulator*> &manipulators,
                        GLenum renderMode) {
	
	Applicable *applicable;
	Drawable *drawable;
	Selectable *selectable;
	vector<Manipulator*>::iterator mi;
	
	// Node is drawable
	if (drawable = dynamic_cast<Drawable*>(node)) {
		if (drawable->isVisible()) {
			if (renderMode == GL_SELECT)
				glPushName(drawable->getID());
			drawable->draw();
			if (selectable = dynamic_cast<Selectable*>(node)) {
				if (selectable->isSelected()) {
					outline.copySizeOf(*selectable);
					outline.draw();
					for (mi=manipulators.begin(); 
					     mi!=manipulators.end();
					     ++mi) {
						if (renderMode == GL_SELECT)
							glPushName((*mi)->getID());
						(*mi)->copySizeOf(*selectable);
						(*mi)->draw();
					}
				}
				paintChildren(node, manipulators, renderMode);
			}
		}
	}
	
	// Node is applicable
	else if (applicable = dynamic_cast<Applicable*>(node)) {
		applicable->apply();
		paintChildren(node, manipulators, renderMode);
		applicable->remove();
	}
	
	// Node
	else
		paintChildren(node, manipulators, renderMode);
}



/**
 * Recursively paints the children of a node.
 * 
 * This functionality is implemented as a separate function, as opposed to 
 * incorporating it directly into <i>paint</i>, because some nodes, mainly 
 * those that implement <i>%Applicable</i>, need to do something, have their 
 * children painted, and then do something else.
 * 
 * @param node
 *     Parent node to paint children for.
 * @param manipulators
 *     User interface widgets used to manipulate selected items.
 */
void Painter::paintChildren(Node *node,
                            vector<Manipulator*> &manipulators,
                            GLenum renderMode) {
	
	int numberOfChildren;
	
	// Paint each child
	numberOfChildren = node->children.size();
	for (int i=0; i<numberOfChildren; ++i)
		paintNode(node->children[i], manipulators, renderMode);
}
