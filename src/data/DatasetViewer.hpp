/*
 * DatasetViewer.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef DATASETVIEWER_HPP
#define DATASETVIEWER_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include <gtkmm/frame.h>
#include "Dataset.hpp"
#include "Canvas.hpp"
using namespace std;


/** @brief Utility for viewing a dataset.
 * @ingroup data
 */
class DatasetViewer : public Gtk::Frame {
public:
	DatasetViewer();
	void draw();
	void goToNext();
	void goToPrevious();
	static void onDisplay(void);
	static void onMouse(int button, int state, int x, int y);
	static void onSpecial(int key, int x, int y);
	void setDataset(Dataset *dataset);
private:
	Dataset *dataset;
	GLenum type;
	int slice, width, height, depth;
	Canvas *canvas;
	static DatasetViewer *instance;
};


#endif
