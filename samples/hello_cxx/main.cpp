/* Copyright (C) 2024 John Törnblom

This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3, or (at your option) any
later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING. If not, see
<http://www.gnu.org/licenses/>.  */

#include <algorithm>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void task(string prefix) {
  vector<int> vec = {4, 2, 3, 1, 5};

  sort(vec.begin(), vec.end());

  cout << prefix << ": sorted vec: ";
  for(int n : vec) {
    cout << n << " ";
  }
  cout << endl;

  try {
    throw int(42);
  } catch(int e) {
    cout << "Caught exception: " << e << endl;
  }
}


int main() {
  cout << "Hello, libcxx!" << endl;
  thread t(task, __FILE__);
  t.join();

  return 0;
}
