#include <iostream>
#include <sstream>
#include <exception>

class Parser {
public:
    Parser();
    bool parse(std::istream &) noexcept;
private:
    int c;
    int amount_a;
    int amount_b;
    std::istream * stream;
    void S();
    void gc();
    void T();
};

Parser::Parser():
    c(0), 
    amount_a(0), 
    amount_b(0),
    stream(nullptr) 
{}

void
Parser::gc() {
    c = stream->get();
}

bool
Parser::parse(std::istream &stream_) noexcept {
    stream = &stream_;
    gc();
    try {
        S();
    }
    catch (std::exception &) {
        return false;
    }

    return true;
}

// S -> a <++amount_a> S | b <++amount_b> S | ε <if (amount_a != amount_b * 2) { throw std::exception(); }>
void
Parser::S() {
    switch (c) {
        case 'a': 
        {
            /*<*/
            ++amount_a;
            /*>*/
            gc();
            S();
            break;
        }
        case 'b':
        {
            /*<*/
            ++amount_b;
            /*>*/
            gc();
            S();
            break;
        }
        case EOF:
        {
            /*<*/
            if (amount_a != amount_b * 2) { 
                throw std::exception();
            }
            break;
            /*>*/
        }
        default:
        {
            throw std::exception();
        }
    }
}

int
main() {
    std::cout << 2 << std::endl;
    std::string s;
    while (getline(std::cin, s)) {
        std::stringstream new_stream;
        Parser parser;
        new_stream.str(s);
        std::cout << (parser.parse(new_stream) ? "YES" : "NO") << std::endl;
    }
    return 0;
}
