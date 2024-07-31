#include <iostream>
#include <string>
#include <sstream>

/*
S → bS | aAB
A → bcA | ccA | ε
B → cbB | ε
--------------------------------------------
recursive descent inapplicability:
first(A) = {b, c}
follow(A) = {c}

first(A) ⋂ follow(A) = {c} != ∅
--------------------------------------------

L(G) = {(b)^n(a)(bc | cc)^k(cb)^m, n,k,m >=0}

--------------------------------------------
(->(4 rule) -> (3 rule) -> (2 rule) ->)
equivalent: 
S → bS | aA
A → bcA | cP | ε
P → cA | bB
B → cbB | ε
*/

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
    void P();
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

// S → bS | aA
void Parser::S() {
    switch (c)
    {
    // S → bS
    case 'b':
        c = str->get();
        S();
        break;
    // S -> aA
    case 'a':
        c = str->get();
        A();
        break;
    default:
        throw std::exception();
        break;
    }
}

// A → bcA | cP | ε
void Parser::A() {
    switch (c)
    {
    // A → bcA
    case 'b':
        c = str->get();
        if (c != 'c') {
            throw std::exception();
        }
        c = str->get();
        A();
        break;
    // A -> cP
    case 'c':
        c = str->get();
        P();
        break;
    // A -> ε
    default:
        break;
    }
}

// P → cA | bB
void Parser::P() {
    switch (c)
    {
    // P → cA
    case 'c':
        c = str->get();
        A();
        break;
    // P -> bB
    case 'b':
        c = str->get();
        B();
        break;
    default:
        throw std::exception();
        break;
    }
}

// B → cbB | ε
void Parser::B() {
    switch (c)
    {
    // B → cbB
    case 'c':
        c = str->get();
        if (c != 'b') {
            throw std::exception();
        }
        c = str->get();
        B();
        break;
    // B -> ε
    default:
        break;
    }
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