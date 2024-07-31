#include <iostream>
#include <set>

std::set<std::pair<std::string, std::string> >
g() {
    std::set<std::pair<std::string, std::string> > answer;
    answer.insert(std::pair<std::string, std::string>("S", "aAB"));
    answer.insert(std::pair<std::string, std::string>("S", "E"));
    answer.insert(std::pair<std::string, std::string>("A", "dDA"));
    answer.insert(std::pair<std::string, std::string>("A", ""));
    answer.insert(std::pair<std::string, std::string>("B", "bE"));
    answer.insert(std::pair<std::string, std::string>("B", "f"));
    answer.insert(std::pair<std::string, std::string>("D", "eA"));
    answer.insert(std::pair<std::string, std::string>("E", "fA"));
    answer.insert(std::pair<std::string, std::string>("E", "g"));
    return answer;
}
