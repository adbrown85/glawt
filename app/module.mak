#
# module.mak
#     
#     Common actions and settings in building most modules.
#     
#     Pulls in all the source files for a module from 'src/' and all the test 
#     files from 'tests/'.  Uses '.cpp' suffix for class files and 
#     '.cxx' suffix for test files.  Note that these should be different so 
#     not to confuse make, plus it keeps things straight in your editor.
#     
#     After compiling a class into an object, the makefile immediately 
#     replaces that object in the archive.  This way the tests are
#     very easy to link.
#     
#     See the makefiles in the module directories for examples, but basically
#     just create a makefile with 'MODULE' and 'PREREQS' variables, where 
#     'MODULE' is the name of the module directory and 'PREREQS' is a 
#     whitespace-separated list of module directories this module depends
#     on.  Next, include this file after those variables, probably with 
#     'include ../module.mak'.  After that, simply write rules for the 
#     dependencies of objects of the form 'CLASS.o : DEPENDENCY.o ...' where
#     'CLASS' is the name of a class and 'DEPENDENCY' is the name of another
#     class it depends on.  Of course, there can be zero, one, or more 
#     dependencies.  Also, note that the module directory should have
#     'bin', 'lib', 'obj', 'src', and 'tests' subdirectories.
#     
#     Type 'make' from a module directory to build that module, and
#     'make tests' to build all the tests for that module.  You can also 
#     enter 'make CLASS' to build just the test for that class, which is
#     put into the 'bin' directory.
#     
#     Finally, please note that some modules may not fit into this
#     mold, especially top-level ones.
#
# 
# Author
#     Andy Brown <andybrown85@gmail.com>
#


# Compiler and linker options
INCLUDES = -I"./src" ${foreach P,$(PREREQS),-I"../$(P)/src"}
DEFINES = -DGL_GLEXT_PROTOTYPES -DILUT_USE_OPENGL
CPPFLAGS = -ggdb $(INCLUDES) $(DEFINES)
LDFLAGS = -lm -lglut -lIL -lILU -lILUT


# Files, full paths, and directories of objects/libraries/tests
OBJECTS = ${patsubst src/%.cpp,%.o,${wildcard src/*.cpp}}
OBJECTS_FULL = ${addprefix obj/, $(OBJECTS)}
LIBRARIES = ${addsuffix .a,$(PREREQS)}
LIBRARIES_DIRS = ${foreach P,$(PREREQS),../$(P)/lib}
LIBRARIES_FULL = ${foreach P,$(PREREQS),../$(P)/lib/$(P).a}
TESTS = ${patsubst tests/%.cxx,%,${wildcard tests/*.cxx}}


# Directories for make to search
VPATH = bin lib obj src tests $(LIBRARIES_DIRS)


# Phony targets for directing make
.PHONY : all allMessage clean message tests testsMessage
all : message allMessage $(MODULE).a
allMessage :
	@echo $(PWD)
	@echo "  Using 'src/*.cpp' for sources..."
	@echo $(OBJECTS)
clean : message
	@echo "  Removing objects, archives, and binaries..."
	@rm --force obj/*.o
	@rm --force lib/*
	@rm --force bin/*
message :
	@echo "$(MODULE)/"
tests : message testsMessage $(TESTS)
testsMessage :
	@echo "  Using 'tests/*.cxx' for tests..."


# Rule for archive from all the objects in this module
$(MODULE).a : $(OBJECTS)
	@echo "  --> lib/$@"


# Rule for object from source, header, and prerequisite libraries
%.o : %.cpp %.hpp $(LIBRARIES)
	@echo "  $<"
	@g++ -c $(CPPFLAGS) -o obj/$@ $<
	@ar cr lib/$(MODULE).a obj/$@


# Rule for binaries from test file, class object, and prerequisite libraries
% : %.cxx %.o $(LIBRARIES)
	@echo "  $< --> bin/$@"
	@g++ $(CPPFLAGS) $(LDFLAGS) -o bin/$@ $< lib/$(MODULE).a $(LIBRARIES_FULL)
