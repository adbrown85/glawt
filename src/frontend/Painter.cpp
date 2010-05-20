/*
 * Painter.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Painter.hpp"
Scene *Painter::outline=NULL;
bool Painter::tried=false;


Painter::Painter(Scene *scene, GLenum mode) : Traverser(scene) {
	
	string filename(GANDER_DATA_DIR);
	
	this->mode = mode;
	
	if (!tried) {
		try {
			//BasicFactory::install();
			outline = new Scene();
			filename += "/ui/outline.xml";
			outline->open(filename);
			outline->prepare();
		} catch (Exception e) {
			delete outline;
			outline = NULL;
			cerr << "[Painter] Problem opening '" << filename << "'." << endl;
			cerr << "[Painter] Selected shapes will not be outlined." << endl;
			cerr << "[Painter] Try installing Gander again." << endl;
		}
		tried = true;
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
	
	// Disable shaders
	program = Program::getCurrent();
	if (program != NULL)
		program->remove();
	
	// Draw outline and manipulators
	glPushAttrib(GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		if (outline != NULL) {
			Traverser::traverseNode(outline->getRoot());
		}
		glPushAttrib(GL_POLYGON_BIT);
			glPolygonMode(GL_FRONT, GL_FILL);
			for (mi=manipulators.begin(); mi!=manipulators.end(); ++mi) {
				if ((*mi)->isEnabled()) {
					if (mode == GL_SELECT)
						glPushName((*mi)->getID());
					(*mi)->draw();
				}
			}
		glPopAttrib();
	glPopAttrib();
	
	// Restore shaders
	if (program != NULL)
		program->apply();
}


/** Paints all the items in a scene. */
void Painter::start() {
	
	Window::applyView();
	Traverser::start();
}

