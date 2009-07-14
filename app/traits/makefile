#
# makefile
#     Builds the Traits module.
#
# Author
#     Andy Brown <andybrown85@gmail.com>
#
MODULE = traits
PREREQUISITES = data
OBJECTS = Drawable.o Identifiable.o Selectable.o
TESTS = Drawable Identifiable Selectable
include ../module.mak


# Dependencies
Applicable.hpp :
Drawable.o : Identifiable.o
Identifiable.o : 
Selectable.o : Drawable.o
