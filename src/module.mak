#
# make-module.mak
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
#     Unless you are doing unit testing or working exclusively in one module,
#     makefiles for modules should not be run directly.  Run make from the 
#     'src' directory, which will pick up changes in all modules.
# 
# 
# Author
#     Andy Brown <andybrown85@gmail.com>
#


# Resolve file paths for module
SOURCES = ${filter-out ${addsuffix .cpp,$(FILTER)}, ${wildcard *.cpp}}
OBJECTS = ${patsubst %.cpp,%.o,$(SOURCES)}
TESTS = ${wildcard *.cxx}
BINARIES = ${patsubst %.cxx,%,$(TESTS)}


# Phony targets for directing make
DIRECTIVES = all check clean tests
.PHONY : $(DIRECTIVES)  child
$(DIRECTIVES) : child message
all : $(OBJECTS) tests
check : 
	@echo "  FILTER  = $(FILTER)"
	@echo "  SOURCES = $(SOURCES)"
	@echo "  TESTS   = $(TESTS)"
	@echo "  CHILD   = $(CHILD)"
child :
ifdef CHILD
	@$(MAKE) -C "../$(CHILD)" $(MAKECMDGOALS)
endif
clean :
	@echo "  Removing $(OBJECTS)"
	@$(RM) $(OBJECTS) 
	@echo "  Removing $(BINARIES)"
	@$(RM) $(BINARIES)
message:
	@echo "$(MODULE)"
tests : $(OBJECTS) $(BINARIES)



# Build a class from its source files, copy to archive
%.o : %.cpp %.hpp
	@echo "  $<"
	@$(CXX) -c $(CXXFLAGS) ${abspath $<}
	@$(AR) -$(ARFLAGS) $(ARCHIVE) $@
	@ranlib $(ARCHIVE)


# Build an executable from a test and archive
% : %.cxx %.o
	@echo "  $< --> $@"
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ ${abspath $<} $(ARCHIVE)
