/*
 * Image.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Image.hpp"


/** Initialize filename and load the image. */
Image::Image(const string &filename) {
	
	// Load
	this->filename = filename;
	pixbuf = Gdk::Pixbuf::create_from_file(filename);
	width = pixbuf->get_width();
	height = pixbuf->get_height();
	
	// Format
	if (pixbuf->get_has_alpha()) {
		format = GL_RGBA;
	} else {
		format = GL_RGB;
	}
	
	// Store
	unpack();
}


/** Copy the pixels from the pixbuf without padding.
 * 
 * @throws Exception if image does not have 8 bits per sample.
 */
void Image::unpack() {
	
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
	strideUnpacked = width * channels;
	data = new GLchar[height*strideUnpacked];
	for (int i=0; i<height; ++i) {
		for (int j=0; j<strideUnpacked; ++j) {
			data[i*strideUnpacked+j] = pixels[i*stridePacked+j];
		}
	}
}

