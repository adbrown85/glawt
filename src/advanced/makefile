#
# makefile
#     Builds the Advanced module.
# 
# Author
#     Andrew Brown <adb1413@rit.edu>
#
MODULE := advanced
GANDER := ../..
include $(GANDER)/src/module.mak

# Factory
AdvancedFactory.o: ${filter-out AdvancedFactory.o,$(OBJECTS)}
$(BINARIES): AdvancedFactory.o

# Nodes
Boolean.o:
BooleanAnd.o: Boolean.o
BooleanXor.o: Boolean.o
Cull.o:
Framebuffer.o:
Fullscreen.o: 
Group.o:
Instance.o: Group.o
Octree.o: 
Target.o: Framebuffer.o
Wireframe.o:
