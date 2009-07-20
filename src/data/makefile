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
include $(GANDER)/src/globals.mak
include $(GANDER)/src/module.mak


# Dependencies
Vector.o :
Matrix.o : Vector.o
Quaternion.o : Matrix.o Vector.o
