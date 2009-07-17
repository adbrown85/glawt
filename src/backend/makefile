#
# makefile
#     Builds the Backend module.
#
# Author
#     Andy Brown <andybrown85@gmail.com>
#
MODULE = backend
NEEDS  = graph
FILTER = Cameraman Command Compositor Director Grip Interpreter Parser Producer
GANDER = ../..
include $(GANDER)/make-globals.mak
include $(GANDER)/make-module.mak


# Objects
Cameraman.o : Delegate.hpp
Command.o : 
Compositor.o : Delegate.hpp
Delegate.hpp : Command.o
Director.o :  Delegate.hpp
Grip.o : Delegate.hpp
Interpreter.o : Cameraman.o Compositor.o Director.o Grip.o Producer.o
Parser.o : Tag.hpp
Producer.o : Delegate.hpp Parser.o
Tag.hpp :

