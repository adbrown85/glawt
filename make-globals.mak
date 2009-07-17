#
# make-globals.mak
#     Common variables and rules needed by all the other makefiles.
# 
# Author
#     Andy Brown <andybrown85@gmail.com>
#


# Resolve directories
BINDIR = ${abspath $(GANDER)/bin}
LIBDIR = ${abspath $(GANDER)/lib}
SRCDIR = ${abspath $(GANDER)/src}
VPATH = $(BINDIR) $(LIBDIR) $(SRCDIR)


# Resolve modules and archive
MODULES = ${notdir ${abspath ${shell ls -d $(SRCDIR)/*/}}}
ARCHIVE = $(LIBDIR)/gander.a


# Phony targets for directing make
PHONIES = all checkGlobals cleanGlobals directories
.PHONY : $(PHONIES)
all : directories
checkGlobals :
	@echo
	@echo "BINDIR  = $(BINDIR)"
	@echo "LIBDIR  = $(LIBDIR)"
	@echo "SRCDIR  = $(SRCDIR)"
	@echo "ARCHIVE = $(ARCHIVE)"
	@echo "MODULES = $(MODULES)"
	@echo
cleanGlobals :
	@echo
	@echo "Removing archive..."
	@$(RM) -f $(ARCHIVE) 
	@echo "Removing executable..."
	@$(RM) -f $(BINDIR)/gander
	@echo
directories :
	@mkdir -p $(BINDIR)
	@mkdir -p $(LIBDIR)
