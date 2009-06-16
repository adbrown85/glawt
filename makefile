CPPFLAGS = -Isrc -DGL_GLEXT_PROTOTYPES -DILUT_USE_OPENGL
LDFLAGS = -lglut -lIL -lILU -lILUT -lm
VPATH = bin:obj:src
OBJECTS = Binding.o \
          Box.o \
          Cameraman.o \
          Command.o \
          Compositor.o \
          Display.o \
          Director.o \
          Grip.o \
          Interpreter.o \
          Item.o \
          Keyboard.o \
          Menu.o \
          Mouse.o \
          Outline.o \
          Producer.o \
          Scene.o \
          Vector.o
%.o : %.cpp %.hpp
	g++ -c $(CPPFLAGS) -o obj/$@ $(filter-out %.hpp, $<)
% : %.o
	g++ $(LDFLAGS) -o bin/$@ $(addprefix obj/, $(OBJECTS))


# Binaries
all: Display
Display :


# Objects
Binding.o : Command.o
Box.o : Item.o Vector.o
Camerman.o : Command.o Delegate.hpp Scene.o State.hpp
Command.o : 
Compositor.o : Command.o Delegate.hpp Scene.o State.hpp
Director.o : Command.o Delegate.hpp Scene.o State.hpp
Display.o : Box.o Control.hpp Keyboard.o Interpreter.o Item.o Menu.o Mouse.o Outline.o Scene.o
Grip.o : Command.o Delegate.hpp Scene.o State.hpp
Interpreter.o : Cameraman.o \
                Command.o \
                Compositor.o \
                Director.o \
                Delegate.hpp \
                Grip.o \
                Producer.o
Item.o : Identifiable.hpp Vector.o
Keyboard.o : Binding.o Command.o Control.hpp Scene.o State.hpp
Mouse.o : Command.o Control.hpp Scene.o State.hpp
Menu.o : Command.o Control.hpp Scene.o State.hpp
Outline.o : Item.o
Producer.o : Command.o Delegate.hpp Scene.o State.hpp
Scene.o : Item.o Vector.o
Vector.o :


# Utility
.PHONY: all clean
clean:
	rm obj/*.o

