CPPFLAGS = -Isrc -DGL_GLEXT_PROTOTYPES -DILUT_USE_OPENGL
LDFLAGS = -lglut -lIL -lILU -lILUT -lm
VPATH = bin:obj:src
OBJECTS = Binding.o Box.o Cameraman.o Command.o Control.o \
          Compositor.o Director.o Display.o Grip.o Interpreter.o Item.o \
          Keyboard.o Matrix.o Menu.o Mouse.o Node.o Outline.o Parser.o \
          Picker.o Producer.o Quaternion.o Translation.o Translator.o \
          Scene.o Shader.o Uniform.o Vector.o
%.o : %.cpp %.hpp
	g++ -ggdb -c $(CPPFLAGS) -o obj/$@ $(filter-out %.hpp, $<)
% : %.o
	g++ -ggdb $(LDFLAGS) -o bin/$@ obj/$(notdir $<) \
	$(filter-out obj/$(notdir $<), $(addprefix obj/, $(OBJECTS)))


# Binaries
all: Application
Application : 
Producer : 


# Objects
Application.o : Display.o Interpreter.o Keyboard.o Menu.o Mouse.o Scene.o
Binding.o : Command.o
Box.o : Item.o Vector.o
Cameraman.o : Command.o Delegate.hpp Scene.o
Command.o : 
Control.o : Binding.o Delegate.hpp Manipulator.hpp Scene.o
Compositor.o : Command.o Delegate.hpp Scene.o
Delegate.hpp : Command.o Scene.o
Director.o :  Command.o Delegate.hpp Scene.o
Display.o :  Control.o Item.o Manipulator.hpp Matrix.o Node.o Outline.o \
             Quaternion.o Scene.o Vector.o
Grip.o : Command.o Delegate.hpp Scene.o
Identifiable.hpp : 
Interpreter.o : Cameraman.o Command.o Compositor.o Delegate.hpp Director.o  \
                Grip.o Producer.o Scene.o
Item.o : Identifiable.hpp Node.o Vector.o
Keyboard.o : Binding.o Command.o Control.o Delegate.hpp Scene.o
Mouse.o : Binding.o Command.o Control.o Delegate.hpp Manipulator.hpp Picker.o \
          Scene.o Translator.o Vector.o
Manipulator.hpp : Item.o Scene.o Vector.o
Matrix.o : Vector.o
Menu.o : Command.o Control.o Delegate.hpp Scene.o
Node.o :
Outline.o : Item.o
Parser.o : Tag.hpp
Picker.o : Item.o Manipulator.hpp Matrix.o Scene.o Translator.o
Producer.o : Box.o Command.o Delegate.hpp Item.o Node.o Parser.o Scene.o \
             Tag.hpp Translation.o Vector.o
Quaternion.o : Matrix.o Vector.o
Tag.hpp :
Translator.o : Item.o Manipulator.hpp Matrix.o Scene.o Vector.o
Translation.o : Node.o Vector.o
Scene.o : Item.o Matrix.o Node.hpp Quaternion.o Shader.o Uniform.o Vector.o
Shader.o : Uniform.o
Vector.o :


# Utility
.PHONY: all clean
clean:
	rm obj/*.o

