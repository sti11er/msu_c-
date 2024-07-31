#include <algorithm>
#include <exception>
#include <iostream>
#include <map>
#include <set>
#include <string>


void DFS(
    std::set<std::string>& generatedStr,
    const std::multimap<std::string, std::string>& g,
    std::set<std::string>& used,
    const std::string& currStr,
    size_t maxlen)
{ 
    bool isFinalStr = true;
    for (
        std::multimap<std::string, std::string>::const_iterator it = g.begin();
        it != g.end(); 
        ++it) 
    {
        size_t pos = currStr.find(it->first); 
        if (pos != std::string::npos) {
            isFinalStr = false;

            std::string nextStr = currStr;
            nextStr.replace(pos, it->first.length(), it->second);
                
            if ((used.count(nextStr) == 0) && (nextStr.length() <= maxlen)) {
                used.insert(nextStr);
                DFS(generatedStr, g, used, nextStr, maxlen);
            }
        } 
    }

    if (isFinalStr) {
        generatedStr.insert(currStr);
    }
}

std::set<std::string> generate(
        const std::multimap<std::string, std::string>& g,
        const std::string &start,
        size_t maxlen) 
{
    for (std::multimap<std::string, std::string>::const_iterator  it = g.begin();
            it != g.end(); ++it) 
    {
        if (((it->first).length() == 0) || ((it->first).length() > (it->second).length())) 
        {
            throw std::exception();
        }
    }
    
    std::set<std::string> generatedStr;
    std::string copyStart = start;
    std::set<std::string> used;
    DFS(generatedStr, g, used, copyStart, maxlen);

    return generatedStr;
}

// int main() {
//     std::string start = "abcd";
//     std::multimap<std::string, std::string> g;
//     g.insert(std::pair<std::string, std::string>("a", "z")); 
//     g.insert(std::pair<std::string, std::string>("z", "qqq"));
//     g.insert(std::pair<std::string, std::string>("abcd", "ggggg"));
    
//     // cycle 
//     g.insert(std::pair<std::string, std::string>("a", "k"));
//     g.insert(std::pair<std::string, std::string>("k", "a"));

//     // > maxlen
//     g.insert(std::pair<std::string, std::string>("a", "aaa"));

//     // exception: значение короче ключа
//     //g.insert(std::pair<std::string, std::string>("abcd", "ggg"));
    
//     // exception: пустой ключ
//     // g.insert(std::pair<std::string, std::string>("", "z"));

//     std::set<std::string> set = generate(g, start, 10);
    
//     for (std::set<std::string>::iterator it = set.begin(); 
//         it != set.end(); ++it) {
//         std::cout << *it << ' ';
//     }
// }