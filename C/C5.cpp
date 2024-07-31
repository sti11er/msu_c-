#include <iostream>

class A
{
public:
    static int x;
    void get_0() const;
};

void A::get_0() const {
    std::cout<<"I AM THE BEST STUDENT!"<<std::endl;
};

// int A::x;
// int
// main()
// {
//     const A a;
//     a.x = 1;
//     a.get_0();
//     return 0;
// }
