#
# module.mak
#     Common actions and settings in building most modules.
#     
#     Automatically pulls in all the source files for a module from 
#     'src/MODULE'.  Uses '.cpp' suffix for class files and '.cxx' suffix
#     for test files.  Note that these should be different so not to confuse 
#     make, plus it keeps things straight in your editor.
#     
#     After compiling a class into an object, the makefile immediately 
#     replaces that object in the 'lib/gander.a' archive.  This way everything
#     is very easy to link.
#     
#     See the makefiles in the module directories for detailed usage, but 
#     basically just create a makefile in the 'src/MODULE' directory with a 
#     'MODULE' variable set to the name of the module.  Next, include this 
#     file with 'include ../module.mak'.
#     
#     After that, simply write rules for the dependencies of objects.  They 
#     should be of the form 'CLASS.o : DEPENDENCY.o ...' where
#     'CLASS' is the name of a class and 'DEPENDENCY' is the name of another
#     class it depends on.
#     
#     Type 'make' from a module directory to build that module, and
#     'make tests' to build all the tests for that module.  You can also 
#     enter 'make CLASS' to build just the test for that class, which is
#     put into the 'bin' directory.  Lastly, 'make check' will print some
#     information on the files the modules will use.
# 
# 
# Author
#     Andy Brown <andybrown85@gmail.com>
#


# Resolve directories
GANDER = ../..
VPATH = $(GANDER)/lib


# Resolve file paths
SOURCES = ${filter-out ${addsuffix .cpp,$(FILTER)}, ${wildcard *.cpp}}
OBJECTS = ${patsubst %.cpp,%.o,$(SOURCES)}
TESTS = ${wildcard *.cxx}
BINARIES = ${patsubst %.cxx,%,$(TESTS)}
ARCHIVE = $(GANDER)/lib/$(MODULE).a
LIBS = ${addsuffix .a,$(PREREQS)}


# Program options
ARFLAGS = cr
CXXFLAGS = -ggdb ${addprefix -I../,$(PREREQS)}
LDFLAGS = -lm -lglut -lIL -lILU -lILUT


# Phony targets for directing make
.PHONY : all check clean tests
${info $(MODULE)/}
all : $(MODULE).a
check :
	@echo "  ! SOURCES = $(SOURCES)"
	@echo "  ! TESTS   = $(TESTS)"
	@echo "  ! LIBS    = $(LIBS)"
clean :
	@echo "  ! Removing objects and binaries..."
	@$(RM) --force $(OBJECTS) $(BINARIES)
tests : all $(BINARIES)


# Build a class from its source files
%.o : %.cpp %.hpp
	@echo "  $<"
	@$(CXX) -c $(CXXFLAGS) $<
	@$(AR) -$(ARFLAGS) $(ARCHIVE) $@
	@ranlib $(ARCHIVE)


# Build an executable from a test and the archive
% : %.cxx $(MODULE).a
	@echo "  $< --> $@"
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^
