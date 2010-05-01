/*
 * Painter.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Painter.hpp"
Node* Painter::outline=NULL;


Painter::Painter(Scene *scene,
                 GLenum mode) : Traverser(scene) {
	
	this->mode = mode;
	
	if (outline == NULL) {
		BasicFactory::install();
		AdvancedFactory::install();
		outline = Factory::open("${GANDER}/glsl/outline.xml");
		outline->prepare();
	}
}


void Painter::onApplicable(Applicable *node) {
	
	Framebuffer *framebuffer;
	
	// Only continue if not a framebuffer node
	if (mode == GL_SELECT && (framebuffer = dynamic_cast<Framebuffer*>(node)))
		return;
	Traverser::onApplicable(node);
}


void Painter::onDrawable(Drawable *node) {
	
	// Load the name if selecting then draw
	if (mode == GL_SELECT)
		glLoadName(node->getID());
	Traverser::onDrawable(node);
}


/**
 * Paints manipulators and an outline for a selected shape.
 */
void Painter::onSelectable(Selectable *node) {
	
	Program *program;
	vector<Manipulator*>::iterator mi;
	
	// Disable shading and texture
	program = Program::getCurrent();
	if (program != NULL)
		program->remove();
	Texture::pause();
	
	// Draw outline
	if (outline != NULL) {
		Traverser::traverseNode(outline);
	}
	
	// Draw manipulators
	glPushAttrib(GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
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


/**
 * Paints all the items in a scene.
 */
void Painter::start() {
	
	Window::applyView();
	Traverser::start();
}

