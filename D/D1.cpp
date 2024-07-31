#include <iostream>
using namespace std;

namespace equations
{
    class IntVariable {
    public:
        IntVariable();
        IntVariable(const int);
        friend ostream& operator<< (ostream&, const IntVariable &);
    private:
        int x;
    };

    IntVariable::IntVariable(const int v): x(v) {}
    IntVariable::IntVariable(): x(0) {}

    ostream& operator<< (ostream &out, const IntVariable &obj)
    {
        return out << obj.x;
    }

    class Expression {
    public:
        Expression();
        Expression(int);
        Expression(IntVariable &);
    private:
        bool error;
        bool is_equal;
        // Expression: kx + b
        IntVariable * x;
        int k;
        int b;
        friend int solve(const Expression& expr);
        friend Expression operator+ (const Expression&l, const Expression&r);
        friend Expression operator- (const Expression&l, const Expression&r);
        friend Expression operator* (const Expression&l, const Expression&r);
        friend Expression operator- (const Expression&x_);
        friend Expression operator== (const Expression&l, const Expression&r);
    };

    Expression::Expression(): 
        error(false), is_equal(false), 
        x(nullptr), k(0), b(0) {}

    Expression::Expression(int b_): 
        error(false), is_equal(false), 
        x(nullptr), k(0), b(b_) {}

    Expression::Expression(IntVariable& x_): 
        error(false), is_equal(false), 
        x(&x_), k(1), b(0) {}

    int solve(const Expression& expr) {
        if (((expr.k == 0) && (expr.b == 0)) 
        || ((expr.k == 0) && (expr.b != 0)) 
        || (expr.error) || (not expr.is_equal) 
        || (-expr.b) % expr.k != 0) {
            return 1;
        }

        *(expr.x) = -expr.b / expr.k;
        return 0;
    }
    
    Expression operator+ (const Expression&l, const Expression&r) {
        Expression tmp;

        if ((l.error || r.error)||((l.x != 0) && (r.x != 0) && (l.x != r.x))) {
            tmp.error = true;
            return tmp;
        }

        tmp.k = l.k + r.k;
        tmp.b = l.b + r.b;

        tmp.x = l.x != nullptr ? l.x : r.x;
        return tmp;
    }

    Expression operator- (const Expression&l, const Expression&r) {
        Expression tmp;

        if ((l.error || r.error)||((l.x != 0) && (r.x != 0) && (l.x != r.x))) {
            tmp.error = true;
            return tmp;
        }

        tmp.k = l.k - r.k;
        tmp.b = l.b - r.b;
        tmp.x = l.x != nullptr ? l.x : r.x;
        return tmp;
    }

    Expression operator* (const Expression&l, const Expression&r) {
        Expression tmp;

        if ((l.error || r.error)||(l.k * r.k != 0)) {
            tmp.error = true; 
            return tmp;
        }

        // kx * b
        if (r.x == nullptr) {
            tmp.k = l.k * r.b;
            tmp.b = l.b * r.b;
        // b * kx
        } else {
            tmp.k = l.b * r.k;
            tmp.b = l.b * r.b;
        }

        tmp.x = l.x != nullptr ? l.x : r.x;
        
        return tmp;
    }


    Expression operator- (const Expression&x_) {
        Expression tmp;

        tmp.error = x_.error;
        tmp.k = -x_.k;
        tmp.b = -x_.b;
        tmp.x = x_.x;

        return tmp;
    }

    Expression operator== (const Expression&l, const Expression&r) {
        Expression tmp;

        tmp = l - r;
        tmp.is_equal = true;  
     
        return tmp;
    }
}