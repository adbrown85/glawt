#
# makefile
#     Builds the Data module.
#
# Author
#     Andy Brown <andybrown85@gmail.com>
#
MODULE = data
CHILDREN = 
FILTER = 
GANDER = ../..
include $(GANDER)/globals.mak
include $(GANDER)/src/module.mak


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

# XML
Tag.o :
Parser.o : Tag.o

# Files
FileUtility.o: 
Preprocessor.o: FileUtility.o
