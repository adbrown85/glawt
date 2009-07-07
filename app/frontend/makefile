#
# makefile
#     Builds the Frontend module.
#
# Author
#     Andy Brown <andybrown85@gmail.com>
#
MODS = data graph backend
CPPFLAGS = -I"./src" $(foreach M,$(MODS),-I"../$(M)/src")
DEFS = -DGL_GLEXT_PROTOTYPES -DILUT_USE_OPENGL
LIBS = $(addsuffix .a,$(MODS))
LIBDIRS = $(foreach M,$(MODS),../$(M)/lib)
VPATH = bin lib obj src $(LIBDIRS)
OBJS = Binding.o Control.o Display.o Keyboard.o Menu.o \
       Mouse.o Picker.o Translator.o
OBJSWDIRS = $(addprefix obj/, $(notdir $(OBJS)))


# Rules for making archives and objects
%.o : %.cpp %.hpp $(LIBS)
	@echo "  $@"
	@g++ -ggdb -c $(CPPFLAGS) -o obj/$@ $<
%.a :
	@echo "  --> $@"
	@ar cr lib/$@ $(OBJSWDIRS)


# Phony
.PHONY: all clean
all: frontend.a
clean:
	rm obj/*.o


# Libraries
frontend.a : $(OBJS)


# Objects
Binding.o : 
Control.o : Binding.o Manipulator.hpp
Display.o : Control.o Manipulator.hpp
Keyboard.o : Binding.o Control.o
Manipulator.hpp : 
Menu.o : Control.o
Mouse.o : Binding.o Control.o Picker.o Translator.o
Picker.o : Translator.o
Translator.o : Manipulator.hpp
