#
# makefile
#     Common actions and settings in building most modules.
#
# Author
#     Andy Brown <andybrown85@gmail.com>
#


# Compiler and linker options
CPPFLAGS = -I"./src" $(foreach P,$(PREREQUISITES),-I"../$(P)/src")
DEFINES = -DGL_GLEXT_PROTOTYPES -DILUT_USE_OPENGL
LDFLAGS = -lm


# Basenames, full paths, and directories of archives/objects
ARCHIVES = $(addsuffix .a,$(PREREQUISITES))
ARCHIVES_DIRS = $(foreach P,$(PREREQUISITES),../$(P)/lib)
ARCHIVES_FULL = $(foreach P,$(PREREQUISITES),../$(P)/lib/$(P).a)
OBJECTS_FULL = $(addprefix obj/, $(notdir $(OBJECTS)))


# Directories for make to search (using VPATH for compatibility)
VPATH = bin lib obj src tests $(ARCHIVES_DIRS)


# Implicit rules for objects, archives, and tests
%.o : %.cpp %.hpp $(ARCHIVES)
	@echo "  $<"
	@g++ -ggdb -c $(CPPFLAGS) $(DEFINES) -o obj/$@ $<
%.a :
	@echo "  --> lib/$@"
	@ar cr "lib/$@" $(OBJECTS_FULL)
%-test : %-test.cpp %.o $(MODULE).a $(ARCHIVES)
	@echo "  $<"
	@g++ $(CPPFLAGS) $(LDFLAGS) -o bin/$@ $< lib/$(MODULE).a $(ARCHIVES_FULL)
	@echo "  --> bin/$@"


# Phony targets for directing make
.PHONY : all clean message tests
all : message $(MODULE).a
clean : message
	@echo "  Removing objects and tests..."
	@rm --force obj/*.o
	@rm --force bin/*
message :
	@echo $(MODULE)
tests : message $(addsuffix -test,$(TESTS))


# Objects to put in this module's archive
$(MODULE).a : $(OBJECTS)
