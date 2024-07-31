#include <iostream>

class A {
public:
    void set_color(int);
    int get_color() const;
    friend std::ostream& operator<<(std::ostream &, const A& ); 
private:
    int color;
};

void A::set_color(int k)
{
    color = k;
}

int A::get_color() const
{
    return color;
}

std::ostream& operator<<(std::ostream& out, const A& obj)
{
    out <<"color = " << obj.get_color();
    return out;
}

class UniquePtr
{
public:
    UniquePtr();
    UniquePtr(A* );
    UniquePtr(UniquePtr& );
    ~UniquePtr();
    UniquePtr& operator= (UniquePtr& );
    A* operator-> () const;
    A& operator* () const;
private:
    A* ptr;
};

UniquePtr::UniquePtr() {
    ptr = 0;
}

UniquePtr::UniquePtr(A* a) {
    ptr = a;
}

UniquePtr::UniquePtr(UniquePtr& u) {
    if (&u != this) {
        ptr = u.ptr;
        u.ptr = 0;
    }
}

UniquePtr::~UniquePtr() {
    if (ptr) { 
        delete ptr; 
    }
}

UniquePtr& UniquePtr::operator= (UniquePtr& u) {
    if (ptr != u.ptr) {
        delete ptr;
        ptr = u.ptr;
        u.ptr = 0;
    }
    return *this; 
}

A* UniquePtr::operator-> () const {
    return ptr;
}   
    
A& UniquePtr::operator* () const {
    return *ptr;
}

// int main()
// {
//     UniquePtr p = new A; // get ownership
//     p->set_color(42);
//     std::cout << *p << std::endl; // color = 42
//     UniquePtr const& q = p; // ownership is not moved
//     p->set_color(111);
//     std::cout << q->get_color() << std::endl; // 111
//     std::cout << *q << std::endl; // color = 111
//     UniquePtr s = new A;
//     s->set_color(31);
//     std::cout << (*s).get_color() << std::endl; // 31
//     s = p; // ownership is moved
//     std::cout << s->get_color() << std::endl; // 111
//     UniquePtr t = s; // ownership is moved
//     t = t = t;
//     std::cout << t->get_color() << std::endl; // 111
// } // no memory leaks