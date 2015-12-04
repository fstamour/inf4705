
CXXFLAGS = --std=c++14 -g -Wall -pedantic
CXX = g++

all: horaire

problem.o: problem.cpp problem.h
stats.o: stats.cpp stats.h
solution.o: solution.cpp solution.h
algo_recuit.o: algo_recuit.cpp algo_recuit.h

horaire: main.cpp problem.o stats.o solution.o # algo_recuit.o
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

