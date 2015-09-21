
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib> // atoi
#include <ctime> // timing

#include "quicksort.h"


using namespace std;

template<typename T>
int readTestSet(const string& filename, vector<T>* data) {
  ifstream input(filename.c_str());
  T buffer;

  input >> buffer;
  while(!input.eof()) {
    data->push_back(buffer);
    input >> buffer;
  }  
  
  return 0;
}

enum EAlgo {
  QUICKSORT,
  QS_RANDOM
};


void showData(const vector<int>& data) {
  for(auto datum : data) {
    cout << datum << endl;
  }
}


int main (int argc, char** argv) {

  srand(time(0));
  
  clock_t tStart = 0;
  clock_t tStop = 0;

  vector<int> data;

  if(!(argc == 3 || argc == 4)) {
    cerr << "Wrong number of parameters" << endl;
    // TODO Print usage
    return 1;
  }

  string filename = argv[1];
  EAlgo algo = EAlgo(atoi(argv[2]));

  int threshold = 1;
  if(argc == 4) {
    threshold = atoi(argv[3]);
  }

  /*
  cout << "File: " << filename << endl;
  cout << "Algo: " << algo << endl;
  cout << "threshold: " << threshold << endl;
  */
  
  readTestSet(filename, &data);

  double n = 1;
  tStart = clock();
  switch(algo) {
  case QUICKSORT:
    quicksort(data.begin(), data.end(), threshold, false);
    break;
  case QS_RANDOM:
    n = 10;
    for(int i = 0; i < n; ++i) {
      quicksort(data.begin(), data.end(), threshold, true);
    }
    break;
  default:
    cerr << "Invalid algo" << endl;
    return 1;
  }
  tStop = clock();

  // To check if its really sorted.
  // showData(data);
  
  //  cout << "Took: " << dt << " seconds" << endl;
  char sep = ',';
  cout << filename << sep
       << data.size() << sep
       << (tStop - tStart)/n << "\n";
  
  return 0;
}
