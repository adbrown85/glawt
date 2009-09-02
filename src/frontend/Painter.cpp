/*
 * Painter.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Painter.hpp"
Box Painter::outline(1.0);



/**
 * Paints all the items in a scene.
 * 
 * @param scene
 *     Collection of items and camera information.
 * @param manipulators
 *     UI elements used to manipulate selected items.
 */
void Painter::paint(Scene &scene,
                    vector<Manipulator*> &manipulators,
                    GLenum renderMode) {
	
	float rotationMatrixArray[16];
	Matrix rotationMatrix;
	
	// Initialize
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	scene.sortByDepth();
	
	// Transform
	glTranslatef(scene.position.x,
	             scene.position.y,
	             scene.position.z);
	rotationMatrix = scene.getRotationMatrix();
	rotationMatrix.getArray(rotationMatrixArray);
	glMultMatrixf(rotationMatrixArray);
	
	// Draw
	paintNode(&scene.rootNode, renderMode, manipulators);
}



/**
 * Recursively paints the children of a node.
 * 
 * This functionality is implemented as a separate function, as opposed to 
 * incorporating it directly into <i>paint</i>, because some nodes need to 
 * paint their children at different times.
 * 
 * @param node
 *     Pointer to the parent node.
 * @param renderMode
 *     If GL_SELECT, will push IDs of items into pick buffer.
 */
void Painter::paintChildren(Node *node,
                            GLenum renderMode,
                            vector<Manipulator*> &manipulators) {
	
	int numberOfChildren;
	vector<Node*> children;
	
	// Paint each child
	children = node->getChildren();
	numberOfChildren = children.size();
	for (int i=0; i<numberOfChildren; ++i)
		paintNode(children[i], renderMode, manipulators);
}



/**
 * Recursively paints a node.
 * 
 * Automatically takes care of performing different actions depending on what 
 * type of interfaces the node supports.
 * 
 * @param node
 *     Pointer to the Node to paint.
 * @param renderMode
 *     If GL_SELECT, will push IDs of items into pick buffer.
 */
void Painter::paintNode(Node *node,
                        GLenum renderMode,
                        vector<Manipulator*> &manipulators) {
	
	Applicable *applicable;
	Drawable *drawable;
	Selectable *selectable;
	Program *program;
	vector<Manipulator*>::iterator mi;
	
	// Node is drawable
	if (drawable = dynamic_cast<Drawable*>(node)) {
		if (drawable->isVisible()) {
			if (renderMode == GL_SELECT)
				glPushName(drawable->getID());
			drawable->draw();
			
			// Node is selectable
			if (selectable = dynamic_cast<Selectable*>(node)) {
				if (selectable->isSelected()) {
					
					// Disable shading
					program = Program::getCurrent();
					program->remove();
					glColor3f(1.0, 1.0, 0.0);
					glPolygonMode(GL_FRONT, GL_LINE);
					
					// Draw outline
					outline.copySizeOf(*selectable);
					outline.draw();
					
					// Draw manipulators
					glDepthFunc(GL_LESS);
					glPolygonMode(GL_FRONT, GL_FILL);
					for (mi=manipulators.begin(); mi!=manipulators.end(); ++mi) {
						if (renderMode == GL_SELECT)
							glPushName((*mi)->getID());
						(*mi)->copySizeOf(*selectable);
						(*mi)->draw();
					}
					glDepthFunc(GL_ALWAYS);
					
					// Restore shading
					glColor3f(1.0, 1.0, 1.0);
					program->apply();
				}
			}
			
			paintChildren(node, renderMode, manipulators);
		}
	}
	
	// Node is applicable
	else if (applicable = dynamic_cast<Applicable*>(node)) {
		applicable->apply();
		paintChildren(node, renderMode, manipulators);
		applicable->remove();
	}
	
	// Node
	else
		paintChildren(node, renderMode, manipulators);
}

