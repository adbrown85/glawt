#
# makefile
#     Builds Gander from its modules.
# 
# Author
#     Andrew Brown <adb1413@rit.edu>
#
GANDER = .
include $(GANDER)/globals.mak


# Phony targets for directing make
DIRECTIVES = all check clean install mostlyclean tests
.PHONY: $(DIRECTIVES) $(MODULES)
.DEFAULT: all
$(DIRECTIVES) $(MODULES):
	@$(MAKE) --directory ./src $(MAKECMDGOALS)
