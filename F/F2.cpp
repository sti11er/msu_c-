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

    class Expression_prev
    {
    public:
        virtual std::ostream& print(std::ostream&) const = 0;
        virtual int get_priority() const = 0;
        virtual ~Expression_prev();
        virtual Expression_prev* cpy() const = 0;
    };

    Expression_prev::~Expression_prev() {}

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

    class VariableExpression: public Expression_prev
    {
    public:
        VariableExpression(const IntVariable&);
        std::ostream& print(std::ostream&) const;
        int get_priority() const;
        Expression_prev* cpy() const;
    private:
        const IntVariable& var;
    };
    
    Expression_prev* VariableExpression::cpy() const {
        return new VariableExpression(var);
    }

    VariableExpression::VariableExpression(const IntVariable& other): var(other) {}

    std::ostream& VariableExpression::print(std::ostream& stream) const {
        stream<<var.getter();
        return stream;
    }

    int VariableExpression::get_priority() const {
        return VAR;
    }

    class LiteralExpression: public Expression_prev
    {
    public:
        std::ostream& print(std::ostream&) const;
        LiteralExpression(int);
        int get_priority() const;
        Expression_prev* cpy() const;
    private:
        int val;
    };

    Expression_prev* LiteralExpression::cpy() const {
        return new LiteralExpression(val);
    }

    std::ostream& LiteralExpression::print(std::ostream& stream) const {
        stream<<val;
        return stream;
    }

    LiteralExpression::LiteralExpression(int val_): val(val_) {}

    int LiteralExpression::get_priority() const {
        return LITERAL;
    }

    class TwoArgs: public Expression_prev
    {
    public:
        int get_priority() const;
        TwoArgs(Expression_prev *, Expression_prev *, const char*, int);
        ~TwoArgs();
        std::ostream& print(std::ostream&) const;
        Expression_prev* cpy() const;
    private:
        int priority;
        Expression_prev* left;
        Expression_prev* right;
        const char *operation;
    };

    Expression_prev* TwoArgs::cpy() const {
        return new TwoArgs(left->cpy(), right->cpy(), operation, priority);
    }

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

    TwoArgs::TwoArgs(Expression_prev *l, Expression_prev *r, const char*o, int p) {
        left = l;
        right = r;
        operation = o;
        priority = p;
    }

    TwoArgs::~TwoArgs() {
        delete left;
        delete right;
    }

    class OneArgs: public Expression_prev 
    {
    public:
        int get_priority() const;
        OneArgs(Expression_prev *, const char*, int);
        ~OneArgs();
        std::ostream& print(std::ostream&) const;
        Expression_prev* cpy() const;
    private:
        Expression_prev* cur;
        const char *operation;
        int priority; 
    };

    Expression_prev* OneArgs::cpy() const {
        return new OneArgs(cur->cpy(), operation, priority);
    }

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

    OneArgs::OneArgs(Expression_prev *c, const char*o, int p) {
        cur = c;
        operation = o;
        priority = p;
    }

    OneArgs::~OneArgs() {
        delete cur;
    }

    class SumExpression: public TwoArgs
    {
    public:
        SumExpression(Expression_prev*, Expression_prev*);
    };

    SumExpression::SumExpression(Expression_prev*l, Expression_prev*r): 
    TwoArgs(l, r, "+", ADD) {}

    class SubExpression: public TwoArgs
    {
    public:
        SubExpression(Expression_prev*, Expression_prev*);
    };

    SubExpression::SubExpression(Expression_prev*l, Expression_prev*r): 
    TwoArgs(l, r, "-", SUB) {}

    class MultiplyExpression: public TwoArgs
    {
    public:
        MultiplyExpression(Expression_prev*, Expression_prev*);
    };

    MultiplyExpression::MultiplyExpression(Expression_prev*l, Expression_prev*r): 
    TwoArgs(l, r, "*", MULT) {}

    class DivisionExpression: public TwoArgs
    {
    public:
        DivisionExpression(Expression_prev*, Expression_prev*);
    };

    DivisionExpression::DivisionExpression(Expression_prev*l, Expression_prev*r): 
    TwoArgs(l, r, "/", DIV) {}

    class NegativeExpression: public OneArgs
    {
    public:
        NegativeExpression(Expression_prev*);
    };

    NegativeExpression::NegativeExpression(Expression_prev*c): 
    OneArgs(c, "-", NEG) {}
    
    class Expression 
    {
    public:
        Expression(int);
        Expression(const Expression&);
        Expression(IntVariable &);
        Expression(Expression_prev *);
        ~Expression();
        Expression_prev* getter() const;
        friend class PrettyPrinter;
        Expression& operator= (const Expression&);
        friend Expression operator+ (const Expression&, const Expression&);
        friend Expression operator- (const Expression&, const Expression&);
        friend Expression operator* (const Expression&, const Expression&);
        friend Expression operator/ (const Expression&, const Expression&);
        friend Expression operator- (const Expression&);
    private:
        Expression_prev* expr;
    };

    Expression_prev* Expression::getter() const {
        return expr;
    }

    Expression::Expression(int v) {
        expr = new LiteralExpression(v);
    }

    Expression::Expression(const Expression& x) {
        expr = x.expr->cpy();
    }   

    Expression::Expression(IntVariable &v) {
        expr = new VariableExpression(v);
    }

    Expression::Expression(Expression_prev *other) {
        expr = other;
    }

    Expression::~Expression() {
        delete expr;
    }

    Expression& Expression::operator= (const Expression &x) {
        if (this == &x) {
            return *this;
        }

        delete[] expr;
        expr = x.expr->cpy();

        return *this;
    }

    Expression operator+ (const Expression& left, const Expression& right) {
        return new SumExpression(left.getter(), right.getter());
    }

    Expression operator- (const Expression& left, const Expression& right) {
        return new SubExpression(left.getter(), right.getter());
    }

    Expression operator* (const Expression& left, const Expression& right) {
        return new MultiplyExpression(left.getter(), right.getter());
    }

    Expression operator/ (const Expression& left, const Expression& right) {
        return new DivisionExpression(left.getter(), right.getter());
    }

    Expression operator- (const Expression& operand) {
        return new NegativeExpression(operand.getter());
    }

    class Output
    {
    public:
        Output(const Expression_prev &);
        friend std::ostream& operator<<(std::ostream& stream, const Output& p);
    private:
        const Expression_prev& expr;
    };

    Output::Output(const Expression_prev& e): expr(e) {}

    std::ostream& operator<<(std::ostream& stream, const Output& out) {
        out.expr.print(stream);
        return stream;
    }

    class PrettyPrinter
    {
    public:
        Output get_infix(const Expression &) const;
    };

    Output PrettyPrinter::get_infix(const Expression &x) const {
        return Output(*(x.expr));
    }
}

int main()
{
    using namespace equations;
    IntVariable x("x");
    Expression expression = ((x + x) + x) * x - (7 - x);
    puts("------");
    // Expression expression2 = expression - expression;
    // PrettyPrinter printer;
    // std::cout << printer.get_infix(expression) << std::endl;
    // std::cout << printer.get_infix(expression2) << std::endl;
}