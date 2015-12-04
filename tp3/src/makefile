
CXXFLAGS = --std=c++14 -g -Wall -pedantic
CXX = g++

all: horaire

data.o: data.cpp data.h
stats.o: stats.cpp stats.h
solution.o: solution.cpp solution.h
algo_recuit.o: algo_recuit.cpp algo_recuit.h

horaire: main.cpp algo_recuit.o solution.o data.o
	$(CXX) $(CXXFLAGS) -o $@ $^

stats: horaire
	./horaire > general_stats.txt

clean:
	rm -f *.o
	rm -f horaire

.PHONY: default
help:
	@echo "Tagets: "
	@echo "    all"
	@echo "    horaire"
	@echo "    help"

