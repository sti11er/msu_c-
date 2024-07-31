#include <iostream>
#include <exception>
#include <limits> 

class Data
{
public:
    virtual ~Data() = default;
    virtual Data* clone() const = 0;
};

class Number: public Data
{
public:
    Number(int);
    Data* clone() const override;
    int value() const;
private:
    int num;
};

Number::Number(int n): num(n) {}

Data* Number::clone() const {
    return new Number(num);
}

int Number::value() const {
    return num;
}

class Text: public Data
{
public:
    Text(std::string);
    Data* clone() const override;
    std::string value() const;
private:
    std::string text;
};

Text::Text(std::string str): text(str) {}

Data* Text::clone() const {
    return new Text(text);
}

std::string Text::value() const {
    return text;
}

class BoundedStack
{
public:
    BoundedStack(size_t);
    BoundedStack(const BoundedStack&);
    ~BoundedStack();
    BoundedStack& operator= (const BoundedStack&);

    size_t size() const;
    void push(const Data &);
    Data *pop();
private:
    Data** stack = nullptr;
    size_t max_size = 0;
    size_t curr_size = 0;
};

BoundedStack::BoundedStack(size_t max) {
    max_size = max;
    curr_size = 0;
    stack = new Data*[max];

    for (size_t i = 0; i < max; ++i) {
        stack[i] = nullptr;
    } 
}


BoundedStack::BoundedStack(const BoundedStack& other) {
    BoundedStack tmp(other.max_size);
    tmp.curr_size = other.curr_size;  

    for (size_t i=0; i<tmp.curr_size; ++i) {
        tmp.stack[i] = (other.stack[i])->clone();
    }
    
    std::swap(stack, tmp.stack);    
    std::swap(curr_size, tmp.curr_size);
    std::swap(max_size, tmp.max_size);
}

BoundedStack& BoundedStack::operator= (const BoundedStack& other) {
    if (&other == this) {
        return *this;
    }
    
    BoundedStack tmp(other);
    std::swap(stack, tmp.stack);
    std::swap(max_size, tmp.max_size);
    std::swap(curr_size, tmp.curr_size);

    return *this;
}

BoundedStack::~BoundedStack() {
    for (size_t i = 0; i < curr_size; ++i) {
        if (stack[i]) {
            delete stack[i];
        }
    }

    if (stack) {
    	delete[] stack;
	}
}

size_t BoundedStack::size() const {
    return curr_size;
}

void BoundedStack::push(const Data &data) {
    if (curr_size >= max_size) {
        throw std::exception();
    }

    stack[curr_size++] = data.clone();
}
    
Data *BoundedStack::pop() {
    if (curr_size == 0) {
        throw std::exception();
    }

    return stack[--curr_size];
}