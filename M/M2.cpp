#include <exception>
#include <iostream>
#include <sstream>

using namespace std;


// S -> a <str << "2"> S <str << "a"> | bS <str << "b">
// T -> S | ε 

class Parser 
{
public:
    Parser();
public:
    bool parse(istream &) noexcept;
    stringstream& getter();
private:
    void gc();
    void S();
    void T();
    stringstream str;
    istream *stream;
    int c;
};

void 
Parser::gc() 
{
    c = stream->get();
}

Parser::Parser(): 
    stream(nullptr), 
    c(0) 
{}

stringstream &
Parser::getter() 
{
    return str;
}

bool
Parser::parse(istream & stream_) noexcept 
{
    stream = &stream_;
    gc();
    try {
        S();
    }
    catch (std::exception &) {
        return false;
    };
    return true;
}

// S -> a <str << "2"> S <str << "a"> | bS <str << "b">
void
Parser::S() 
{
    switch (c) {
        case 'a':
            gc();
            /*<*/
            str << '2';
            /*>*/
            T();
            /*<*/
            str << 'a';
            /*>*/
            break;
        case 'b':
            gc();
            T();
            /*<*/
            str << 'b';
            /*>*/
            break;
        default:
            throw exception();
            break;
    }
}

// T -> S | ε 
void
Parser::T() 
{
    switch (c) {
        case EOF:
            break;
        default:
            S();
            break;
    }
}

int
main() 
{
    std::string s;
    while (getline(std::cin, s)) {
        std::stringstream new_stream;
        Parser parser;
        string str;
        new_stream.str(s);
        if (parser.parse(new_stream)) {
            string buf;
            parser.getter() >> buf;
            cout << buf << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}

