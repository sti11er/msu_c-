class A {
    int i;
public:
    A(int x) : i(x) {  }
    virtual ~A() {  }
    int f() const { return i + g() + h(); }
    virtual int g() const { return i; }
    int h() const { return 18; }
};
class B : public A {
public:
    B() : A(50) {  }
    ~B() {  }
    int f() const { return g() - 2; }
    virtual int g() const { return 8; }
    int h() const { return 9; }
};
int main() {
    B b;
    A* p = &b;
    // std::cout << "result = (" << p->f() << ';' << b.f() << ')' << std::endl;
    return 0;
}