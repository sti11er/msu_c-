#include <iostream>
#include <set>

std::set<std::pair<char, std::string>>
g1() {
    std::set<std::pair<char, std::string>> res;
    res.insert(std::pair<char, std::string>('S', "cA"));
    res.insert(std::pair<char, std::string>('A', "bA"));
    res.insert(std::pair<char, std::string>('A', "aA"));
    res.insert(std::pair<char, std::string>('A', "_"));
    return res;
}

std::set<std::pair<char, std::string>>
g2() {
    std::set<std::pair<char, std::string>> res;
    res.insert(std::pair<char, std::string>('S', "aS"));
    res.insert(std::pair<char, std::string>('S', "c"));
    res.insert(std::pair<char, std::string>('S', "bS"));
    return res;
}