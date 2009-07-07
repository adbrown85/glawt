#
# makefile
#     Builds the Backend module.
#
# Author
#     Andy Brown <andybrown85@gmail.com>
#
MODS = data graph
CPPFLAGS = -Isrc $(foreach M,$(MODS),"-I../$(M)/src")
DEFS = -DGL_GLEXT_PROTOTYPES -DILUT_USE_OPENGL
LIBS = $(addsuffix .a,$(MODS))
LIBDIRS = $(foreach M,$(MODS),../$(M)/lib)
VPATH = bin lib obj src $(LIBDIRS)
OBJS = Cameraman.o Command.o Compositor.o Director.o Grip.o \
       Interpreter.o Parser.o Producer.o
OBJSWDIRS = $(addprefix obj/, $(notdir $(OBJS)))


# Rules for making archives and objects
%.o : %.cpp %.hpp $(LIBS)
	@echo "  $@"
	@g++ -ggdb -c $(CPPFLAGS) $(DEFS) -o obj/$@ $<
%.a :
	@echo "  --> $@"
	@ar cr "lib/$@" $(OBJSWDIRS)


# Phony targets
.PHONY : all clean
all : backend.a
clean :
	rm obj/*.o


# Archives
backend.a : $(OBJS)


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

