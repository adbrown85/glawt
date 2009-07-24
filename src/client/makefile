#
# makefile
#     Builds the Client module.
#
# Author
#     Andy Brown <andybrown85@gmail.com>
#
MODULE = client
CHILDREN = frontend backend graph traits data
FILTER = 
GANDER = ../..
include $(GANDER)/src/globals.mak
include $(GANDER)/src/module.mak
BINARIES += $(bindir)/gander


# Phony targets for directing make
.PHONY: all clean
all: gander


# Executables
gander: Client.o ${addsuffix .a,$(CHILDREN)}
	@echo "  $(bindir)/$@"
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(bindir)/$@ $^
