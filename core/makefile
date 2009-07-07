CPPFLAGS = -Isrc -DGL_GLEXT_PROTOTYPES -DILUT_USE_OPENGL
LDFLAGS = -lglut -lIL -lILU -lILUT -lm
VPATH = bin:lib:obj:src
OBJECTS = Box.o Item.o Matrix.o Node.o Outline.o Quaternion.o \
          Scene.o Translation.o Vector.o
%.o : %.cpp %.hpp
	@echo "  $@"
	@g++ -ggdb -c $(CPPFLAGS) -o obj/$@ $(filter-out %.hpp, $<)
%.a :
	@echo "  $@"
	@ar cr "lib/$@" $(addprefix obj/, $(notdir $(OBJECTS)))


# Phony
.PHONY: all clean
all: Core.a
clean:
	rm obj/*.o


# Libraries
Core.a : $(OBJECTS)


# Objects
Box.o : Item.o Vector.o
Identifiable.hpp : 
Item.o : Identifiable.hpp Node.o Vector.o
Matrix.o : Vector.o
Node.o :
Outline.o : Item.o
Quaternion.o : Matrix.o Vector.o
Scene.o : Item.o Matrix.o Node.hpp Quaternion.o Shader.o Uniform.o Vector.o
Translation.o : Node.o Vector.o
Vector.o :
