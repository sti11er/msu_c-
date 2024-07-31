#include <vector>
#include <iterator>
#include <list>
#include <set>
#include <iostream>

namespace with_vector {
int fun(std::string const &s1, std::string const &s2) {
    std::string str1 = s1;
    std::string str2 = s2;
    std::vector<std::string> vec;
    for (size_t i0 = 0; i0 < str1.length() + 1; ++i0) {
        for (size_t j0 = 0; j0 < str1.length() + 1 - i0; ++j0) {
            for (size_t i = 0; i < str2.length() + 1; ++i) {
                for (size_t j = 0; j < str2.length() + 1 - i; ++j) {
                    vec.push_back(str1.substr(i0, j0) + str2.substr(i, j));
                    vec.push_back(str2.substr(i, j) + str1.substr(i0, j0));
                }
            }
        }
    }
    std::vector<std::string> vec_set;
    std::vector<std::string>::const_iterator p = vec.begin();
    while (p != vec.end()) {
        int f = 0;
        std::vector<std::string>::const_iterator q = vec_set.begin();
        while (q != vec_set.end()) {
            if (*p == *q) {
                f = 1;
            }
            q++;
        }
        if (f == 0) {
            vec_set.push_back(*p);
        }
        p++;
    }
    return vec_set.size();
}
}

namespace with_list {
int fun(std::string const &s1, std::string const &s2) {
    std::string str1 = s1;
    std::string str2 = s2;
    std::list<std::string> lis;
    for (size_t i0 = 0; i0 < str1.length() + 1; ++i0) {
        for (size_t j0 = 0; j0 < str1.length() + 1 - i0; ++j0) {
            for (size_t i = 0; i < str2.length() + 1; ++i) {
                for (size_t j = 0; j < str2.length() + 1 - i; ++j) {
                    lis.push_back(str1.substr(i0, j0) + str2.substr(i, j));
                    lis.push_back(str2.substr(i, j) + str1.substr(i0, j0));
                }
            }
        }
    }
    std::list<std::string> lis_set;
    std::list<std::string>::const_iterator p = lis.begin();
    while (p != lis.end()) {
        int f = 0;
        std::list<std::string>::const_iterator q = lis_set.begin();
        while (q != lis_set.end()) {
            if (*p == *q) {
                f = 1;
            }
            q++;
        }
        if (f == 0) {
            lis_set.push_back(*p);
        }
        p++;
    }
    return lis_set.size();
}
}

namespace with_best {
int fun(std::string const &s1, std::string const &s2) {
    std::string str1 = s1;
    std::string str2 = s2;
    std::set<std::string> set;
    for (size_t i0 = 0; i0 < str1.length() + 1; ++i0) {
        for (size_t j0 = 0; j0 < str1.length() + 1 - i0; ++j0) {
            for (size_t i = 0; i < str2.length() + 1; ++i) {
                for (size_t j = 0; j < str2.length() + 1 - i; ++j) {
                    set.insert(str1.substr(i0, j0) + str2.substr(i, j));
                    set.insert(str2.substr(i, j) + str1.substr(i0, j0));
                }
            }
        }
    }
    return set.size();
}
}

int
main()
{
    std::cout << with_vector::fun("", "sd") << std::endl;
    std::cout << with_list::fun("ae", "ea") << std::endl;
    std::cout << with_best::fun("ae", "ea") << std::endl;
}