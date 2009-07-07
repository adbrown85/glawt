CPPFLAGS = -Isrc -I"../core/src" \
           -DGL_GLEXT_PROTOTYPES -DILUT_USE_OPENGL
LDFLAGS = -lglut -lIL -lILU -lILUT -lm
VPATH = bin:lib:obj:src
OBJECTS = Cameraman.o Command.o Compositor.o Director.o Grip.o \
          Interpreter.o Parser.o Producer.o
%.o : %.cpp %.hpp
	@echo "  $@"
	@g++ -ggdb -c $(CPPFLAGS) -o obj/$@ $(filter-out %.hpp, $<)
%.a :
	@echo "  $@"
	@ar cr "lib/$@" $(addprefix obj/, $(notdir $(OBJECTS)))


# Phony
.PHONY : all clean
all : Backend.a
clean :
	rm obj/*.o


# Libraries
Backend.a : $(OBJECTS)


# Objects
Cameraman.o : Delegate.hpp
Command.o : 
Compositor.o : Delegate.hpp
Delegate.hpp : Command.o
Director.o :  Delegate.hpp
Grip.o : Delegate.hpp
Interpreter.o : Cameraman.o Compositor.o Director.o Grip.o Producer.o
Parser.o : Tag.hpp
Producer.o : Delegate.hpp Parser.o
Tag.hpp :

