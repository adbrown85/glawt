#
# makefile
#     Builds Gander from its modules.
# 
# Author
#     Andy Brown <andybrown85@gmail.com>
#
GANDER = .
include $(GANDER)/make-globals.mak


# Phony targets for directing make
PHONIES = all clean check tests
.PHONY : $(PHONIES)
$(PHONIES) :
	@$(MAKE) --directory ./src $@ --quiet
