#
# makefile
#     Builds the Graph module.
#
# Author
#     Andy Brown <andybrown85@gmail.com>
#
MODULE = graph
CHILD  = traits
FILTER = Shader Uniform
GANDER = ../..
include $(GANDER)/src/globals.mak
include $(GANDER)/src/module.mak


# Basic node
Node.o :

# Shape nodes
Shape.o : Node.o Translation.o
Box.o : Shape.o
Outline.o : Shape.o

# Transformation nodes
Transformation.hpp : Node.o
Translation.o : Transformation.hpp

# Collections of nodes
Selection.o :
Scene.o : Node.o Selection.o
