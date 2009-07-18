#
# makefile
#     Builds Gander from its modules.
# 
# Author
#     Andy Brown <andybrown85@gmail.com>
#
GANDER = ..
include $(GANDER)/src/globals.mak


# Phony targets for directing make
DIRECTIVES = all check clean tests
.PHONY : $(DIRECTIVES) depends
$(DIRECTIVES) : depends
all : gander
check : 
	@echo
	@echo "bindir  = $(bindir)"
	@echo "libdir  = $(libdir)"
	@echo "srcdir  = $(srcdir)"
	@echo "ARCHIVE = $(ARCHIVE)"
	@echo "MODULES = $(MODULES)"
	@echo
clean :
	$(RM) $(ARCHIVE) 
	$(RM) $(bindir)/gander
depends :
	@$(MAKE) --directory ./graph --quiet $(MAKECMDGOALS)


# Gander executable
gander : gander.cpp gander.hpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ ${abspath $<} $(ARCHIVE)
