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
TransformFactory.o: Scale.o Translation.o

# Textures
Texture2D.o: Texture.o
Texture3D.o: Texture.o
Octree.o: Texture.o Texture3D.o
TextureFactory.o: Texture2D.o Texture3D.o Octree.o

# Rendering
Cull.o: 
Framebuffer.o: 
Target.o: Framebuffer.o Texture2D.o
RenderFactory.o: Cull.o Framebuffer.o Target.o

# Shaders
Program.o: 
Shader.o: Program.o
Uniform.o: Program.o Shader.o Texture.o
UNIFORMS = ${filter-out Uniform.o, ${patsubst %.cpp,%.o,${wildcard Uniform*.cpp}}}
$(UNIFORMS): Uniform.o
ShaderFactory.o: Program.o Shader.o $(UNIFORMS)

# Shapes
Shape.o: Program.o
Fullscreen.o: Shape.o
Cube.o: Shape.o
Square.o: Shape.o
ShapeFactory.o: Cube.o Fullscreen.o Square.o

# Testing
FACTORIES = ${patsubst %.cpp,%.o,${wildcard *Factory.cpp}}
$(BINARIES): $(FACTORIES)

# Checks
check: checkUniforms checkFactories
checkUniforms:
	@echo "  UNIFORMS = $(UNIFORMS)"
checkFactories:
	@echo "  FACTORIES = $(FACTORIES)"
