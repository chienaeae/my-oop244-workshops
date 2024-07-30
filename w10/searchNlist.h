#ifndef SENECA_SEARCHNLIST_H_
#define SENECA_SEARCHNLIST_H_

#include <iostream>

#include "Collection.h"

namespace seneca {

// seach function that searches an array for a key and stores the matches in a
// collection.
//
// note template T1 must be able to compare with T2
template <typename T1, typename T2>
bool search(Collection<T1> &collection, const T1 arr[], int size, T2 key) {
  bool found = false;
  for (int i = 0; i < size; i++) {
    if (arr[i] == key) {
      found = true;
      collection.add(arr[i]);
    }
  }
  return found;
}

// listArrayElements function that lists all the elements in an array
// the title is printed first, then each element is printed with its index and a
// colon in front of it.
//
// note T1 must have operator<< overloaded
template <typename T1>
void listArrayElements(const char *title, const T1 arr[], int size) {
  std::cout << title << std::endl;
  for (int i = 0; i < size; i++) {
    std::cout << i + 1 << ": " << arr[i] << std::endl;
  }
}
}; // namespace seneca
#endif