#
# makefile
#     Builds the Backend module.
# 
# Author
#     Andrew Brown <adb1413@rit.edu>
#
MODULE := backend
GANDER := ../..
include $(GANDER)/src/module.mak

# Utilities
Command.o : 

# Delegates
Delegate.hpp : Command.o
Cameraman.o : Command.o Delegate.hpp
Compositor.o : Command.o Delegate.hpp
Director.o :  Command.o Delegate.hpp
Grip.o : Command.o Delegate.hpp
Producer.o : Command.o Delegate.hpp

# Interpreting
Interpreter.o : Cameraman.o Compositor.o Director.o Grip.o Producer.o
