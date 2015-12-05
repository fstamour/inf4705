
CXXFLAGS = --std=c++14 -Wall -pedantic -O2
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

profile: CXXFLAGS += -p -fno-omit-frame-pointer
profile: horaire

profiling.png:
	gprof horaire | gprof2dot -s | dot -Tpng -o profiling.png

# $(shell pkg-config --libs --cflags opencl-utils)
opencl: CXXFLAGS += -g -lOpenCL
opencl: test_opencl.cpp
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

