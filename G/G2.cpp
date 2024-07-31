#include <iostream>
#include <exception>
#include <cstring>
#include <string>

void fill_by_different_strings(std::string *buf, size_t size, size_t len);

enum {ALPH_CAPACITY = 36};

class TokenPool
{
public:
    TokenPool(size_t);
    TokenPool(const TokenPool&) = delete;
    TokenPool& operator= (const TokenPool&) = delete;
    ~TokenPool();
    size_t token_length() const;
    void get_token(char *);
    void return_token(const char *);
private:
    std::string *tokens;
    size_t *access;
    size_t amount_tokens;
    size_t len_token;
};

TokenPool::TokenPool(size_t amount) {
    try {
        tokens = new std::string[amount];
        access = new size_t[amount];

        for (size_t i=0; i<amount; ++i) {
            access[i] = 1;
        }

        len_token = 0;
        amount_tokens = amount;

        while (amount != 0) {
            ++len_token;
            amount /= ALPH_CAPACITY;
        }
        
        fill_by_different_strings(tokens, amount_tokens, len_token);
    }
    catch (std::exception& obj) {
        delete[] tokens;
        delete[] access;
        throw;
    }
}

TokenPool::~TokenPool() {
    delete[] tokens;
    delete[] access;
}

size_t TokenPool::token_length() const {
    return len_token;
}

class MyExc: public std::exception
{
public:
    MyExc(const char *);
    const char* what() const noexcept;
private:
    const char *msg;
};

MyExc::MyExc(const char* str): msg(str) {}
const char* MyExc::what() const noexcept {
    return msg;
}


void TokenPool::get_token(char *addr) {
    for (size_t i=0; i<amount_tokens; ++i) {
        if (access[i]) {
            strcpy(addr, tokens[i].c_str());
            access[i] = 0;
            return;
        }
    }
    throw MyExc("free token not found");
}

void TokenPool::return_token(const char *addr) {
    for (size_t i=0; i<amount_tokens; ++i) {
        if (!access[i]) {
            if (!strcmp(addr, tokens[i].c_str())) {
                access[i] = 1;
                return;
            }
        }
    }
    throw MyExc("token access error");
}
