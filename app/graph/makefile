#
# makefile
#     Builds the Graph module.  Use 'tests/*.cxx' for tests.
#
# Author
#     Andy Brown <andybrown85@gmail.com>
#
MODULE = graph
PREREQS = data traits
include ../module.mak


# Basic node
Node.o :

# Shape nodes
Shape.o : Node.o Translation.o
Box.o : Shape.o Node.o Translation.o
Outline.o : Shape.o Node.o Translation.o

# Transformation nodes
Transformation.hpp : Node.o
Translation.o : Transformation.hpp Node.o

# Collections of nodes
Selection.o :
Scene.o : Node.o Selection.o
