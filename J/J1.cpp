#include <iostream>
#include <string>
int
main()
{
    std::cout<<"0"<<std::endl;
    std::cout<<"2"<<std::endl;
    std::string str;
    while (getline(std::cin, str, '\n')) {
        if (str.empty()) {
            std::cout<<"YES"<<std::endl;
            continue;
        }
        size_t k;
        if ((k = str.size()) % 3) {
            std::cout<<"NO"<<std::endl;
            continue;
        }
        std::string right_str = "";
        for (size_t i = 0; i < k / 3; ++i) {
            right_str += "ab";
        }
        for (size_t i = 0; i < k / 3; ++i) {
            right_str += "c";
        }
        if (str == right_str) {
            std::cout<<"YES"<<std::endl;
        }
        else {
            std::cout<<"NO"<<std::endl;
        }
    }
    return 0;
}
