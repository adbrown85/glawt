/*
 * Tester.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TESTER_HPP
#define TESTER_HPP
#include "common.h"
#include <gtkmm/main.h>
#include <gtkmm/window.h>
#include "Node.hpp"
#include "FileUtility.hpp"
#include "Scene.hpp"
#include "Traverser.hpp"
#include "CanvasGTK.hpp"
using namespace std;


/** @brief Utility for testing nodes.
 * @ingroup graph
 */
class Tester : public CanvasListener {
public:
	void display(void);
	string getFilename();
	Scene* getScene();
	void onCanvasEvent(const CanvasEvent &event);
	void onCanvasEventDisplay(const CanvasEvent &event);
	void onCanvasEventKey(const CanvasEvent &event);
	void open(const string &filename);
	void start();
private:
	Traverser *traverser;
	Scene *scene;
	Canvas *canvas;
	Camera *camera;
};

inline Scene* Tester::getScene() {return scene;}
inline string Tester::getFilename() {return scene->getFilename();}


#endif
