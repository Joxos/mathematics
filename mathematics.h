#pragma once

#include <vector>

using namespace std;

template <typename T> class Set {
private:
  vector<T> elements;

public:
  Set(void) { elements = vector<T>(); }

  bool add(T element) {
    for (auto i : elements) {
      if (i == element) {
        return false;
      }
    }
    elements.push_back(element);
    return true;
  }

  bool remove(T element) {
    for (auto it = elements.begin(); it != elements.end(); ++it) {
      if (*it == element) {
        elements.erase(it);
        return true;
      }
    }
    return false;
  }

  bool eq(Set s) {
    for (auto i = elements.begin(); i != elements.end(); ++i) {
      for (auto j = s.begin(); j != elements.end(); ++j) {
        if (*i != *j) {
          return false;
        }
      }
    }
    return true;
  }

  bool notEq(Set s) { return !eq(s); }

  /* bool isSubset(Set s) {} */

  // note that whether the variable is exsist or not, it's copy get ready
  // note that head dose not store any data
  auto begin(void) { return elements.begin(); }

  auto end(void) { return elements.end(); }
};
