/*
 * Texture3D.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TEXTURE3D_HPP
#define TEXTURE3D_HPP
#include "common.h"
#include <ctime>                        // For clocking compression
#include "Dataset.hpp"
#include "Tag.hpp"
#include "Texture.hpp"
using namespace std;
using System::glog;


/** @brief %Texture node for volumes.
 * @ingroup basic
 */
class Texture3D : public Texture {
public:
	Texture3D(const Tag &tag);
	virtual ~Texture3D();
	virtual void finalize();
	static Texture3D* find(Node *node, const string &name);
	virtual Dataset* getDataset();
	virtual GLenum getInternalFormat() const;
	virtual GLint getRawFootprint() const;
	virtual int getWidth() const;
	virtual int getHeight() const;
	virtual int getDepth() const;
	virtual string toString() const;
private:
	bool compress;
	Dataset *dataset;
};

inline Dataset* Texture3D::getDataset() {return dataset;}
inline int Texture3D::getDepth() const {return dataset->getDepth();}
inline int Texture3D::getHeight() const {return dataset->getHeight();}
inline int Texture3D::getWidth() const {return dataset->getWidth();}


#endif
