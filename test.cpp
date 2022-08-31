#include "mathematics.h"
#include <iostream>

template <typename T> void display(Set<T> s, string sep = " ") {
  for (auto it = s.begin(); it != s.end(); ++it) {
    cout << *it << sep;
  }
  cout << endl;
}

struct Point {
  double x, y;
};

int main(void) {
  Set<int> s = Set<int>();

  for (int i = 1; i <= 11; i = i + 2) {
    s.insert(i);
  }
  display(s);
  // 1 3 5 7 9 11

  s.erase(11);
  display(s);
  // 1 3 5 7 9

  s.insert(9);
  // 0
  display(s);
  // 1 3 5 7 9

  Set<int> s1 = Set<int>();
  for (int i = 1; i <= 11; i = i + 2) {
    s1.insert(i);
  }
  cout << "s: ";
  display(s);
  // s: 1 3 5 7 9
  cout << "s1: ";
  display(s1);
  // s1: 1 3 5 7 9 11
  cout << (s == s1) << endl;
  // 0 0

  s1.erase(11);
  cout << "s: ";
  display(s);
  // s: 1 3 5 7 9
  cout << "s1: ";
  display(s1);
  // s: 1 3 5 7 9
  cout << (s == s1) << endl;
  // 1 1

  return 0;
}
