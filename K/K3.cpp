#include <iostream>
#include <set>

std::set<std::pair<char, std::string>>
g3() {
    std::set<std::pair<char, std::string>> res;
    res.insert(std::pair<char, std::string>('S', "Fa"));
    res.insert(std::pair<char, std::string>('S', "a"));
    res.insert(std::pair<char, std::string>('S', "Sa"));
    res.insert(std::pair<char, std::string>('F', "Sb"));
    res.insert(std::pair<char, std::string>('F', "Fb"));
    res.insert(std::pair<char, std::string>('F', "b"));
    return res;
}

std::set<std::pair<char, std::string>>
g4() {
    std::set<std::pair<char, std::string>> res;
    res.insert(std::pair<char, std::string>('S', "aK"));
    res.insert(std::pair<char, std::string>('B', "bK"));
    res.insert(std::pair<char, std::string>('B', "aB"));
    res.insert(std::pair<char, std::string>('K', "aB"));
    res.insert(std::pair<char, std::string>('K', "_"));
    res.insert(std::pair<char, std::string>('B', "_"));
    return res;
}
