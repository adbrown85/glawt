/*
 * TextureBuilder.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "TextureBuilder.hpp"


/** Builds a texture from a file. */
TextureInvoice TextureBuilder::build(const string &filename, bool compress) {
	
	prepare();
	assemble(filename);
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
	invoice.width     = analyzer.getWidth();
	invoice.height    = analyzer.getHeight();
	invoice.depth     = analyzer.getDepth();
	invoice.format    = PixelFormat::getFormat(analyzer.getFormat());
	invoice.footprint = analyzer.getFootprint();
	invoice.precision = analyzer.getBitsPerPixel();
}

