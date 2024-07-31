#include <iostream>

using namespace std;

#include <iostream>

class A {
public:
    A();
    A(const A&);
    A(double);
    A(float, unsigned short);
    ~A();

    void m();
};

A::A() { std::cout << "1 "; }
A::A(const A&) { std::cout << "2 "; }
A::A(double) { std::cout << "3 "; }
A::A(float, unsigned short) { std::cout << "4 "; }
A::~A(){ std::cout << "5 "; }
void A::m() {
    A *obj1 = new A();
    delete obj1;
    A *obj2 = new A(1.53);
    A *obj3 = new A(*obj2);
    delete obj2;
    delete obj3;
    A *obj4 = new A(*obj1);
    A *obj5 = new A(6.6f, 342);
    delete obj4;
    delete obj5;
}