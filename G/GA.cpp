#include <iostream>

class A
{
public:
    virtual ~A() = default;
};

class B
{
public:
    virtual ~B() = default;
};

class C: public A, public B 
{
};

A* f() {
    return new C();
}

int 
main() 
{
    A*p = f();
    B*q;

    if ((q = dynamic_cast<B *>(p)) && static_cast<void *>(q) > static_cast<void *>(p)) {
        std::cout << "OK\n";
    }
}