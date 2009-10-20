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
ARCHIVE = $(libdir)/$(MODULE).a
ARCHIVES = ${foreach C,$(CHILDREN),$(libdir)/$(C).a}


# Phony targets for directing make
.PHONY: all check clean mostlyclean tests
all: $(OBJECTS) $(BINARIES)
check: 
	@echo "  FILTER   = $(FILTER)"
	@echo "  SOURCES  = $(SOURCES)"
	@echo "  OBJECTS  = $(OBJECTS)"
	@echo "  TESTS    = $(TESTS)"
	@echo "  BINARIES = $(BINARIES)"
	@echo "  ARCHIVE  = $(ARCHIVE)"
	@echo "  ARCHIVES = $(ARCHIVES)"
clean: 
	@echo "  Removing $(OBJECTS)"
	@$(RM) $(OBJECTS) 
	@echo "  Removing $(ARCHIVE)"
	@$(RM) $(ARCHIVE)
	@echo "  Removing $(BINARIES)"
	@$(RM) $(BINARIES)
mostlyclean: 
	@echo "  Removing $(OBJECTS)"
	@$(RM) $(OBJECTS)
install: all
tests: $(OBJECTS) $(BINARIES)


# Build objects from their source files, copy to archive
$(OBJECTS):
%.o : %.cpp %.hpp $(addsuffix .a,$(CHILDREN))
	@echo "  $<"
	@$(CXX) -c $(CXXFLAGS) $<
	@$(AR) -$(ARFLAGS) $(ARCHIVE) $@
	@ranlib $(ARCHIVE)


# Build executables from their tests and objects
$(BINARIES): 
%: %.cxx %.o $(addsuffix .a,$(CHILDREN))
	@echo "  $< --> $@"
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $< $(ARCHIVE) $(ARCHIVES)
