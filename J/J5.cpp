#include <iterator>
#include <set>
#include <map>
#include <string>
#include <iostream>

std::set<std::string>
my_generate(const std::multimap<std::string, std::string> & g, const std::string & start, size_t maxlen, std::set<std::string> & all);

std::set<std::string>
generate(const std::multimap<std::string, std::string> & g, const std::string & start, size_t maxlen) {
    std::set<std::string> all;
    return my_generate(g, start, maxlen, all);
}

std::set<std::string>
my_generate(
    const std::multimap<std::string, std::string> & g, 
    const std::string & start, 
    size_t maxlen, 
    std::set<std::string> & all) 
{
    std::multimap<std::string, std::string>::const_iterator p = g.begin(), p_end = g.end();
    std::set<std::string> ans;
    bool the_end = true;
    while (p != p_end) {
        if ((p->first).length() == 0) {
            throw std::exception();
        }
        if ((p->first).length() > (p->second).length()) {
            throw std::exception();
        }
        size_t ind = start.find(p->first);
        if (ind != std::string::npos) {
            the_end = false;
            std::string str_ans = start;
            str_ans.replace(ind, (p->first).length(), p->second);
            
            if ((all.count(str_ans) == 0) && (str_ans.length() <= maxlen)) {
                all.insert(str_ans);
                std::set<std::string> ans_new = my_generate(g, str_ans, maxlen, all);
                std::set<std::string>::const_iterator p1 = ans_new.begin(), q1 = ans_new.end();
                while (p1 != q1) {
                    if (p1->length() <= maxlen) {
                        ans.insert(*p1);
                    }
                    p1++;
                }
            }
        }
        p++;
    }
    if (the_end) {
        ans.insert(start);
    }
    return ans;
}

int main() {
    std::multimap<std::string, std::string> m;
    m.insert(std::pair<std::string, std::string>("S", "5"));
    m.insert(std::pair<std::string, std::string>("S", "SSS"));
    m.insert(std::pair<std::string, std::string>("S", "A"));
    m.insert(std::pair<std::string, std::string>("A", "S"));
    std::set<std::string> ans = generate(m, "Sabcd", 15);
    std::set<std::string>::const_iterator p1 = ans.begin(), q1 = ans.end();
    while (p1 != q1) {
        std::cout << *p1 << std::endl;
        p1++;
    }
}