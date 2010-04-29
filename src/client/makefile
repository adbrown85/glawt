#
# makefile
#     Builds the Client module.
# 
# Author
#     Andrew Brown <adb1413@rit.edu>
#
MODULE := client
GANDER := ../..
include $(GANDER)/src/module.mak
BINARIES += $(bindir)/gander

# Phony targets for directing make
.PHONY: all clean install
all: gander
install: 
	install $(bindir)/gander /usr/local/bin

# Executables
gander: Client
	@echo "  $(bindir)/$@"
	@cp Client $(bindir)/gander
