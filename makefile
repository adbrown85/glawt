CPPFLAGS = -Isrc -DGL_GLEXT_PROTOTYPES -DILUT_USE_OPENGL
LDFLAGS = -lglut -lIL -lILU -lILUT -lm
VPATH = bin:obj:src
OBJECTS = Binding.o Box.o Cameraman.o Command.o Control.o Compositor.o \
          Director.o Display.o Grip.o Interpreter.o Item.o Keyboard.o \
          Matrix.o Menu.o Mouse.o Outline.o Picker.o Producer.o \
          Quaternion.o Translator.o Scene.o Vector.o
%.o : %.cpp %.hpp
	g++ -ggdb -c $(CPPFLAGS) -o obj/$@ $(filter-out %.hpp, $<)
% : %.o
	g++ -ggdb $(LDFLAGS) -o bin/$@ $(addprefix obj/, $(OBJECTS))


# Binaries
all: Display
Display : Box.o Interpreter.o Keyboard.o Menu.o Mouse.o


# Objects
Binding.o : Command.o
Box.o : Item.o Vector.o
Cameraman.o : Command.o Delegate.hpp Scene.o State.hpp
Command.o : 
Control.o : Binding.o Manipulator.hpp Delegate.hpp Scene.o
Compositor.o : Command.o Delegate.hpp Scene.o
Director.o :  Command.o Delegate.hpp Scene.o
Display.o :  Control.o Item.o Outline.o Quaternion.o Scene.o
Grip.o : Command.o Delegate.hpp Scene.o State.hpp
Interpreter.o : Cameraman.o Command.o Compositor.o Director.o Delegate.hpp \
                Grip.o Producer.o
Item.o : Identifiable.hpp Vector.o
Keyboard.o : Binding.o Command.o Control.o Scene.o
Mouse.o : Binding.o Command.o Control.o Delegate.hpp Manipulator.hpp Picker.o \
          Scene.o Translator.o Vector.o
Matrix.o : Vector.o
Menu.o : Command.o Control.o Scene.o
Outline.o : Item.o
Picker.o : Item.o Manipulator.hpp Quaternion.o Scene.o
Producer.o : Command.o Delegate.hpp Scene.o State.hpp
Quaternion.o : Matrix.o Vector.o
Translator.o : Item.o Matrix.o Manipulator.hpp
Scene.o : Item.o Quaternion.o Vector.o
Vector.o :


# Utility
.PHONY: all clean
clean:
	rm obj/*.o

