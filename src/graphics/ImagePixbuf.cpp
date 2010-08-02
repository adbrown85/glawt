/*
 * ImagePixbuf.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ImagePixbuf.hpp"


ImagePixbuf::ImagePixbuf(const string &filename) : Image(filename) {
	
	// Load
	pixbuf = Gdk::Pixbuf::create_from_file(getFilename());
	setWidth(pixbuf->get_width());
	setHeight(pixbuf->get_height());
	
	// Format
	if (pixbuf->get_has_alpha()) {
		setFormat(GL_RGBA);
	} else {
		setFormat(GL_RGB);
	}
	
	// Store
	data = NULL;
	unpack();
}


/** Deletes the data. */
ImagePixbuf::~ImagePixbuf() {
	
	if (data != NULL) {
		delete[] data;
	}
}


/** Copy the pixels from the pixbuf without padding.
 * 
 * @throws Exception if image does not have 8 bits per sample.
 */
void ImagePixbuf::unpack() {
	
	guint8 *pixels;
	int bitsPerSample, channels, stridePacked, strideUnpacked;
	
	// Get info from pixbuf
	pixels = pixbuf->get_pixels();
	stridePacked = pixbuf->get_rowstride();
	channels = pixbuf->get_n_channels();
	bitsPerSample = pixbuf->get_bits_per_sample();
	
	// Verify
	if (bitsPerSample != 8) {
		throw Exception("[Image] Does not have 8 bits per sample.");
	}
	
	// Initialize the data
	strideUnpacked = getWidth() * channels;
	data = new GLchar[getHeight()*strideUnpacked];
	for (int i=0; i<getHeight(); ++i) {
		for (int j=0; j<strideUnpacked; ++j) {
			data[i*strideUnpacked+j] = pixels[i*stridePacked+j];
		}
	}
}

