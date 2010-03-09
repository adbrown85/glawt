#
# globals.mak
#     Common variables and rules needed by all the other makefiles.
# 
# Author
#     Andy Brown <andybrown85@gmail.com>
#


# Resolve directories
bindir = $(GANDER)/bin
docdir = $(GANDER)/doc
libdir = $(GANDER)/lib
srcdir = $(GANDER)/src
VPATH = $(bindir) $(libdir) $(srcdir)


# Resolve modules and archives
MODULES = data traits graph backend frontend client
ARCHIVES = frontend.a backend.a graph.a traits.a data.a
ARCHIVES_FULL = ${addprefix $(libdir)/,$(ARCHIVES)}


# Options for archiver, compiler, and linker
ARFLAGS = cr
DEFINES = GL_GLEXT_PROTOTYPES ILUT_USE_OPENGL
CXXFLAGS = -ggdb ${addprefix -I$(srcdir)/,$(MODULES)} ${addprefix -D,$(DEFINES)}
LDFLAGS = -lm -lglut -lIL -lILU -lILUT


# Phony targets for directing make
.PHONY : all html tests FORCE
all tests: FORCE
FORCE :
	@mkdir -p $(bindir)
	@mkdir -p $(libdir)
html:
	@make -C $(docdir)

