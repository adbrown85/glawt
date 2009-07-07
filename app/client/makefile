#
# makefile
#     Builds the Client module.
#
# Author
#     Andy Brown <andybrown85@gmail.com>
#
MODS = frontend backend graph data 
CPPFLAGS = -I./src $(foreach M,$(MODS),"-I../$(M)/src")
DEFS = -DGL_GLEXT_PROTOTYPES -DILUT_USE_OPENGL
LDFLAGS = -lglut -lIL -lILU -lILUT -lm
LIBS = $(addsuffix .a,$(MODS))
LIBDIRS = $(foreach M,$(MODS),../$(M)/lib)
LIBSWDIRS = $(foreach M,$(MODS),"../$(M)/lib/$(M).a")
VPATH = bin obj src $(LIBDIRS)
OBJS = Client.o
OBJSWDIRS = $(addprefix obj/, $(OBJS))


# Rules for making archives and objects
%.o : %.cpp %.hpp $(LIBS)
	@echo "  $@"
	@g++ -ggdb -c $(CPPFLAGS) $(DEFS) -o obj/$@ $<
% : %.o
	@echo "  --> $@"
	@g++ -ggdb $(LDFLAGS) -o bin/$@ $(OBJSWDIRS) $(LIBSWDIRS)


# Phony targets
.PHONY: all clean
all: Client
clean:
	rm obj/*.o


# Binaries
Client : 


# Objects
Client.o : 
