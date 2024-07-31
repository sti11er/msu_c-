#include <iostream>
#include <set>

std::set<std::pair<char, std::string>>
g3() {
    std::set<std::pair<char, std::string>> res;
    res.insert(std::pair<char, std::string>('A', "Sa"));
    res.insert(std::pair<char, std::string>('S', "Bc"));
    res.insert(std::pair<char, std::string>('B', "Ab"));
    res.insert(std::pair<char, std::string>('S', "d"));
    return res;
}

std::set<std::pair<char, std::string>>
g4() {
    std::set<std::pair<char, std::string>> res;
    res.insert(std::pair<char, std::string>('S', "B_"));
    res.insert(std::pair<char, std::string>('S', "A_"));
    res.insert(std::pair<char, std::string>('B', "Ab"));
    res.insert(std::pair<char, std::string>('B', "Bb"));
    res.insert(std::pair<char, std::string>('A', "Aa"));
    res.insert(std::pair<char, std::string>('A', "a"));
    return res;
}
