#
# make-globals.mak
#     Common variables and rules needed by all the other makefiles.
# 
# Author
#     Andy Brown <andybrown85@gmail.com>
#


# Resolve directories
bindir = ${abspath $(GANDER)/bin}
libdir = ${abspath $(GANDER)/lib}
srcdir = ${abspath $(GANDER)/src}
VPATH = $(bindir) $(libdir) $(srcdir)


# Resolve modules and archive
MODULES = ${notdir ${abspath ${shell ls -d $(srcdir)/*/}}}
ARCHIVE = $(libdir)/gander.a


# Options for archiver, compiler, and linker
ARFLAGS = cr
CXXFLAGS = -ggdb ${addprefix -I$(GANDER)/src/,$(MODULES)}
LDFLAGS = -lm -lglut -lIL -lILU -lILUT


# Phony targets for directing make
.PHONY : all tests FORCE
all tests : FORCE
FORCE :
	@mkdir -p $(bindir)
	@mkdir -p $(libdir)
