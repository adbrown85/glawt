#
# makefile
#     Builds the Data module.
#
# Author
#     Andy Brown <andybrown85@gmail.com>
#
CPPFLAGS = -Isrc
LDFLAGS = -lm
VPATH = bin:lib:obj:src
OBJS = Matrix.o Quaternion.o Vector.o
OBJSWDIRS = $(addprefix obj/, $(notdir $(OBJS)))


# Implicit rules
%.o : %.cpp %.hpp
	@echo "  $@"
	@g++ -ggdb -c $(CPPFLAGS) -o obj/$@ $<
%.a :
	@echo "  --> $@"
	@ar cr "lib/$@" $(OBJSWDIRS)


# Phony targets
.PHONY: all clean
all: data.a
clean:
	rm obj/*.o


# Archive
data.a : $(OBJS)


# Objects
Matrix.o : Vector.o
Quaternion.o : Matrix.o Vector.o
Vector.o :
