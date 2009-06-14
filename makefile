CPPFLAGS = -Isrc -DGL_GLEXT_PROTOTYPES -DILUT_USE_OPENGL
LDFLAGS = -lglut -lIL -lILU -lILUT
VPATH = bin:obj:src
OBJECTS = Box.o Item.o Vector.o
%.o : %.cpp %.hpp
	g++ -c $(CPPFLAGS) -o obj/$@ $(filter-out %.hpp, $<)
% : %.o
	g++ $(LDFLAGS) -o bin/$@ $(addprefix obj/, $(OBJECTS))


# Binaries
all: Item
Application :
Box : 
Command : 
Display :
Interpreter : 
Item : 
Scene : 
Shader : 
Uniform :


# Objects
Application.o : Box.o Scene.o Shader.o Uniform.o
Box.o : Item.o Vector.o
Command.o : 
Controls.o : Scene.o
Display.o : Box.o Controls.o Item.o Menu.o Scene.o
Interpreter.o : Commands.hpp
Item.o : Vector.o Identifiable.hpp
Menu.o : Scene.o
Scene.o : Box.o Item.o Shader.o Vector.o
Shader.o : Uniform.o
Uniform.o :
Vector.o :


# Utility
.PHONY: all clean
clean:
	rm obj/*.o

