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
 * @param renderMode
 *     Either GL_RENDER or GL_SELECT.
 */
void Painter::paint(Scene &scene,
                    vector<Manipulator*> &manipulators,
                    GLenum renderMode) {
	
	float rotationMatrixArray[16];
	Matrix rotationMatrix;
	
	// Initialize
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (renderMode != GL_SELECT)
		scene.sortByDepth();
	
	// Transform
	glTranslatef(scene.position.x,
	             scene.position.y,
	             scene.position.z);
	rotationMatrix = scene.getRotationMatrix();
	rotationMatrix.getArray(rotationMatrixArray);
	glMultMatrixf(rotationMatrixArray);
	
	// Draw
	paintNode(&scene.root, renderMode, manipulators);
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
 * @param manipulators
 *     UI elements used to manipulate selected items.
 */
void Painter::paintChildren(Node *node,
                            GLenum renderMode,
                            vector<Manipulator*> &manipulators) {
	
	int numberOfChildren;
	vector<Node*> children;
	
	// Paint each child
	children = node->getChildren();
	numberOfChildren = children.size();
	for (int i=0; i<numberOfChildren; ++i) {
		paintNode(children[i], renderMode, manipulators);
	}
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
 * @param manipulators
 *     UI elements used to manipulate selected items.
 */
void Painter::paintNode(Node *node,
                        GLenum renderMode,
                        vector<Manipulator*> &manipulators) {
	
	Applicable *applicable;
	Drawable *drawable;
	Selectable *selectable;
	Framebuffer *framebuffer;
	
	// Node is drawable and visible
	if ((drawable = dynamic_cast<Drawable*>(node))
	      && drawable->isVisible()) {
		
		// Draw the node
		if (renderMode == GL_SELECT)
			glLoadName(drawable->getID());
		drawable->draw();
		
		// Paint UI elements for selected nodes
		if ((selectable = dynamic_cast<Selectable*>(node))
		      && selectable->isSelected()
		      && !Framebuffer::isActive())
			paintUIElements(selectable, renderMode, manipulators);
		
		// Paint children
		paintChildren(node, renderMode, manipulators);
	}
	
	// Node is applicable
	else if (applicable = dynamic_cast<Applicable*>(node)) {
		applicable->apply();
		paintChildren(node, renderMode, manipulators);
		applicable->remove();
	}
	
	// Regular node
	else
		paintChildren(node, renderMode, manipulators);
}



/**
 * Paints manipulators and an outline for a selected shape.
 */
void Painter::paintUIElements(Selectable *selectable,
                              GLenum renderMode,
                              vector<Manipulator*> &manipulators) {
	
	Program *program;
	vector<Manipulator*>::iterator mi;
	
	// Disable shading and texture
	program = Program::getCurrent();
	if (program != NULL)
		program->remove();
	Texture::pause();
	Light::pause();
	
	// Draw outline
	glPushAttrib(GL_CURRENT_BIT);
		glColor3f(1.0, 1.0, 0.0);
		glPushAttrib(GL_POLYGON_BIT);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			glPolygonMode(GL_FRONT, GL_LINE);
			outline.copySizeOf(*selectable);
			outline.draw();
		glPopAttrib();
	glPopAttrib();
	
	// Draw manipulators
	glPushAttrib(GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glPushAttrib(GL_POLYGON_BIT);
			glPolygonMode(GL_FRONT, GL_FILL);
			for (mi=manipulators.begin(); mi!=manipulators.end(); ++mi) {
				if (renderMode == GL_SELECT)
					glPushName((*mi)->getID());
				(*mi)->copySizeOf(*selectable);
				(*mi)->draw();
			}
		glPopAttrib();
	glPopAttrib();
	
	// Restore shading and texturing
	if (program != NULL)
		program->apply();
	Texture::restart();
	Light::restart();
}

