#ifndef _QUICKSORT_H
#define _QUICKSORT_H

///// Heavily inspired from.
///// http://rosettacode.org/wiki/Sorting_algorithms/Quicksort#C.2B.2B

#include <iostream>
#include <iterator>
#include <algorithm> // for std::partition
#include <functional> // for std::less
 
// helper function for median of three
template<typename T>
 T median(T t1, T t2, T t3)
{
  if (t1 < t2)
  {
    if (t2 < t3)
      return t2;
    else if (t1 < t3)
      return t3;
    else
      return t1;
  }
  else
  {
    if (t1 < t3)
      return t1;
    else if (t2 < t3)
      return t3;
    else
      return t2;
  }
}


template <typename RandomAccessIterator>
void bubble_sort(RandomAccessIterator begin, RandomAccessIterator end) {
  bool swapped = true;
  while (begin != end-- && swapped) {
    swapped = false;
    for (auto i = begin; i != end; ++i) {
      if (*(i + 1) < *i) {
        std::iter_swap(i, i + 1);
        swapped = true;
      }
    }
  }
}

template<typename RandomAccessIterator>
void quicksort(RandomAccessIterator first, RandomAccessIterator last, unsigned threshold, bool isRandomPivot) {
  typedef typename std::iterator_traits<RandomAccessIterator>::value_type
    value_type;

  size_t elementCount = last - first;

  if (elementCount <= threshold){
    // TODO Finish bubblesort call
    bubble_sort(first, last);

  } else if (elementCount > 0) {
    // Choose the pivot
    value_type pivot = 0;
    if(isRandomPivot) {
        pivot = rand() % (elementCount - threshold) + 1;
        pivot = *(first + pivot);
    }
    else {
      pivot = *first;
        
    }
    //    std::cout << "n: " << elementCount << " pivot: " << pivot << std::endl;

    // Could be optimized to do only one pass.
    RandomAccessIterator split1 = std::partition(first, last,
						 [pivot](const auto& em){ return em < pivot; });
    RandomAccessIterator split2 = std::partition(split1, last,
						 [pivot](const auto& em){ return !(pivot < em); });
    quicksort(first, split1, threshold, isRandomPivot);
    quicksort(split2, last, threshold, isRandomPivot);
  }
}

#endif // _QUICKSORT_H
