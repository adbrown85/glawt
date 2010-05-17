#
# makefile
#     Builds the Basic module.
# 
# Author
#     Andrew Brown <adb1413@rit.edu>
#
MODULE := basic
GANDER := ../..
include $(GANDER)/src/module.mak

# Factory
BasicFactory.o: ${filter-out BasicFactory.o,$(OBJECTS)}
$(BINARIES): BasicFactory.o

# Shaders
Program.o: 
Shader.o: Program.o
Uniform.o: Program.o Shader.o Texture.o
UNIFORMS = ${filter-out Uniform.o,${patsubst %.cpp,%.o,${wildcard Uniform*.cpp}}}
$(UNIFORMS): Uniform.o
check: checkUniforms
checkUniforms:
	@echo "  UNIFORMS = $(UNIFORMS)"

# Textures
TEXTURES = ${patsubst %.cpp,%.o,${wildcard Texture*D.cpp}}
$(TEXTURES): Texture.o
check: checkTextures
checkTextures:
	@echo "  TEXTURES = $(TEXTURES)"

# Shapes
Shape.o: Program.o
Hexahedron.o: Shape.o
Box.o: Hexahedron.o
Cube.o: Hexahedron.o
Square.o: Shape.o
Disk.o: Shape.o

# Transforms
Scale.o: Transformation.hpp
Translate.o: Transformation.hpp
