#include <set>
#include <string>


std::set<std::pair<std::string, std::string>> g()
{
    std::set<std::pair<std::string, std::string>> res;
    
    res.insert({"A","yAy"});
    res.insert({"S","A"});
    res.insert({"A","xAx"});
    res.insert({"A","xx"});
    res.insert({"A","yy"});
    return res;
}