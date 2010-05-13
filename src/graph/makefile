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

# Base classes
Identifiable.o:
Node.o:

# Sub classes
Applicable.hpp: Node.o
Drawable.o: Node.o Identifiable.o
Transformation.hpp: Applicable.hpp Node.o

# Collections
Selection.o: Drawable.o
Scene.o: Factory.o Node.o Selection.o
Traverser.o: Applicable.hpp Drawable.o Node.o Scene.o

# Utility
Factory.o: Node.o
Tester.o: Traverser.o
NodeNotifier.o: Node.o NodeEvent.hpp NodeListener.hpp
