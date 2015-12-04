
CXXFLAGS = --std=c++14 -Wall -pedantic
CXX = g++

all: horaire

data.o: data.cpp data.h
stats.o: stats.cpp stats.h
solution.o: solution.cpp solution.h
algo_recuit.o: algo_recuit.cpp algo_recuit.h

horaire: CXXFLAGS += -lpthread
horaire: main.cpp algo_recuit.o solution.o data.o
	$(CXX) $(CXXFLAGS) -o $@ $^

debug: CXXFLAGS += -g
debug: horaire

profile: CXXFLAGS += -p
profile: horaire


clean:
	rm -f *.o
	rm -f horaire

.PHONY: default
help:
	@echo "Tagets: "
	@echo "    all"
	@echo "    horaire"
	@echo "    help"

