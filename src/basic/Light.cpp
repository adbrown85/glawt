/*
 * Light.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Light.hpp"
Scene *Light::widget=NULL;
bool Light::tried=false;


/** Initializes attributes. */
Light::Light(const Tag &tag) : SimpleDrawable(tag), Nameable(tag) {
	
	// Intensities
	if (!tag.get("ambient", ambient, false)) {
		ambient = LIGHT_DEFAULT_AMBIENT;
	} if (!tag.get("diffuse", diffuse, false)) {
		diffuse = LIGHT_DEFAULT_DIFFUSE;
	} if (!tag.get("specular", specular, false)) {
		specular = LIGHT_DEFAULT_SPECULAR;
	}
	
	// Make sure can't select
	selectable = false;
	
	// Widget
	if (!tried) {
		try {
			widget = new Scene();
			widget->open(Resources::get("ui/light-widget.xml"));
			widget->prepare();
			traverser = new Traverser(widget);
		} catch (Exception e) {
			delete widget;
			widget = NULL;
			traverser = NULL;
			glog << "[Light] Problem opening light widget." << endl;
			glog << "[Light] Lights will not be visible." << endl;
			glog << "[Light] Try reinstalling Gander." << endl;
		}
		tried = true;
	}
}


/** Destroys the widget and traverser. */
Light::~Light() {
	
	if (widget != NULL) {
		delete widget;
		widget = NULL;
	}
	if (traverser != NULL) {
		delete traverser;
		traverser = NULL;
	}
}


/** Draws the widget representing the light. */
void Light::draw() const {
	
	if (traverser == NULL || widget == NULL)
		return;
	
	traverser->start();
}


Matrix Light::getLightMatrix() {
	
	Matrix biasMatrix(0.5, 0.0, 0.0, 0.5,
	                  0.0, 0.5, 0.0, 0.5,
	                  0.0, 0.0, 0.5, 0.5,
	                  0.0, 0.0, 0.0, 1.0);
	
	return biasMatrix
	         * State::getModelMatrix()
	         * getTransformationInverse()
	         * State::getProjectionMatrix();
}


void Light::getLightMatrix(GLfloat array[16]) {
	
	getLightMatrix().toArray(array);
}


/** @return Position of the light in view space coordinates. */
Vector Light::getPosition() {
	
	Vector pos;
	
	if (getCanvas() == NULL) {
		NodeException e(getTag());
		e << "[Light] Canvas is NULL!";
		throw e;
	}
	
	pos = SimpleDrawable::getPosition();
	return getCanvas()->getCamera()->getViewMatrix() * pos;
}


string Light::toString() const {
	
	ostringstream stream;
	
	stream << SimpleDrawable::toString();
	if (hasName())
		stream << " name='" << getName() << "'";
	stream << " ambient='" << ambient << "'"
	       << " diffuse='" << diffuse << "'"
	       << " specular='" << specular << "'";
	return stream.str();
}


Light* Light::search(Node *node, const string &name) {
	
	Light *light;
	Node::iterator it;
	queue<Node*> Q;
	
	Q.push(node);
	while (!Q.empty()) {
		node = Q.front();
		light = dynamic_cast<Light*>(node);
		if ((light != NULL) && (light->getName() == name))
			return light;
		for (it=node->begin(); it!=node->end(); ++it)
			Q.push((*it));
		Q.pop();
	}
	return NULL;
}

