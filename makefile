CPPFLAGS = -Isrc -DGL_GLEXT_PROTOTYPES -DILUT_USE_OPENGL
LDFLAGS = -lglut -lIL -lILU -lILUT
VPATH = bin:obj:src
#          Display.o
OBJECTS = Box.o  \
          Controls.o \
          Item.o  \
          Interpreter.o  \
          Menu.o  \
          Scene.o  \
          Shader.o  \
          Uniform.o  \
          Vector.o
%.o : %.cpp %.hpp
	g++ -c $(CPPFLAGS) -o obj/$@ $(filter-out %.hpp, $<)
% : %.o
	g++ $(LDFLAGS) -o bin/$@ $(addprefix obj/, $(OBJECTS))


# Binaries
all: Interpreter
Application :
Box : 
Display :
Interpreter : 
Item : 
Scene : 
Shader : 
Uniform :


# Objects
Application.o : Box.o Scene.o Shader.o Uniform.o
Box.o : Item.o Vector.o
Controls.o : Scene.o
Display.o : Box.o Controls.o Item.o Menu.o Scene.o
Interpreter.o : Commands.hpp
Item.o : Vector.o
Menu.o : Scene.o
Scene.o : Box.o Item.o Shader.o Vector.o
Shader.o : Uniform.o
Uniform.o :
Vector.o :


# Utility
.PHONY: clean
clean:
	rm obj/*.o

