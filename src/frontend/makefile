#
# makefile
#     Builds the Frontend module.
#
# Author
#     Andy Brown <andybrown85@gmail.com>
#
MODULE = frontend
CHILD  = backend
FILTER = Binding Control Display Keyboard Menu Mouse Painter Picker Translator
GANDER = ../..
include $(GANDER)/src/globals.mak
include $(GANDER)/src/module.mak


# Utilities
Binding.o : 
Picker.o : Painter.o Manipulator.hpp

# Manipulators
Manipulator.hpp : 
Translator.o : Manipulator.hpp

# Controls
Control.o : Binding.o Manipulator.hpp
Keyboard.o : Binding.o Control.o
Menu.o : Control.o
Mouse.o : Binding.o Control.o Picker.o Translator.o

# Display
Painter.o : Manipulator.hpp Translator.o
Display.o : Control.o Manipulator.hpp Painter.o
