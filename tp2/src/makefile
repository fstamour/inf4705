
CXXFLAGS = --std=c++14
CXX = g++

.PHONY: default
default:
	@echo "Tagets: "
	@echo "    all"
	@echo "    dynamique"
	@echo "    recuitSimule"
	@echo "    vorace"


all: dynamique recuitSimule vorace

debug: CXXFLAGS += -g -Wall
debug: dynamique recuitSimule vorace

dynamique.cpp vorace.cpp: template.cpp
	sed -e 's/ALGO/$(@:.cpp=)/g' $^ > $@

option_parse.o: option_parse.h option_parse.cpp
exemplaire_struct.o: exemplaire_struct.h exemplaire_struct.cpp
algo_dynamique.o: algo_dynamique.h algo_dynamique.cpp
utils.o: utils.h utils.cpp

dynamique: dynamique.cpp exemplaire_struct.o option_parse.o algo_dynamique.o utils.o
	$(CXX) $(CXXFLAGS) -o $@ $^

recuitSimule: recuit_simule.cpp exemplaire_struct.o option_parse.o
	$(CXX) $(CXXFLAGS) -o $@ $^

vorace: vorace.cpp exemplaire_struct.o option_parse.o
	$(CXX) $(CXXFLAGS) -o $@ $^

test_mu: mu.cpp utils.o
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f *.o
	#rm -f dynamique.cpp recuit_simule.cpp vorace.cpp
	rm -f dynamique recuitSimule vorace

