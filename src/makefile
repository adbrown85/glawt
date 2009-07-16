#
# makefile
#     Builds Gander from its modules.
# 
# Author
#     Andy Brown <andybrown85@gmail.com>
#
MODULES = data traits graph


# Phony targets for directing make
PHONIES = all check clean tests
.PHONY : $(PHONIES) $(MODULES)
$(PHONIES) : $(MODULES)


# Rule for making a module
$(MODULES) :
	@$(MAKE) --directory $@ --quiet ${filter-out $(MODULES), $(MAKECMDGOALS)}


# Module dependencies
data : 
traits : data
graph : traits

