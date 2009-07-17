#
# makefile
#     Builds Gander from its modules.
# 
# Author
#     Andy Brown <andybrown85@gmail.com>
#
GANDER = ..
include $(GANDER)/make-globals.mak


# Phony targets for directing make
DIRECTIVES = all check clean tests
.PHONY : $(DIRECTIVES)
$(DIRECTIVES) : 
	@$(MAKE) --directory ./graph --quiet $@
check : checkGlobals
clean : cleanGlobals
