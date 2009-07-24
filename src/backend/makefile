#
# makefile
#     Builds the Backend module.
#
# Author
#     Andy Brown <andybrown85@gmail.com>
#
MODULE = backend
CHILDREN = graph traits data
FILTER = 
GANDER = ../..
include $(GANDER)/src/globals.mak
include $(GANDER)/src/module.mak


# Utilities
Command.o : 
Tag.o :
Parser.o : Tag.o
Factory.o : Tag.o

# Delegates
Delegate.hpp : Command.o
Cameraman.o : Command.o Delegate.hpp
Compositor.o : Command.o Delegate.hpp
Director.o :  Command.o Delegate.hpp
Grip.o : Command.o Delegate.hpp
Producer.o : Command.o Delegate.hpp Factory.o Parser.o

# Interpreting
Interpreter.o : Cameraman.o Compositor.o Director.o Grip.o Producer.o
