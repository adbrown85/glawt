#
# makefile
#     Builds the Graph module.
# 
# Author
#     Andrew Brown <adb1413@rit.edu>
#
MODULE := graph
GANDER := ../..
include $(GANDER)/src/module.mak

# Factory
Factory.o: Node.o

# Base classes
Identifiable.o: 
Node.o:

# Sub classes
Applicable.hpp:
Drawable.o: Node.o Identifiable.o
Selectable.o: Drawable.o
Transformation.hpp: Applicable.hpp Node.o

# Collections
Selection.o: Selectable.o
Scene.o: Factory.hpp Node.o Selection.o
Traverser.o: Applicable.hpp Drawable.o Selectable.o Node.o Scene.o

# Testing
Tester.o: Applicable.hpp Drawable.o Selectable.o Node.o Scene.o
