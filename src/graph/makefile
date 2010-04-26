#
# makefile
#     Builds the Graph module.
# 
# Author
#     Andrew Brown <adb1413@rit.edu>
#
MODULE = graph
CHILDREN = base data
FILTER = 
GANDER = ../..
include $(GANDER)/globals.mak
include $(GANDER)/src/module.mak


# Transformations
Translation.o: 
Scale.o: 

# Textures
Texture2D.o: 
Texture3D.o: 
Octree.o: Texture3D.o

# Rendering
Cull.o: 
Framebuffer.o: 
Target.o: Framebuffer.o Texture2D.o

# Shaders
Program.o: 
Shader.o: Program.o
UNIFORMS = ${filter-out Uniform.o UniformFactory.o, ${wildcard Uniform*.o}}
Uniform.o: Program.o Shader.o Texture2D.o Texture3D.o
$(UNIFORMS): Uniform.o
UniformFactory.o: $(UNIFORMS)
check: checkUniforms
checkUniforms:
	@echo "  UNIFORMS = $(UNIFORMS)"

# Shapes
Fullscreen.o: 
Cube.o: Program.o
Square.o: Program.o
