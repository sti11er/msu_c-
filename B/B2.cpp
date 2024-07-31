#include <iostream>
using namespace std;

class A {
public:
    int* nums = nullptr;
    int size = 0; 
    ~A();
    void append(const int el);
    void bubble_soritizing();
};

A::~A() {  
    size = 0;
    delete[] nums; 
}

void A::append(const int el) {
    size++;
    int* tmp = new int[size];

    for (int i = 0; i < size - 1; i++) {
    tmp[i] = nums[i];
    }

    tmp[size - 1] = el;
    delete[] nums;
    nums = tmp;
}

// соритровка пузырьком
void A::bubble_soritizing() {
	int tmp;
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (nums[j] > nums[j + 1]) {
                tmp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = tmp;
            }
        }
    }
}

int 
main() {
    int el;
    A a;
    while (cin >> el) {
        a.append(el);
    }

    a.bubble_soritizing();

    for (int i = 0; i < a.size; i++) {
        cout << a.nums[i] << " ";
    }
    cout << endl;

    return 0;
}