/*
 * Attachment.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Attachment.hpp"


class AttachmentTest {
public:
	void testColorAttachments();
	void testMaxColorAttachments();
	void testMaxDrawBuffers();
};


void AttachmentTest::testMaxDrawBuffers() {
	
	cout << "Max draw buffers: " << endl;
	cout << GL_MAX_DRAW_BUFFERS << endl;
}


void AttachmentTest::testMaxColorAttachments() {
	
	cout << "\nMax color attachments: " << endl;
	cout << GL_MAX_COLOR_ATTACHMENTS << endl;
}


void AttachmentTest::testColorAttachments() {
	
	cout << "\nColor attachments..." << endl;
	cout << GL_COLOR_ATTACHMENT0 << endl;
	cout << GL_COLOR_ATTACHMENT1 << endl;
	cout << GL_COLOR_ATTACHMENT2 << endl;
	cout << GL_COLOR_ATTACHMENT3 << endl;
	cout << GL_COLOR_ATTACHMENT4 << endl;
	cout << GL_COLOR_ATTACHMENT5 << endl;
	cout << GL_COLOR_ATTACHMENT6 << endl;
}


int main(int argc,
         char *argv[]) {
	
	AttachmentTest test;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Attachment" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	test.testMaxDrawBuffers();
	test.testMaxColorAttachments();
	test.testColorAttachments();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Attachment" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}

