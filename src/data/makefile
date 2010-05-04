#
# makefile
#     Builds the Data module.
# 
# Author
#     Andrew Brown <adb1413@rit.edu>
#
MODULE := data
GANDER := ../..
include $(GANDER)/src/module.mak

# Exception
${filter-out Exception.o,$(OBJECTS)}: Exception.o

# Math
Vector.o: 
Matrix.o: Vector.o
Quaternion.o: Matrix.o Vector.o

# Volume
DatasetHeader.o: Tag.o
Dataset.o: DatasetHeader.o Tag.o
OctreeBuilder.o:
OctreeNode.o:
Slice.o: Dataset.o
VlbMaker.o: DatasetHeader.o

# XML and text
Tag.o : Text.o
Parser.o : Tag.o Text.o

# Files
FileUtility.o:
Preprocessor.o: FileUtility.o Text.o

# OpenGL
Window.o: Matrix.o Quaternion.o Vector.o
