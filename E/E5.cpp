class A {
private: void h();
public: void g(int);
};

class B: A {
public: void f() { /*1*/ h(); }
protected: void f(char x) { /*2*/ f(-x); }
private: void f(int);
         void h(int);
};

class C: public B {
public:    void h(double);
protected: void t() { /*3*/ f('0'); }
           void h() { /*4*/ f(3); }
};

int main() {
    B b;
    /*5*/ b.f();
    /*6*/ b.g(2);
    C c;
    /*7*/ c.f(1);
    /*8*/ c.h();
    /*9*/ c.f();
    /*10*/ c.h(1);
    B *p = &c;
    /*11*/ p->h(.0);
}


#include <iostream>

int
main()
{
    std::cout<<"1 0\n"; 
    std::cout<<"2 B\n";
    std::cout<<"3 B\n";
    std::cout<<"4 0\n";
    std::cout<<"5 B\n"; //?
    std::cout<<"6 0\n";
    std::cout<<"7 0\n";
    std::cout<<"8 0\n";
    std::cout<<"9 B\n"; // ?
    std::cout<<"10 C\n";
    std::cout<<"11 0\n";
    return 0;
}