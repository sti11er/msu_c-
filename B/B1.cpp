#include <iostream>
#include <algorithm>

using namespace std;

int main() {
  int* nums = nullptr;

  int x;
  int size = 0; 
  while (cin >> x) {
    size++;
    int* tmp = new int[size];

    for (int i = 0; i < size - 1; i++) {
      tmp[i] = nums[i];
    }

    tmp[size - 1] = x;
    delete[] nums;
    nums = tmp;
  }

  sort(nums, nums + size);

  for (int i = 0; i < size; i++) {
    cout << nums[i] << " ";
  }
  cout << endl;
  delete[] nums;
  return 0;
}