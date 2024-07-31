#include <iostream>
#include <sstream>
#include <exception>

class Parser
{
public:
    Parser();
    bool parse(std::istream &);
private:
    std::istream * str;
    int c;
    void S();
    void A();
    void B();
};

Parser::Parser(): str(0) {}

bool Parser::parse(std::istream& stream) {
    str = &stream;
    c = str->get();

    try {
        S();
    }
    catch (...) {
        return false;
    }

    if (str->eof()) {
        return true;
    }
    return false;
}

void Parser::S() {
    // S → AS
    if (c == 'b' || c == 'c') {
        A();
        S();
    }
    // S → B
    else {
        B();
    }
}

void Parser::A() {
    // A → b 
    if (c =='b')
    {
        c = str->get();
    }
    // A → c
    else if (c =='c')
    {
        c = str->get();
    }
    else {
        throw std::exception(); 
    }
}

void Parser::B() {
    // B → dBf
    if (c == 'd')
    {
        c = str->get();
        B();
        if (c != 'f') {
            throw std::exception();
        }
        c = str->get();
    }
    // B → a
    else if (c == 'a') {
        c = str->get();
    }
    // B → ε
}

int
main()
{
    std::string s;
    while (getline(std::cin, s)) {
        std::stringstream str;
        Parser parser;
        str.str(s);
        std::cout << (parser.parse(str) ? "YES"  :  "NO") << std::endl;
    }
}