/*
 * Painter.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Painter.hpp"
Scene *Painter::outline=NULL;
bool Painter::tried=false;


Painter::Painter(Canvas *canvas, Scene *scene) : Traverser(scene) {
	
	// Basics
	setCanvas(canvas);
	
	// Widgets
	if (!tried) {
		try {
			outline = new Scene();
			outline->open(Resources::get("ui/outline.xml"));
			outline->prepare();
		} catch (Exception e) {
			delete outline;
			outline = NULL;
			glog << "[Painter] Problem opening outline widget." << endl;
			glog << "[Painter] Selected shapes will not be outlined." << endl;
			glog << "[Painter] Try installing Gander again." << endl;
		}
		tried = true;
	}
}


Painter::~Painter() {
	
	if (outline != NULL) {
		delete outline;
		outline = NULL;
	}
}


void Painter::onDrawable(Node *node, Drawable *drawable) {
	
	Program *program;
	vector<Manipulator*>::iterator mi;
	Transformable *transformable;
	
	// Stop if not visible
	if (!drawable->isVisible())
		return;
	
	// Draw
	Traverser::onDrawable(node, drawable);
	
	// Stop if not selected
	if (!drawable->isSelected())
		return;
	
	// Disable shaders
	program = Program::getCurrent();
	if (program != NULL)
		program->remove();
	
	// Draw outline and manipulators
	transformable = dynamic_cast<Transformable*>(node);
	if (transformable != NULL) {
		glPushAttrib(GL_DEPTH_BUFFER_BIT);
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
			if (outline != NULL)
				Traverser::traverseNode(outline->getRoot());
			glPushAttrib(GL_POLYGON_BIT);
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				for (mi=manipulators.begin(); mi!=manipulators.end(); ++mi) {
					if ((*mi)->isEnabled()) {
						(*mi)->draw(transformable, getCanvas());
					}
				}
			glPopAttrib();
		glPopAttrib();
	}
	
	// Restore shaders
	if (program != NULL)
		program->apply();
}


/** Paints all the items in a scene. */
void Painter::start() {
	
	getCanvas()->getCamera()->apply();
	State::setMode(MODEL_MODE);
	State::loadIdentity();
	Traverser::start();
}

