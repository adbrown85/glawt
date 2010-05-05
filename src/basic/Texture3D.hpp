/*
 * Texture3D.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TEXTURE3D_HPP
#define TEXTURE3D_HPP
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include "Dataset.hpp"
#include "Tag.hpp"
#include "Texture.hpp"
using namespace std;


/**
 * @ingroup basic
 * @brief %Texture node for volumes.
 */
class Texture3D : public Texture {
public:
	Texture3D(const Tag &tag);
	virtual void associate();
	static Texture3D* find(Node *node,
	                       const string &name);
	virtual Dataset* getDataset();
	virtual int getDepth() const;
	virtual int getHeight() const;
	virtual int getWidth() const;
protected:
	virtual void load();
private:
	Dataset dataset;
};


inline Dataset* Texture3D::getDataset() {return &dataset;}
inline int Texture3D::getDepth() const {return dataset.getDepth();}
inline int Texture3D::getHeight() const {return dataset.getHeight();}
inline int Texture3D::getWidth() const {return dataset.getWidth();}


#endif
