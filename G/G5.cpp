#include <string>
#include <exception>
#include <iostream>
#include <typeinfo>
#include <cstring>

class Data {
public:
    virtual ~Data();
    virtual Data * allocate() const = 0;
};

Data::~Data() {}

class Number : public Data {
public:
    Number(int);
    Data * allocate() const;
    int value() const;
private:
    int value_f;
};

Data *
Number::allocate() const {
    return new Number(value_f);
}

Number::Number(int x) {
    value_f = x;
}

int
Number::value() const {
    return value_f;
}

class Text: public Data {
public:
    Text(std::string);
    Data * allocate() const;
    std::string value() const;
private:
    std::string value_f;
};

Data *
Text::allocate() const {
    return new Text(value_f);
}

Text::Text(std::string x) {
    value_f = x;
}

std::string
Text::value() const {
    return value_f;
}

class BoundedStack {
public:
    BoundedStack(size_t);
    ~BoundedStack();
    BoundedStack(const BoundedStack &) = delete;
    BoundedStack & operator = (const BoundedStack &) = delete;
    void push(const Data &data);
    Data * pop();
private:
    size_t count_elem;
    size_t first_free;
    Data ** stack;
};

void
BoundedStack::push(const Data &data) {
    if (first_free == count_elem) {
        throw std::exception();
    }
    stack[first_free] = data.allocate();
    ++first_free;
}

Data *
BoundedStack::pop() {
    if (first_free == 0) {
        throw std::exception();
    }
    return stack[--first_free];
}

BoundedStack::BoundedStack(size_t x) {
    stack = new Data*[x];
    count_elem = x;
    first_free = 0;
}

BoundedStack::~BoundedStack() {
    for (size_t i = 0; i < first_free; ++i) {
        delete stack[i];
    }
    delete [] stack;
}

int
main() {
    try {
        BoundedStack stack(1000);
        Data * x1;
        Data * x2;
        for (size_t i = 0; i < 50; ++i) {
            stack.push(Number(i));
            stack.push(Text("OK"));
        }
        for (size_t i = 0; i < 50; ++i) {
            x1 = dynamic_cast<Text *>(stack.pop());
            x2 = dynamic_cast<Number *>(stack.pop());
            std::cout << (dynamic_cast<Text *>(x1))->value() << std::endl;
            std::cout << (dynamic_cast<Number *>(x2))->value() << std::endl;
            delete x1;
            delete x2;
        }
        for (size_t i = 0; i < 250; ++i) {
            stack.push(Number(i));
            stack.push(Text("OK"));
        }
        for (size_t i = 0; i < 250; ++i) {
            x1 = dynamic_cast<Text *>(stack.pop());
            x2 = dynamic_cast<Number *>(stack.pop());
            std::cout << (dynamic_cast<Text *>(x1))->value() << std::endl;
            std::cout << (dynamic_cast<Number *>(x2))->value() << std::endl;
            delete x1;
            delete x2;
        }
    }
    catch(std::exception & x) {
        std::cout << "ERROR" << std::endl;
    }
}
