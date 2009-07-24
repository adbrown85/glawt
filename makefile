#
# makefile
#     Builds Gander from its modules.
# 
# Author
#     Andy Brown <andybrown85@gmail.com>
#
GANDER = .
include $(GANDER)/src/globals.mak


# Phony targets for directing make
DIRECTIVES = all clean check tests
.PHONY: $(DIRECTIVES) $(MODULES)
.DEFAULT: all
$(DIRECTIVES) $(MODULES):
	@$(MAKE) --directory ./src $(MAKECMDGOALS)
