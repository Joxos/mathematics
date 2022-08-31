#include "mathematics.h"
#include <iostream>

int main(void) {
  Set<int> s = Set<int>();
  for (int i = 1; i < 10; i = i + 2) {
    s.add(i);
  }
  for (auto it = s.begin(); it != s.end(); ++it) {
    cout << *it << " ";
  }
  cout << endl;
}
