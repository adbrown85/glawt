/*
 * TextureBuilder.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "TextureBuilder.hpp"


/** Builds a texture from a file. */
TextureInvoice TextureBuilder::build(const string &filename, bool compress) {
	
	check(filename);
	prepare();
	assemble(filename, compress);
	complete();
	package();
	return invoice;
}


/** Builds a texture from an order. */
TextureInvoice TextureBuilder::build(const TextureOrder &order) {
	
	prepare();
	assemble(order);
	complete();
	package();
	return invoice;
}


/** Checks that the file exists. */
void TextureBuilder::check(const string &filename) {
	
	ifstream file;
	bool opened;
	
	file.open(filename.c_str());
	opened = file;
	file.close();
	if (!opened) {
		Exception e;
		e << "[TextureBuilder] Could not open '" << filename << "'.";
		throw e;
	}
}


/** Generates and binds a new texture. */
void TextureBuilder::prepare() {
	
	invoice.type = getType();
	glGenTextures(1, &invoice.handle);
	glBindTexture(invoice.type, invoice.handle);
}


/** Records details in the invoice. */
void TextureBuilder::package() {
	
	TextureAnalyzer analyzer;
	
	// Setup
	analyzer.setTexture(invoice.type, invoice.handle);
	
	// Record
	invoice.width      = analyzer.getWidth();
	invoice.height     = analyzer.getHeight();
	invoice.depth      = analyzer.getDepth();
	invoice.format     = PixelFormat::getFormat(analyzer.getFormat());
	invoice.footprint  = analyzer.getFootprint();
	invoice.precision  = analyzer.getBitsPerPixel();
	invoice.compressed = analyzer.isCompressed();
}

