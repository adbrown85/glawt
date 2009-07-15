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
#     After compiling a class into an object, the makefile creates an 
#     archive for it.  The archive includes the object and the objects for
#     all classes in this module that it depends on.  This way the tests are
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
.PHONY : all clean message tests testsMessage
all : message $(MODULE).a
allMessage :
	@echo "  Using 'src/*.cpp' for sources."
clean : message
	@echo "  Removing objects, archives, and binaries..."
	@rm --force obj/*.o
	@rm --force lib/*
	@rm --force bin/*
message :
	@echo "$(MODULE)/"
tests : message testsMessage $(TESTS)
testsMessage :
	@echo "  Using 'tests/*.cxx' for tests."


# Rules for making an object from source, header, and prerequisite modules
%.o : %.cpp %.hpp $(LIBRARIES)
	@echo "  $<"
	@g++ -c $(CPPFLAGS) -o obj/$@ $<
	@ar cr lib/$*.a ${addprefix obj/,${notdir ${filter %.o,$@ $^}}}


# Rule for making tests from test, object, and prerequisite modules
% : %.cxx %.o $(LIBRARIES)
	@echo "  $<"
	@g++ $(CPPFLAGS) $(LDFLAGS) -o bin/$@ $< lib/$*.a $(LIBRARIES_FULL)
	@echo "  --> bin/$@"


# Rule for making the archive from all the objects in this module
$(MODULE).a : $(OBJECTS)
	@ar cr "lib/$@" $(OBJECTS_FULL)
	@echo "  --> lib/$@"
