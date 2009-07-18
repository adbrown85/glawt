#
# makefile
#     Builds the Backend module.
#
# Author
#     Andy Brown <andybrown85@gmail.com>
#
MODULE = backend
CHILD  = graph
FILTER = Cameraman Command Compositor Director Grip Interpreter Parser Producer
GANDER = ../..
include $(GANDER)/src/globals.mak
include $(GANDER)/src/module.mak


# Utilities
Command.o : 
Tag.hpp :
Parser.o : Tag.hpp

# Delegates
Delegate.hpp : Command.o
Cameraman.o : Delegate.hpp
Compositor.o : Delegate.hpp
Director.o :  Delegate.hpp
Grip.o : Delegate.hpp
Producer.o : Delegate.hpp Parser.o

# Interpreting
Interpreter.o : Cameraman.o Compositor.o Director.o Grip.o Producer.o
