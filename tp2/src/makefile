
CXXFLAGS = --std=c++14 -g
CXX = g++



all: dynamique recuitSimule vorace

debug: CXXFLAGS += -g -Wall
debug: dynamique recuitSimule vorace

recuit_simule.cpp dynamique.cpp vorace.cpp: template.cpp
	sed -e 's/ALGO/$(@:.cpp=)/g' $^ > $@

algo_recuit_simule.o: algo_recuit_simule.cpp algo_recuit_simule.h algo_recuit_simule_proto.h
algo_dynamiqe.o: algo_dynamiqe.cpp algo_dynamiqe.h
algo_vorace.o: algo_vorace.cpp algo_vorace.h
option_parse.o: option_parse.h option_parse.cpp
exemplaire_struct.o: exemplaire_struct.h exemplaire_struct.cpp
utils.o: utils.h utils.cpp

dynamique: dynamique.cpp exemplaire_struct.o option_parse.o algo_dynamique.o utils.o
	$(CXX) $(CXXFLAGS) -o $@ $^

recuitSimule: recuit_simule.cpp exemplaire_struct.o option_parse.o algo_recuit_simule.o
	$(CXX) $(CXXFLAGS) -o $@ $^

vorace: vorace.cpp exemplaire_struct.o option_parse.o
	$(CXX) $(CXXFLAGS) -o $@ $^

test_mu: mu.cpp utils.o
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f *.o
	rm -f dynamique.cpp recuit_simule.cpp vorace.cpp
	rm -f dynamique recuitSimule vorace

.PHONY: default
help:
	@echo "Tagets: "
	@echo "    all"
	@echo "    dynamique"
	@echo "    recuitSimule"
	@echo "    vorace"
	@echo "    help"




# Just for "fun"
algo_recuit_simule_proto.h: algo_recuit_simule.h
	grep -A 1  @proto $^ | sed -e '/^\(\/\/\s*@proto.*\|--\)$$/d' -e 's/\s*{\s*$$/;/' -e 's/)\s*$$/);/' -re 's/\s*=.*(,|\))/\1/g' > $@


