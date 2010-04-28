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

# Variables
UNIFORMS = ${filter-out Uniform.o, ${patsubst %.cpp,%.o,${wildcard Uniform*.cpp}}}
TEXTURES = ${patsubst %.cpp,%.o,${wildcard Texture*D.cpp}}
FACTORIES = ${patsubst %.cpp,%.o,${wildcard *Factory.cpp}}
BASIC = Cube Program Scale Shader Square Texture Translation Uniform
ADVANCED = Cull Framebuffer Fullscreen Octree Target

# Basic
BasicFactory.o: ${addsuffix .o,$(BASIC)} $(TEXTURES) $(UNIFORMS)
Cube.o: Shape.o
Program.o: 
Scale.o: Transformation.hpp
Shader.o: Program.o
Shape.o: Program.o
Square.o: Shape.o
$(TEXTURES): Texture.o
Translation.o: Transformation.hpp
Uniform.o: Program.o Shader.o Texture.o
$(UNIFORMS): Uniform.o

# Advanced
AdvancedFactory.o: ${addsuffix .o,$(ADVANCED)}
Cull.o:
Framebuffer.o:
Fullscreen.o: Shape.o
Octree.o: Texture.o Texture3D.o
Target.o: Framebuffer.o Texture2D.o

# Testing
$(BINARIES): $(FACTORIES)

# Checks
check: checkUniforms checkFactories checkBasic checkAdvanced checkTextures
checkUniforms:
	@echo "  UNIFORMS = $(UNIFORMS)"
checkFactories:
	@echo "  FACTORIES = $(FACTORIES)"
checkTextures:
	@echo "  TEXTURES = $(TEXTURES)"
checkBasic:
	@echo "  BASIC    = $(BASIC)"
checkAdvanced:
	@echo "  ADVANCED = $(ADVANCED)"
