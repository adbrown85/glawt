#
# makefile
#     Builds the Frontend module.
# 
# Author
#     Andrew Brown <adb1413@rit.edu>
#
MODULE := frontend
GANDER := ../..
include $(GANDER)/src/module.mak

# Manipulators
Manipulator.o: 
Translator.o: Manipulator.o

# Controls
Binding.o: 
Control.o: Binding.o Manipulator.o
Keyboard.o: Control.o
Menu.o: Control.o
Picker.o: Painter.o
MouseData.hpp: Manipulator.o
MouseHelper.o: Control.o MouseData.hpp
MouseClickHelper.o: MouseHelper.o Picker.o
MouseDragHelper.o: MouseHelper.o Translator.o
Mouse.o: MouseClickHelper.o MouseDragHelper.o

# Display
Display.o: Control.o Manipulator.o Painter.o Picker.o
Painter.o: Manipulator.o Translator.o

# Executables
Display: Keyboard.o Mouse.o Translator.o
