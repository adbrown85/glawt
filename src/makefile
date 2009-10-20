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
DIRECTIVES = all check clean install mostlyclean tests
.PHONY : $(DIRECTIVES) $(MODULES)
$(DIRECTIVES): $(MODULES)

# Rules for making modules
$(MODULES):
	@$(MAKE) -C ./$@ ${filter-out $(MODULES),$(MAKECMDGOALS)}

# Dependencies
client: frontend
frontend: backend
backend: graph
graph: traits
traits: data
data:
