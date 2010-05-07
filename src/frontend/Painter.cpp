/*
 * Painter.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Painter.hpp"
Scene *Painter::outline=NULL;


Painter::Painter(Scene *scene,
                 GLenum mode) : Traverser(scene) {
	
	this->mode = mode;
	
	if (outline == NULL) {
		BasicFactory::install();
		AdvancedFactory::install();
		outline = new Scene();
		outline->open("${GANDER}/glsl/outline.xml");
		outline->prepare();
	}
}


void Painter::onApplicable(Applicable *node) {
	
	// Only continue if not a framebuffer node
	if (mode == GL_SELECT && !node->areChildrenSelectable())
		return;
	Traverser::onApplicable(node);
}


void Painter::onDrawable(Drawable *node) {
	
	Program *program;
	vector<Manipulator*>::iterator mi;
	
	// Stop if not visible
	if (!node->isVisible())
		return;
	
	// Load the name if selecting then draw
	if (mode == GL_SELECT)
		glLoadName(node->getID());
	Traverser::onDrawable(node);
	
	// Stop if not selected
	if (!node->isSelected())
		return;
	
	// Disable shading and texture
	program = Program::getCurrent();
	if (program != NULL)
		program->remove();
	Texture::pause();
	
	// Draw outline and manipulators
	glPushAttrib(GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		Traverser::traverseNode(outline->getRoot());
		glPushAttrib(GL_POLYGON_BIT);
			glPolygonMode(GL_FRONT, GL_FILL);
			for (mi=manipulators.begin(); mi!=manipulators.end(); ++mi) {
				if (mode == GL_SELECT)
					glPushName((*mi)->getID());
				(*mi)->copySizeOf(*node);
				(*mi)->draw();
			}
		glPopAttrib();
	glPopAttrib();
	
	// Restore shading and texturing
	if (program != NULL)
		program->apply();
	Texture::restart();
}


/** Paints all the items in a scene. */
void Painter::start() {
	
	Window::applyView();
	Traverser::start();
}

