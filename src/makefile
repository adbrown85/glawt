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

# Compile all the objects
$(MODULES):
	@$(MAKE) -C ./$@ $(MAKECMDGOALS)
