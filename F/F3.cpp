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

    class OldExpression
    {
    public:
        virtual std::ostream& print(std::ostream&) const = 0;
        virtual int get_priority() const = 0;
        virtual ~OldExpression();
        // virtual OldExpression * copy() const = 0;
    };

    OldExpression::~OldExpression() { }

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

    class VariableExpression: public OldExpression
    {
    public:
        VariableExpression(const IntVariable&);
        std::ostream& print(std::ostream&) const;
        int get_priority() const;
        virtual OldExpression * copy() const;
    private:
        const IntVariable& var;
    };

    OldExpression *
    VariableExpression::copy() const
    {
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

    class LiteralExpression: public OldExpression
    {
    public:
        std::ostream& print(std::ostream&) const;
        LiteralExpression(int);
        int get_priority() const;
        virtual OldExpression * copy() const;
    private:
        int val;
    };

    OldExpression *
    LiteralExpression::copy() const
    {
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

    class TwoArgs: public OldExpression
    {
    public:
        int get_priority() const;
        TwoArgs(OldExpression *, OldExpression *, const char*, int);
        ~TwoArgs();
        std::ostream& print(std::ostream&) const;
        OldExpression * copy() const;
    private:
        int priority;
        OldExpression* left;
        OldExpression* right;
        const char *operation;
    };

    OldExpression* TwoArgs::copy() const {
        return new TwoArgs(left->copy(), right->copy(), operation, priority);
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

    TwoArgs::TwoArgs(OldExpression *l, OldExpression *r, const char*o, int p) {
        left = l;
        right = r;
        operation = o;
        priority = p;
    }

    TwoArgs::~TwoArgs() {
        delete left;
        delete right;
    }

    class OneArgs: public OldExpression 
    {
    public:
        int get_priority() const;
        OneArgs(OldExpression *, const char*, int);
        ~OneArgs();
        std::ostream& print(std::ostream&) const;
        OldExpression* copy() const;
    private:
        OldExpression* cur;
        const char *operation;
        int priority; 
    };

    OldExpression* OneArgs::copy() const {
        return new OneArgs(cur->copy(), operation, priority);
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

    OneArgs::OneArgs(OldExpression *c, const char*o, int p) {
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
        SumExpression(OldExpression*, OldExpression*);
    };

    SumExpression::SumExpression(OldExpression*l, OldExpression*r): 
    TwoArgs(l, r, "+", ADD) {}

    class SubExpression: public TwoArgs
    {
    public:
        SubExpression(OldExpression*, OldExpression*);
    };

    SubExpression::SubExpression(OldExpression*l, OldExpression*r): 
    TwoArgs(l, r, "-", SUB) {}

    class MultiplyExpression: public TwoArgs
    {
    public:
        MultiplyExpression(OldExpression*, OldExpression*);
    };

    MultiplyExpression::MultiplyExpression(OldExpression*l, OldExpression*r): 
    TwoArgs(l, r, "*", MULT) {}

    class DivisionExpression: public TwoArgs
    {
    public:
        DivisionExpression(OldExpression*, OldExpression*);
    };

    DivisionExpression::DivisionExpression(OldExpression*l, OldExpression*r): 
    TwoArgs(l, r, "/", DIV) {}

    class NegativeExpression: public OneArgs
    {
    public:
        NegativeExpression(OldExpression*);
    };

    NegativeExpression::NegativeExpression(OldExpression*c): 
    OneArgs(c, "-", NEG) {}

    class Expression
    {
    public:
        Expression(const Expression &);
        Expression(int);
        Expression(IntVariable &);
        Expression(OldExpression *);
        ~Expression();
        Expression & operator = (const Expression &);
    private:
        friend class PrettyPrinter;
        friend Expression operator + (Expression, Expression);
        friend Expression operator - (Expression, Expression);
        friend Expression operator * (Expression, Expression);
        friend Expression operator / (Expression, Expression);
        friend Expression operator - (Expression);
        OldExpression *ptr;
    };

    Expression::Expression(const Expression & x) {
        ptr = x.ptr->copy();
    }

    Expression::Expression(int x) {
        ptr = new LiteralExpression(x);
    }

    Expression::Expression(IntVariable & x) {
        ptr = new VariableExpression(x);
    }

    Expression::Expression(OldExpression * x) {
        ptr = x;
    }

    Expression::~Expression() {
        delete ptr;
    }

    Expression &
    Expression::operator = (const Expression & x) {
        if (this == &x) {
            return *this;
        }
        delete ptr;
        ptr = x.ptr->copy();
        return *this;
    }

    Expression
    operator + (Expression left, Expression right) {
        return new SumExpression(left.ptr->copy(), right.ptr->copy());
    }

    Expression
    operator - (Expression left, Expression right)
    {
        return new SubExpression(left.ptr->copy(), right.ptr->copy());
    }

    Expression
    operator * (Expression left, Expression right) {
        return new MultiplyExpression(left.ptr->copy(), right.ptr->copy());
    }

    Expression
    operator / (Expression left, Expression right) {
        return new DivisionExpression(left.ptr->copy(), right.ptr->copy());
    }

    Expression
    operator - (Expression x) {
        return new NegativeExpression(x.ptr->copy());
    }

    class Output
    {
    public:
        Output(const OldExpression &);
        friend std::ostream& operator<<(std::ostream& stream, const Output& p);
    private:
        const OldExpression& expr;
    };

    Output::Output(const OldExpression& e): expr(e) {}

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
        return Output(*(x.ptr));
    }
}

int 
main()
{
    using namespace equations;
    IntVariable x("x");
    Expression expression = ((x + x) + x) * x - (7 - x);
    // Expression expression2 = expression2 - expression2;
    PrettyPrinter printer;
    std::cout << printer.get_infix(expression) << std::endl;
    //std::cout << printer.get_infix(expression2) << std::endl;
}