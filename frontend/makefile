CPPFLAGS = -Isrc -I"../backend/src" -I"../core/src" \
           -DGL_GLEXT_PROTOTYPES -DILUT_USE_OPENGL
LDFLAGS = -lglut -lIL -lILU -lILUT -lm
VPATH = bin:lib:obj:src
OBJECTS = Binding.o Control.o Display.o Keyboard.o Menu.o \
          Mouse.o Picker.o Translator.o
%.o : %.cpp %.hpp
	@echo "  $@"
	@g++ -ggdb -c $(CPPFLAGS) -o obj/$@ $(filter-out %.hpp, $<)
%.a :
	@echo "  $@"
	@ar cr "lib/$@" $(addprefix obj/, $(notdir $(OBJECTS)))


# Phony
.PHONY: all clean
all: Frontend.a
clean:
	rm obj/*.o


# Libraries
Frontend.a : $(OBJECTS)


# Objects
Binding.o : 
Control.o : Binding.o Manipulator.hpp
Display.o : Control.o Manipulator.hpp
Keyboard.o : Binding.o Control.o
Manipulator.hpp : 
Menu.o : Control.o
Mouse.o : Binding.o Control.o Manipulator.hpp Picker.o Translator.o
Picker.o : Manipulator.hpp Translator.o
Translator.o : Manipulator.hpp
