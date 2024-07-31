#include <iostream>

class A
{
public:
    A();
    A(const A &);
    ~A();
};

class B
{
public:
    B();
    B(const B &);
    ~B();

private:
    A a;   
};

A::A() { std::cout << "A\n"; }
A::A(const A&) { std::cout << "A(&)\n"; }
A::~A() { std::cout << "~A\n"; }
B::B() { std::cout << "B\n"; }
B::B(const B&) { std::cout << "B(&)\n"; }
B::~B() { std::cout << "~B\n"; }

A f(B b)
{
    return A();
}

int
main()
{
    A a;
    B b;
    {
        B c = b;
    }
    f(b);
}