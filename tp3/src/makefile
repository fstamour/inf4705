
CXXFLAGS = --std=c++14 -g -Wall -pedantic
CXX = g++

all: horaire

data.o: data.cpp data.h

horaire: main.cpp data.o
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f *.o
	rm -f horaire

.PHONY: default
help:
	@echo "Tagets: "
	@echo "    all"
	@echo "    horaire"
	@echo "    help"

