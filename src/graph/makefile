#
# makefile
#     Builds the Graph module.
#
# Author
#     Andy Brown <andybrown85@gmail.com>
#
MODULE = graph
CHILDREN = traits data
FILTER = 
GANDER = ../..
include $(GANDER)/src/globals.mak
include $(GANDER)/src/module.mak


# Basic node
Node.o:

# Drawable/Selectable nodes
Shape.o: Node.o
Box.o: Shape.o
Outline.o: Shape.o
Square.o: Shape.o

# Applicable nodes
Transformation.hpp: Node.o
Translation.o: Node.o Transformation.hpp
Program.o: Node.o
Shader.o: Node.o Program.o 
Texture.o : Node.o
Texture2D.o : Node.o Texture.o
Texture3D.o : Node.o Texture.o
Uniform.o: Node.o Program.o Shader.o Texture2D.o Texture3D.o

# Collections of nodes
Selection.o:
Scene.o: Node.o Selection.o
