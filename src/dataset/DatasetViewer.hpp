/*
 * DatasetViewer.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef DATASETVIEWER_HPP
#define DATASETVIEWER_HPP
#include "common.h"
#include "Dataset.hpp"
#include "Canvas.hpp"
#include "Toolkit.hpp"
using namespace std;


/** @brief Utility for viewing a dataset.
 * @ingroup graphics
 */
class DatasetViewer : public CanvasListener {
public:
	void goToNext();
	void goToPrevious();
	void load();
	void onCanvasEvent(const CanvasEvent &event);
	void onCanvasEventButton(const CanvasEvent &event);
	void onCanvasEventDisplay(const CanvasEvent &event);
	void onCanvasEventKey(const CanvasEvent &event);
	void setCanvas(Canvas *canvas);
	void setDataset(Dataset *dataset);
private:
	Dataset *dataset;
	GLenum type;
	int slice, width, height, depth;
	Canvas *canvas;
};
inline void DatasetViewer::setCanvas(Canvas *c) {canvas = c;}
inline void DatasetViewer::setDataset(Dataset *d) {dataset = d;}


#endif
