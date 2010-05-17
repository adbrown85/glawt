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
Scaler.o: Manipulator.o

# Controls
Binding.o: 
Control.o: Binding.o Manipulator.o
Keyboard.o: Control.o
Menu.o: Control.o
Picker.o: Painter.o
MouseData.hpp: Manipulator.o
MouseHelper.o: Control.o MouseData.hpp
MouseClickHelper.o: MouseHelper.o Picker.o
MouseDragHelper.o: MouseHelper.o
Mouse.o: MouseClickHelper.o MouseDragHelper.o Translator.o Scaler.o

# Display
Display.o: Control.o Painter.o
Painter.o: Manipulator.o

# Executables
Display: Keyboard.o Mouse.o Translator.o Scaler.o
