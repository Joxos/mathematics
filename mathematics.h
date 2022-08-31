#pragma once

#include <set>

using namespace std;

template <typename T> class Set : public set<T> {
private:
  set<T> elements;

public:
  Set(void) { elements = set<T>(); }

  /* bool isSubset(Set s) {} */
};
