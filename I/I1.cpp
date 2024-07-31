#include <vector>
#include <list>
#include <set>
#include <string>
#include <iostream>

template <typename T>
T combinate(std::string const &s1, std::string const &s2) 
{
    T combinate;
    std::string str1 = s1;
    std::string str2 = s2;

    for (size_t i = 0; i < str1.length() + 1; ++i) {
        for (size_t j = 0; j < str1.length() + 1 - i; ++j) {
            for (size_t k = 0; k < str2.length() + 1; ++k) {
                for (size_t q = 0; q < str2.length() + 1 - k; ++q) {
                    combinate.push_back(str1.substr(i, j) + str2.substr(k, q));
                    combinate.push_back(str2.substr(k, q) + str1.substr(i, j));
                }
            }
        }
    }

    return combinate;
}

template <>
std::set<std::string> combinate(std::string const &s1, std::string const &s2) 
{
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
    return set;
}


template <typename T>
int amount_unique(T combinate) 
{
    T unique;
    typename T::const_iterator start1 = combinate.begin();
    typename T::const_iterator end1 = combinate.end();

    while (start1 != end1) {
        size_t is_unique = 1;
        typename T::const_iterator start2 = unique.begin();
        typename T::const_iterator end2 = unique.end();

        while (start2 != end2) {
            if (*start1 == *start2) {
                is_unique = 0;
            }
            start2++;
        }
        if (is_unique) {
            unique.push_back(*start1);
        }
        start1++;
    }

    return unique.size();
}

namespace with_vector
{
    int fun(std::string const &s1, std::string const &s2) 
    {
        return amount_unique(combinate< std::vector<std::string> >(s1, s2)); 
    }
};

namespace with_list
{
    int fun(std::string const &s1, std::string const &s2) 
    {
        return amount_unique(combinate< std::list<std::string> >(s1, s2)); 
    }
};

namespace with_best
{
    int fun(std::string const &s1, std::string const &s2) 
    {
        return (combinate< std::set<std::string> >(s1, s2)).size();
    }
};