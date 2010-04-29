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
Cull.o:
Framebuffer.o:
Fullscreen.o: 
Octree.o: 
Target.o: Framebuffer.o
Wireframe.o:
