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
include $(GANDER)/globals.mak
include $(GANDER)/src/module.mak


# Basic node
Node.o:

# Applicable nodes
Cull.o: Node.o
Framebuffer.o: Node.o
Light.o: Node.o
LightColor.o: Node.o Light.o
Transformation.hpp: Node.o
Translation.o: Node.o Transformation.hpp
Octree.o: Texture3D.o Texture.o
Program.o: Node.o
Target.o: Framebuffer.o Node.o Texture2D.o
Texture.o : Node.o
Texture2D.o : Node.o Texture.o
Texture3D.o : Node.o Texture.o
Uniform.o: Node.o Program.o Shader.o Texture2D.o Texture3D.o

# Sub nodes
Shader.o: Node.o Program.o
Ambient.o: LightColor.o
Diffuse.o: LightColor.o
Position.o: Light.o
Specular.o: LightColor.o

# Drawable/Selectable nodes
Fullscreen.o: Node.o
Shape.o: Node.o
Box.o: Shape.o Texture.o
Outline.o: Shape.o
Square.o: Shape.o Texture.o

# Collections of nodes
Selection.o: Node.o
Factory.o: ${filter-out Factory.o Scene.o Tester.o, $(OBJECTS)}
Scene.o: Node.o Factory.o Selection.o
Tester.o: Scene.o

# Binaries
Scene: Shape.o Translation.o
Shape: Translation.o
Tester: 
