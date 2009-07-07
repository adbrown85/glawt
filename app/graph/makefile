#
# makefile
#     Builds the Graph module.
#
# Author
#     Andy Brown <andybrown85@gmail.com>
#
MODS = data
CPPFLAGS = -I"./src" $(foreach M,$(MODS),-I"../$(M)/src")
DEFS = -DGL_GLEXT_PROTOTYPES -DILUT_USE_OPENGL
LIBS = $(addsuffix .a,$(MODS))
LIBDIRS = $(foreach M,$(MODS),../$(M)/lib)
VPATH = bin lib obj src $(LIBDIRS)
OBJS = Box.o Item.o Node.o Outline.o Scene.o Translation.o
OBJSWDIRS = $(addprefix obj/, $(notdir $(OBJS)))


# Rules for making archives and objects
%.o : %.cpp %.hpp $(LIBS)
	@echo "  $@"
	@g++ -ggdb -c $(CPPFLAGS) $(DEFS) -o obj/$@ $<
%.a :
	@echo "  --> $@"
	@ar cr "lib/$@" $(OBJSWDIRS)


# Phony targets
.PHONY: all clean
all: graph.a
clean:
	rm obj/*.o


# Archives
graph.a : $(OBJS) 


# Objects
Box.o : Item.o
Item.o : Identifiable.hpp Node.o
Node.o : 
Outline.o : Item.o
Scene.o : Item.o Node.o
Translation.o : Node.o
