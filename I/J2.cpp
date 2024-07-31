#include <iostream>
#include <set>
#include <utility>
#include <string>
#include <algorithm>

bool
left_nonterm(const std::pair<std::string, std::string> x)
{
    for (auto i = x.first.begin(); i != x.first.end(); ++i) {
        if (isupper(*i)) {
            return true;
        }
    }
    return false;
}

bool
check_S_in_right(std::set<std::pair<std::string, std::string>> const& g)
{
    for (auto i = g.begin(); i != g.end(); ++i) {
        if (i->second.find('S') != std::string::npos) {
            return true;
        }
    }
    return false;
    
}
bool
S_in_right_for_first(const std::pair<std::string, std::string> x)
{
    if (x.first == "S" && x.second == "") {
        return false;
    }
    if (x.first.length() <= x.second.length()) {
        return true;
    }
    return false;
}
bool
S_not_in_right_for_first(const std::pair<std::string, std::string> x)
{
    if (x.first == "S" && x.second == "") {
        return true;
    }
    if (x.first.length() <= x.second.length()) {
        return true;
    }
    return false;
    
    
}
bool
cond_type_2(const std::pair<std::string, std::string> x)
{
    if (x.first.length() == 1) {
        return true;
    }
    return false;
    
}
bool
cond_type_left(const std::pair<std::string, std::string> x)
{
    for (auto i = x.second.begin(); i != x.second.end(); ++i) {
        if ((isupper(*i)) && (i != x.second.begin())) {
            return false;
        }
    }
    return true;
    
}
bool
cond_type_right(const std::pair<std::string, std::string> x)
{
    for (auto i = x.second.rbegin(); i != x.second.rend(); ++i) {
        if ((isupper(*i)) && (i != x.second.rbegin())) {
            return false;
        }
    }
    return true;
}

bool
is_left(std::set<std::pair<std::string, std::string>> const &g)
{
    return all_of(g.begin(), g.end(), cond_type_left);
}
bool
is_right(std::set<std::pair<std::string, std::string>> const &g)
{
    return all_of(g.begin(), g.end(), cond_type_right);
}

bool
is_type0(std::set<std::pair<std::string, std::string>> const &g)
{
    return all_of(g.begin(), g.end(), left_nonterm);
}
bool
is_type1(std::set<std::pair<std::string, std::string>> const &g)
{
    if (check_S_in_right(g)) {
        return all_of(g.begin(), g.end(), S_in_right_for_first);
    }
    else {
        return all_of(g.begin(), g.end(), S_not_in_right_for_first);
        
    }
}
bool
is_type2(std::set<std::pair<std::string, std::string>> const &g)
{
    return all_of(g.begin(), g.end(), cond_type_2);
}
bool
is_type3(std::set<std::pair<std::string, std::string>> const &g)
{
    return is_right(g) || is_left(g);
    
}

int
grammar_type(std::set<std::pair<std::string, std::string>> const &g)
{
    if (!is_type0(g)) {
        return -1;
    }
    int type = 0;
    if (is_type1(g)) {
        type = 1;
    }
    
    if (is_type2(g)) {
        type = 2;
    }
    
    if (is_type2(g) && is_type3(g)) {
        type = 3;
    }
    return type;
}



