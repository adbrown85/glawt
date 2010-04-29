#
# globals.mak
#     Common variables and rules needed by all the other makefiles.
# 
# Author
#     Andrew Brown <adb1413@rit.edu>
#
include $(GANDER)/functions.mak

# List modules
MODULES := data graph basic advanced backend frontend client

# Resolve directories
bindir := $(GANDER)/bin
docdir := $(GANDER)/doc
libdir := $(GANDER)/lib
srcdir := $(GANDER)/src
VPATH := $(bindir) $(libdir) $(srcdir)

# Options for archiver, compiler, and linker
ARFLAGS := cr
DEFINES := GL_GLEXT_PROTOTYPES ILUT_USE_OPENGL
INCLUDES := ${addprefix -I$(srcdir)/,$(MODULES)}
CXXFLAGS := -Wall -Werror -ggdb  $(INCLUDES) ${addprefix -D,$(DEFINES)}
LDFLAGS := -lm -lglut -lIL -lILU -lILUT

# Phony targets for directing make
.PHONY: all html tests FORCE
all tests: FORCE
FORCE:
	@mkdir -p $(bindir)
	@mkdir -p $(libdir)
html:
	@make -C $(docdir)

