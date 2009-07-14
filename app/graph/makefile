#
# makefile
#     Builds the Graph module.
#
# Author
#     Andy Brown <andybrown85@gmail.com>
#
MODULE = graph
MODS = data traits
CPPFLAGS = -I"./src" $(foreach M,$(MODS),-I"../$(M)/src")
DEFS = -DGL_GLEXT_PROTOTYPES -DILUT_USE_OPENGL
LIBS = $(addsuffix .a,$(MODS))
LIBDIRS = $(foreach M,$(MODS),../$(M)/lib)
VPATH = bin lib obj src $(LIBDIRS)
OBJS = Box.o Node.o Outline.o Scene.o Selection.o Shape.o Translation.o
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
all: $(MODULE).a
clean:
	rm obj/*.o


# Archives
$(MODULE).a : $(OBJS) 


# Objects
Box.o : Shape.o
Node.o : 
Outline.o : Shape.o
Scene.o : Node.o
Selection.o :
Shape.o : Node.o
Transformation.hpp : Node.o
Translation.o : Transformation.hpp
