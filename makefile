#
# makefile
#     Builds Gander.
# 
# Author
#     Andy Brown <andybrown85@gmail.com>
#


# Phony
.PHONY : all clean
all : 
	@echo "Core"
	@$(MAKE) --directory "core" --quiet
	@echo "Backend"
	@$(MAKE) --directory "backend" --quiet
	@echo "Frontend"
	@$(MAKE) --directory "frontend" --quiet
	@echo "Application"
	@$(MAKE) --directory "app" --quiet
clean :
	@echo "Core"
	@$(MAKE) --directory "core" clean --quiet
	@echo "Backend"
	@$(MAKE) --directory "backend" clean --quiet
	@echo "Frontend"
	@$(MAKE) --directory "frontend" clean --quiet
	@echo "Application"
	@$(MAKE) --directory "app" clean --quiet
