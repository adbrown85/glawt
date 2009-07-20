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
.PHONY : $(DIRECTIVES) $(MODULES)
$(DIRECTIVES): $(MODULES)
clean:
	$(RM) $(bindir)/gander

# Compile all the objects
$(MODULES):
	@$(MAKE) -C ./$@ $(MAKECMDGOALS)


# Gander executable
gander : gander.cpp gander.hpp
	@echo "$< --> gander"
#	@$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ ${abspath $<} $(ARCHIVES)
