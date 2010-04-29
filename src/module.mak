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
#     Andrew Brown <adb1413@rit.edu>
#
include $(GANDER)/globals.mak

# Resolve file paths for module
SOURCES := ${wildcard *.cpp}
OBJECTS := ${patsubst %.cpp,%.o,$(SOURCES)}
MAINS := ${wildcard *.cxx}
BINARIES := ${patsubst %.cxx,%,$(MAINS)}
ARCHIVE := $(MODULE).a
LIBRARY := $(libdir)/$(ARCHIVE)
CHILDREN := ${call before,$(MODULE),$(MODULES)}
ARCHIVES := ${addsuffix .a,${call reverse,$(CHILDREN)}}
LIBRARIES := ${addprefix $(libdir)/,$(ARCHIVES)}

# Phony targets for directing make
.PHONY: all check clean mostlyclean tests
all: $(OBJECTS) $(BINARIES)
check: 
	@echo "  SOURCES  = $(SOURCES)"
	@echo "  OBJECTS  = $(OBJECTS)"
	@echo "  MAINS    = $(MAINS)"
	@echo "  BINARIES = $(BINARIES)"
	@echo "  ARCHIVE  = $(ARCHIVE)"
	@echo "  ARCHIVES = $(ARCHIVES)"
clean: 
	@echo "  Removing $(OBJECTS)"
	@$(RM) $(OBJECTS) 
	@echo "  Removing $(LIBRARY)"
	@$(RM) $(LIBRARY)
	@echo "  Removing $(BINARIES)"
	@$(RM) $(BINARIES)
mostlyclean: 
	@echo "  Removing $(OBJECTS)"
	@$(RM) $(OBJECTS)
install: all
tests: $(OBJECTS) $(BINARIES)

# Build objects from their source files, copy to archive
$(OBJECTS):
%.o : %.cpp %.hpp $(ARCHIVES)
	@echo "  $<"
	@$(CXX) -c $(CXXFLAGS) $<
	@$(AR) -$(ARFLAGS) $(LIBRARY) $@
	@ranlib $(LIBRARY)

# Build executables from their tests and objects
$(BINARIES): 
%: %.cxx %.o $(ARCHIVES)
	@echo "  $< --> $@"
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $< $(LIBRARY) $(LIBRARIES)
