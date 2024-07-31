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

    class Simplest {
    public:
        Simplest(int);
        Simplest(const char *p);
        Simplest(std::string);

        std::string getter() const;
    private:
        std::string str;
    };
    Simplest::Simplest(int k)
    {
        str = std::to_string(k);
    }
    Simplest::Simplest(std::string s)
    {
        str = s;
    }
    Simplest::Simplest(const char *s)
    {
        str = static_cast<std::string>(s);
    }

    std::string Simplest::getter() const
    {
        return str;
    }

    class SimplestExpression
    {   
    public:
        SimplestExpression(Simplest);
        std::ostream& print(std::ostream&) const;
        int get_priority() const;
    private:
        Simplest var;
    };

    SimplestExpression::SimplestExpression(Simplest v): var(v) {}

    std::ostream& SimplestExpression::print(std::ostream& stream) const {
        stream<<var.getter();
        return stream;
    }

    int SimplestExpression::get_priority() const {
        return VAR;
    }

    template <typename T, typename U>
    class TwoArgs
    {
    public:
        TwoArgs(T, U, std::string, int);

        int get_priority() const;
        std::ostream& print(std::ostream&) const;
    private:
        int priority;
        T left;
        U right;
        std::string operation;
    };

    template <typename T, typename U>
    TwoArgs<T, U>::TwoArgs(T l, U r, std::string o, int p):
        priority(p),
        left(l),
        right(r),
        operation(o) {
    }

    template <typename T, typename U>
    int TwoArgs<T, U>::get_priority() const {
        return priority; 
    }

    template <typename T, typename U>
    std::ostream& TwoArgs<T, U>::print(std::ostream& stream) const {
        bool is_block_left = get_priority() < (left.get_priority());
        if (is_block_left) {
            stream << '(';
        }
        left.print(stream);
        if (is_block_left) {
            stream << ')';
        }
        stream << ' ' << operation << ' ';

        bool is_block_right = get_priority() <= (right.get_priority());
        if (is_block_right) {
            stream << '(';
        }
        right.print(stream);
        if (is_block_right) {
            stream << ')';
        }
        return stream;
    }

    template <typename T>
    class OneArgs
    {
    public:
        OneArgs(T, std::string, int);

        int get_priority() const;
        std::ostream& print(std::ostream&) const;
    private:
        T cur;
        std::string operation;
        int priority; 
    };

    template <typename T>
    OneArgs<T>::OneArgs(T c, std::string o, int p):
        cur(c), 
        operation(o),
        priority(p) {
    }

    template <typename T>
    int OneArgs<T>::get_priority() const {
        return priority;
    }

    template <typename T>
    std::ostream& OneArgs<T>::print(std::ostream& stream) const {
        stream << operation;
        bool is_block = get_priority() < (cur.get_priority());
        if (is_block) {
            stream << '(';
        }
        cur.print(stream);
        if (is_block) {
            stream << ')';
        }
        return stream;
    }

    template <typename T>
    class Output
    {
    public:
        Output(T);
        T expr;
    };

    template <typename T>
    Output<T>::Output(T t): expr(t) {}

    template <typename T>
    std::ostream& operator<<(std::ostream& stream, Output<T> out) {
        out.expr.print(stream);
        return stream;
    }

    class PrettyPrinter {
    public:
        template <typename T>
        Output<T> get_infix(T t);
    };

    template <typename T>
    Output<T> PrettyPrinter::get_infix(T t) {
        return Output(t);
    }
    
    template <typename T>
    SimplestExpression expr(T v) {
        return SimplestExpression(v);
    }

    template <typename T, typename U>
    TwoArgs<T, U> plus(T left, U right)
    {
        return TwoArgs(left, right, "+", ADD);
    }

    template <typename T, typename U>
    TwoArgs<T, U> minus(T left, U right)
    {
        return TwoArgs(left, right, "-", SUB);
    }

    template <typename T, typename U>
    TwoArgs<T, U> mult(T left, U right)
    {
        return TwoArgs(left, right, "*", MULT);
    }

    template <typename T, typename U>
    TwoArgs<T, U> div(T left, U right)
    {
        return TwoArgs(left, right, "/", DIV);
    }

    template <typename T>
    OneArgs<T> neg(T operand)
    {
        return OneArgs(operand, "-", NEG);
    }
    using Variable = Simplest;
}
