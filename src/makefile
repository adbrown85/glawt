#
# makefile
#     Builds Gander from its modules.
# 
# Author
#     Andrew Brown <adb1413@rit.edu>
#
GANDER = ..
include $(GANDER)/globals.mak


# Phony targets for directing make
DIRECTIVES = all check clean install mostlyclean tests
.PHONY : $(DIRECTIVES) $(MODULES)
$(DIRECTIVES): $(MODULES)

# Rules for making modules
$(MODULES):
	@$(MAKE) -C ./$@ ${filter-out $(MODULES),$(MAKECMDGOALS)}

# Dependencies
client: frontend
frontend: backend
backend: advanced
advanced: basic
basic: graph
graph: data
data:
