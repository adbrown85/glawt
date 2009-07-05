CPPFLAGS = -Isrc -DGL_GLEXT_PROTOTYPES -DILUT_USE_OPENGL
LDFLAGS = -lglut -lIL -lILU -lILUT -lm
VPATH = bin:obj:src
OBJECTS = Application.o Binding.o Box.o Cameraman.o Command.o Control.o \
          Compositor.o Director.o Display.o Grip.o Interpreter.o Item.o \
          Keyboard.o Matrix.o Menu.o Mouse.o Outline.o Picker.o Producer.o \
          Quaternion.o Translator.o Scene.o Shader.o Uniform.o Vector.o
%.o : %.cpp %.hpp
	g++ -ggdb -c $(CPPFLAGS) -o obj/$@ $(filter-out %.hpp, $<)
% : %.o
	g++ -ggdb $(LDFLAGS) -o bin/$@ $(addprefix obj/, $(OBJECTS))


# Binaries
all: Application
Application : 


# Objects
Application.o : Box.o Display.o Interpreter.o Item.o Keyboard.o Menu.o \
                Mouse.o Scene.o Shader.o Uniform.o Vector.o
Binding.o : Command.o
Box.o : Item.o Vector.o
Cameraman.o : Command.o Delegate.hpp Scene.o
Command.o : 
Control.o : Binding.o Delegate.hpp Manipulator.hpp Scene.o
Compositor.o : Command.o Delegate.hpp Scene.o
Delegate.hpp : Command.o Scene.o
Director.o :  Command.o Delegate.hpp Scene.o
Display.o :  Control.o Item.o Manipulator.hpp Matrix.o Outline.o \
             Quaternion.o Scene.o Vector.o
Grip.o : Command.o Delegate.hpp Scene.o
Identifiable.hpp : 
Interpreter.o : Cameraman.o Command.o Compositor.o Delegate.hpp Director.o  \
                Grip.o Producer.o Scene.o
Item.o : Identifiable.hpp Vector.o
Keyboard.o : Binding.o Command.o Control.o Delegate.hpp Scene.o
Mouse.o : Binding.o Command.o Control.o Delegate.hpp Manipulator.hpp Picker.o \
          Scene.o Translator.o Vector.o
Manipulator.hpp : Item.o Scene.o Vector.o
Matrix.o : Vector.o
Menu.o : Command.o Control.o Delegate.hpp Scene.o
Outline.o : Item.o
Picker.o : Item.o Manipulator.hpp Matrix.o Scene.o Translator.o
Producer.o : Command.o Delegate.hpp Scene.o
Quaternion.o : Matrix.o Vector.o
Translator.o : Item.o Manipulator.hpp Matrix.o Scene.o Vector.o
Scene.o : Item.o Matrix.o Quaternion.o Shader.o Uniform.o Vector.o
Shader.o : Uniform.o
Vector.o :


# Utility
.PHONY: all clean
clean:
	rm obj/*.o

