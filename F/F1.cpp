#include <iostream>
#include <cstring>

namespace equations
{
    enum
    {
        VAR = 0, 
        LITERAL = 0,
        NEG = 0,
        MULT = 1, 
        DIV = 1,
        ADD = 2, 
        SUB = 2
    };

    class Expression
    {
    public:
        virtual std::ostream& print(std::ostream&) const = 0;
        virtual int get_priority() const = 0;
        virtual ~Expression();
    };

    Expression::~Expression() { std::cout << "expr\n"; }

    class IntVariable
    {
    public:
        IntVariable(const char*);
        IntVariable(const IntVariable&);
        const char* getter() const;
        ~IntVariable();
        IntVariable& operator= (const IntVariable&);
    private:
        char *var;
    };

    const char* IntVariable::getter() const {
        return var;
    }

    IntVariable::IntVariable(const char* x) {
        var = new char[strlen(x) + 1];
        strcpy(var, x);
    }

    IntVariable::IntVariable(const IntVariable& other) {
        var = new char[strlen(other.var) + 1];
        strcpy(var, other.var);
    }

    IntVariable::~IntVariable() {
        delete[] var;
    }

    IntVariable& IntVariable::operator= (const IntVariable& other) {
        if (&other == this)
            return *this;

        delete[] var;
        var = new char[strlen(other.var) + 1];
        strcpy(var, other.var);

        return *this;
    }

    class VariableExpression: public Expression
    {
    public:
        VariableExpression(const IntVariable&);
        std::ostream& print(std::ostream&) const;
        int get_priority() const;
    private:
        const IntVariable& var;
    };

    VariableExpression::VariableExpression(const IntVariable& other): var(other) {}

    std::ostream& VariableExpression::print(std::ostream& stream) const {
        stream<<var.getter();
        return stream;
    }

    int VariableExpression::get_priority() const {
        return VAR;
    }

    class LiteralExpression: public Expression
    {
    public:
        std::ostream& print(std::ostream&) const;
        LiteralExpression(int);
        int get_priority() const;
    private:
        int val;
    };

    std::ostream& LiteralExpression::print(std::ostream& stream) const {
        stream<<val;
        return stream;
    }

    LiteralExpression::LiteralExpression(int val_): val(val_) {}

    int LiteralExpression::get_priority() const {
        return LITERAL;
    }

    class TwoArgs: public Expression
    {
    public:
        int get_priority() const;
        TwoArgs(Expression *, Expression *, const char*, int);
        ~TwoArgs();
        std::ostream& print(std::ostream&) const;
    private:
        int priority;
        Expression* left;
        Expression* right;
        const char *operation;
    };

    int TwoArgs::get_priority() const {
        return priority;
    }

    std::ostream& TwoArgs::print(std::ostream& stream) const {
        bool is_block_left = get_priority() < (left->get_priority());
        if (is_block_left) {
            stream << '(';
        }
        left->print(stream);
        if (is_block_left) {
            stream << ')';
        }
        stream << ' ' << operation << ' ';

        bool is_block_right = get_priority() <= (right->get_priority());
        if (is_block_right) {
            stream << '(';
        }
        right->print(stream);
        if (is_block_right) {
            stream << ')';
        }
        return stream;
    }

    TwoArgs::TwoArgs(Expression *l, Expression *r, const char*o, int p) {
        left = l;
        right = r;
        operation = o;
        priority = p;
    }

    TwoArgs::~TwoArgs() {
        std::cout << operation << std::endl;
        delete left;
        delete right;
    }

    class OneArgs: public Expression 
    {
    public:
        int get_priority() const;
        OneArgs(Expression *, const char*, int);
        ~OneArgs();
        std::ostream& print(std::ostream&) const;
    private:
        Expression* cur;
        const char *operation;
        int priority; 
    };

    int OneArgs::get_priority() const {
        return priority;
    }

    std::ostream& OneArgs::print(std::ostream& stream) const {
        stream << operation;
        bool is_block = get_priority() < (cur->get_priority());
        if (is_block) {
            stream << '(';
        }
        cur->print(stream);
        if (is_block) {
            stream << ')';
        }
        return stream;
    }

    OneArgs::OneArgs(Expression *c, const char*o, int p) {
        cur = c;
        operation = o;
        priority = p;
    }

    OneArgs::~OneArgs() {
        std::cout << operation << std::endl;
        delete cur;
    }

    class SumExpression: public TwoArgs
    {
    public:
        SumExpression(Expression*, Expression*);
    };

    SumExpression::SumExpression(Expression*l, Expression*r): 
    TwoArgs(l, r, "+", ADD) {}

    class SubExpression: public TwoArgs
    {
    public:
        SubExpression(Expression*, Expression*);
    };

    SubExpression::SubExpression(Expression*l, Expression*r): 
    TwoArgs(l, r, "-", SUB) {}

    class MultiplyExpression: public TwoArgs
    {
    public:
        MultiplyExpression(Expression*, Expression*);
    };

    MultiplyExpression::MultiplyExpression(Expression*l, Expression*r): 
    TwoArgs(l, r, "*", MULT) {}

    class DivisionExpression: public TwoArgs
    {
    public:
        DivisionExpression(Expression*, Expression*);
    };

    DivisionExpression::DivisionExpression(Expression*l, Expression*r): 
    TwoArgs(l, r, "/", DIV) {}

    class NegativeExpression: public OneArgs
    {
    public:
        NegativeExpression(Expression*);
    };

    NegativeExpression::NegativeExpression(Expression*c): 
    OneArgs(c, "-", NEG) {}

    class Output
    {
    public:
        Output(const Expression &);
        friend std::ostream& operator<<(std::ostream& stream, const Output& p);
    private:
        const Expression& expr;
    };

    Output::Output(const Expression& e): expr(e) {}

    std::ostream& operator<<(std::ostream& stream, const Output& out) {
        out.expr.print(stream);
        return stream;
    }

    class PrettyPrinter
    {
    public:
        Output get_infix(const Expression &) const;
    };

    Output PrettyPrinter::get_infix(const Expression &expr) const {
        return Output(expr);
    }

    Expression *expr(IntVariable &v)
    {
        return new VariableExpression(v);
    }

    Expression *expr(int v)
    {
        return new LiteralExpression(v);
    }

    Expression *plus(Expression *left, Expression *right)
    {
        return new SumExpression(left, right);
    }

    Expression *minus(Expression *left, Expression *right)
    {
        return new SubExpression(left, right);
    }

    Expression *mult(Expression *left, Expression *right)
    {
        return new MultiplyExpression(left, right);
    }

    Expression *div(Expression *left, Expression *right)
    {
        return new DivisionExpression(left, right);
    }

    Expression *neg(Expression *operand)
    {
        return new NegativeExpression(operand);
    }
}

int 
main()
{
    using namespace equations;
    IntVariable x("x"), y("y"), z("z");
    Expression const * expression =
        minus(
            mult(
                plus(
                    plus(expr(x), expr(x)),
                    expr(x)
                ),
                expr(x)
            ),
            minus(expr(7), expr(x))
        );

    PrettyPrinter printer;
    // -x - (x + x + (-1 + y)) * x + (2 - -z)
    std::cout << printer.get_infix(*expression) << std::endl;
    // using associativity:
    // ((x + y) + z) -> x + y + z
    // ((x + y) - z) -> x + y - z
    // (x + (y + z)) -> x + (y + z)
    // using precedence:
    // ((x * y) + z) -> x * y + z
    // (x * (y + z)) -> x * (y + z)
    puts("-------");
    delete expression;
}