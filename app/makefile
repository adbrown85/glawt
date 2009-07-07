#
# makefile
#     Builds Gander from its modules.
# 
# Author
#     Andy Brown <andybrown85@gmail.com>
#
MODULES = data graph backend frontend client
OPTS = --quiet


# Macros
define make-module
$(1) : 
	@echo $(1)
	@$(MAKE) --directory ./$(1) $(filter clean,$(MAKECMDGOALS)) $(OPTS)
endef


# Phony
.PHONY : all clean $(MODULES)
all : $(MODULES)
clean : $(MODULES)


# Modules
$(foreach M,$(MODULES),$(eval $(call make-module,$(M))))
