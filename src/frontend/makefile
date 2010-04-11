#
# makefile
#     Builds the Frontend module.
# 
# Author
#     Andrew Brown <adb1413@rit.edu>
#
MODULE = frontend
CHILDREN = backend graph traits data
FILTER = 
GANDER = ../..
include $(GANDER)/globals.mak
include $(GANDER)/src/module.mak

# Utilities
Binding.o: 
Picker.o: Painter.o Manipulator.hpp

# Manipulators
Manipulator.hpp : 
Translator.o : Manipulator.hpp

# Controls
Control.o : Binding.o Manipulator.hpp
Keyboard.o : Binding.o Control.o
Menu.o : Control.o

# Mouse controls
MouseData.hpp: Manipulator.hpp
MouseHelper.o: Control.o MouseData.hpp
MouseClickHelper.o: MouseHelper.o Picker.o
MouseDragHelper.o: MouseHelper.o Translator.o
Mouse.o: Control.o MouseClickHelper.o MouseData.hpp MouseDragHelper.o

# Display
Display.o : Control.o Manipulator.hpp Painter.o Picker.o
Painter.o : Manipulator.hpp Translator.o

# Executables
Display: Keyboard.o Mouse.o Translator.o
