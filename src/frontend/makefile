#
# makefile
#     Builds the Frontend module.
#
# Author
#     Andy Brown <andybrown85@gmail.com>
#
MODULE = frontend
NEEDS  = backend
FILTER = Binding Control Display Keyboard Menu Mouse Painter Picker Translator
GANDER = ../..
include $(GANDER)/make-globals.mak
include $(GANDER)/make-module.mak


# Objects
Binding.o : 
Control.o : Binding.o Manipulator.hpp
Display.o : Control.o Manipulator.hpp Painter.o
Keyboard.o : Binding.o Control.o
Manipulator.hpp : 
Menu.o : Control.o
Mouse.o : Binding.o Control.o Picker.o Translator.o
Painter.o : Manipulator.hpp Translator.o
Picker.o : Painter.o Manipulator.hpp
Translator.o : Manipulator.hpp
