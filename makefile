#
# makefile
#     Builds Gander from its modules, and copies to current directory.
# 
# Author
#     Andy Brown <andybrown85@gmail.com>
#


# Phony targets
.PHONY : all clean
all :
	@$(MAKE) --directory ./app --quiet
	@echo "--> gander"
	@cp ./app/client/bin/Client ./gander
clean :
	@$(MAKE) --directory ./app clean --quiet
