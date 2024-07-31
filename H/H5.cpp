#include <iostream>
#include <string>

/*
template <typename T, typename U>
void f(T, U) { std::cout << "f-T-U" << std::endl; }

template <typename U>
void f(short, U) { std::cout << "f-short-U" << std::endl; }

template <typename T>
void f(T x, int) { std::cout << "f-T-int" << std::endl; void *p = &x[0]; }

template <typename T>
void f(T *, int) { std::cout << "f-T*-int" << std::endl; }

template <typename T, typename U>
void f(T, U, U) { std::cout << "f-T-U-U" << std::endl; }

template <>
void f(int, int) { std::cout << "f-int-int" << std::endl; }

void f(int, int) { std::cout << "int-int" << std::endl; }

void f(short, short) { std::cout << "short-short" << std::endl; }
*/

// insert arguments for each call
int main()
{
    f(13.5f, "string");    // f-T-U
    f(static_cast<std::string>("string"), 6);    // f-T-int
    f("string", 6);    // f-T*-int
    f(13.5f, 5, 6);    // f-T-U-U
    f(static_cast<short>(5), "string");    // f-short-U
    f(static_cast<short>(5), static_cast<short>(5));    // short-short
    f(6, 6);    // int-int
}