CPP = g++
CFLAGS = -O3 -std=c++17

OPENCV = `pkg-config opencv --cflags --libs`
LIBS = #$(OPENCV)

OBJECTFILES=main.o

simulate: $(OBJECTFILES)
	$(CPP) $(LFLAGS) $(OBJECTFILES) -o $@ $(LIBS)

$(OBJECTFILES):
	$(CPP) $(CFLAGS) $*.cpp -c

main.o: main.cpp 2d-diffusion-limited-aggregation.h

#clearing files
clean:
	@echo Cleaning object files...
	rm *.o
