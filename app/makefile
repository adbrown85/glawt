CPPFLAGS = -Isrc -I"../core/src" -I"../backend/src" -I"../frontend/src"
LDFLAGS = -lglut -lIL -lILU -lILUT -lm
VPATH = bin:obj:src
LIBRARIES = ../frontend/lib/Frontend.a \
            ../backend/lib/Backend.a \
            ../core/lib/Core.a
OBJECTS = Application.o
%.o : %.cpp %.hpp
	@echo "  $@"
	@g++ -ggdb -c $(CPPFLAGS) -o obj/$@ $(filter-out %.hpp, $<)


# Phony
.PHONY: all clean
all: Application
clean:
	rm obj/*.o


# Libraries
Application : Application.o
	@echo "  gander"
	@g++ -ggdb $(LDFLAGS) -o bin/gander \
	$(addprefix obj/, $(OBJECTS)) $(LIBRARIES)


# Objects
Application.o : 
