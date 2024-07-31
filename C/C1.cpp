#include <iostream>
using namespace std;

class Array {
public:
    friend void print(const Array &);
    Array(int size = 0);
    ~Array();
    int& item(int);
    const int& item(int) const;
private:
    int s;
    int *arr;
};

Array::Array(int size) {
    s = size;
    arr = new int[size];
}

Array::~Array() {
    s = 0;
    delete[] arr;
}

int& Array:: item(int i) {
    if ((i >= s) || (s < 0)) {
        cout<<"Out of bound";
        exit(0);
    }
    return arr[i];
}

const int& Array:: item(int i) const {
    if ((i >= s) || (s < 0)) {
        cout<<"Out of bound";
        exit(0);
    }
    return arr[i];
}

void print(const Array &obj) {
    for (int i = 0; i < obj.s-1; i++) {
        cout<<obj.item(i)<<' ';
    }
    cout<<obj.item(obj.s-1)<<endl;
}

int
main()
{
    int count = 10;
    Array obj(count);
    for (int i = 0; i < count; ++i) {
        cin>>obj.item(i);
    }
    print(obj);
    return 0;
}
