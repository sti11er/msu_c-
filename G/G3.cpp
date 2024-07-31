#include <iostream>
#include <exception>
#include <cstring>
#include <string>

class Action 
{
public:
    virtual ~Action() = default;
    virtual void run() = 0;
};

class TokenizedAction
{
public:
    TokenizedAction(TokenPool&, Action&);
    TokenizedAction(const TokenizedAction&) = delete;
    TokenizedAction& operator=(const TokenizedAction&) = delete;
    ~TokenizedAction();
    void run();
private:
    std::string token;
    TokenPool &token_pool;
    Action &action;
};

TokenizedAction::TokenizedAction(TokenPool&t, Action&a):
token_pool(t), action(a) {
    token_pool.get_token(token.data());
}  


TokenizedAction::~TokenizedAction() {
    token_pool.return_token(token.c_str());
} 

void TokenizedAction::run () {
    action.run();
}