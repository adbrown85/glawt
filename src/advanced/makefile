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

# Geometry
Boolean.o:
BooleanAnd.o: Boolean.o
BooleanXor.o: Boolean.o
Fullscreen.o: 
Group.o:
Instance.o: Group.o

# Rendering
Cull.o:
Wireframe.o:
Framebuffer.o:
Attachment.o: Framebuffer.o
Bind.o: Attachment.o
Target.o: Attachment.o

# Acceleration
Octree.o: 
