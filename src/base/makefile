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


# Applicable
Applicable.hpp:
Transformation.hpp: Applicable.hpp Node.o

# Drawable
Identifiable.o: 
Drawable.o: Identifiable.o
Selectable.o: Drawable.o

# Basics
Node.o:
Selection.o: Selectable.o
Scene.o: Factory.hpp Node.o Selection.o

# Testing
Tester.o: Applicable.hpp Drawable.o Node.o Scene.o
