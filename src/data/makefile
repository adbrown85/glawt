#
# makefile
#     Builds the Data module.
#
# Author
#     Andy Brown <andybrown85@gmail.com>
#
MODULE = data
NEEDS  = 
FILTER = 
GANDER = ../..
include $(GANDER)/make-globals.mak
include $(GANDER)/make-module.mak


# Dependencies
Vector.o :
Matrix.o : Vector.o
Quaternion.o : Matrix.o Vector.o
