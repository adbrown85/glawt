#
# makefile
#     Builds the Base module.
# 
# Author
#     Andrew Brown <adb1413@rit.edu>
#
MODULE = base
CHILDREN = data
FILTER = 
GANDER = ../..
include $(GANDER)/globals.mak
include $(GANDER)/src/module.mak


# Altering
Applicable.hpp:
Transformation.hpp: Applicable.hpp Node.o

# Drawing
Identifiable.o: 
Drawable.o: Identifiable.o
Selectable.o: Drawable.o
Texture.o: Applicable.hpp Node.o

# Basics
Node.o:
Shape.o: Node.o Selectable.o

# Collections
Selection.o: Selectable.o
