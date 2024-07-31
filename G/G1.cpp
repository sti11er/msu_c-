#include <iostream>
#include <climits>
#include <exception>

namespace no_exceptions
{

    enum ErrorCodes
    {
        SUCCESS,
        OVERFLOW,
        DIVBYZERO,
    };

    static const char *errors[] =
    {
        [SUCCESS] = "Success",
        [OVERFLOW] = "Integer overflow",
        [DIVBYZERO] = "Division by zero",
    };

    struct Expression
    {
        virtual int get_value(int &) const = 0;
        virtual ~Expression() = default;
    };

    class IntVariable 
    {
    public:
        IntVariable();
        void set_value(int);
        int get_value() const;
    private:
        int var; 
    };

    IntVariable::IntVariable(): var(0) {}

    void IntVariable::set_value(int x) {
        var = x;
    }

    int IntVariable::get_value() const {
        return var;
    }

    struct VariableExpression: Expression
    {
        const IntVariable &var;
        VariableExpression(const IntVariable &);
        int get_value(int &) const;  
    };

    VariableExpression::VariableExpression(const IntVariable& var_): var(var_) {}

    int VariableExpression::get_value(int &value) const {
        value = var.get_value();
        return SUCCESS;
    }

    struct LiteralExpression: Expression
    {
        int lit;
        LiteralExpression(int);
        int get_value(int &) const;
    };

    LiteralExpression::LiteralExpression(int lit_): lit(lit_) {}

    int LiteralExpression::get_value(int & value) const {
        value = lit;
        return SUCCESS;
    }

    struct BinaryExpression: Expression
    {
        Expression const & left;
        Expression const & right;
        BinaryExpression(Expression const &left_, Expression const &right_);
    };

    BinaryExpression::BinaryExpression(Expression const &left_, Expression const &right_): 
    left(left_), right(right_) {}

    struct SumExpression: BinaryExpression
    {
        SumExpression(Expression const &left_, Expression const &right_);
        int get_value(int &) const;
    };

    SumExpression::SumExpression(Expression const &left_, Expression const &right_):
    BinaryExpression(left_, right_) {}

    int
    SumExpression::get_value(int &value) const
    {
        int ret;

        int left_value;
        if ((ret = left.get_value(left_value)) != 0) {
            return ret;
        }

        int right_value;
        if ((ret = right.get_value(right_value)) != 0) {
            return ret;
        }

        if (((left_value >= 0) && (right_value > INT_MAX - left_value))
            || ((left_value < 0) && (right_value < INT_MIN - left_value))) {
            return OVERFLOW;
        }

        value = left_value + right_value;
        return SUCCESS;
    }

    struct MultExpression: BinaryExpression
    {
        MultExpression(Expression const &left_, Expression const &right_);
        int get_value(int &) const;
    };

    MultExpression::MultExpression(Expression const &left_, Expression const &right_):
    BinaryExpression(left_, right_) {}

    int MultExpression::get_value(int &value) const {
        int ret;

        int left_value;
        if ((ret = left.get_value(left_value)) != 0) {
            return ret;
        }

        int right_value;
        if ((ret = right.get_value(right_value)) != 0) {
            return ret;
        }

        if ((left_value > 0 && (right_value > INT_MAX / left_value || right_value < INT_MIN / left_value))
            || (left_value < 0 && (right_value < INT_MAX / left_value || right_value > INT_MIN / left_value))) {
            return OVERFLOW;
        }

        value = left_value * right_value;
        return SUCCESS;
    }

    struct DivExpression: BinaryExpression
    {
        DivExpression(Expression const &left_, Expression const &right_);
        int get_value(int &value) const; 
    };

    DivExpression::DivExpression(Expression const &left_, Expression const &right_):
    BinaryExpression(left_, right_) {}

    int DivExpression::get_value(int &value) const {
        int ret;

        int left_value;
        if ((ret = left.get_value(left_value)) != 0) {
            return ret;
        }

        int right_value;
        if ((ret = right.get_value(right_value)) != 0) {
            return ret;
        }
        
        if (right_value == 0) {
            return DIVBYZERO;
        }

        if (left_value == INT_MIN && right_value == -1) {
            return OVERFLOW;
        }

        value = left_value / right_value;
        return SUCCESS;
    }
}

namespace with_exceptions
{
    enum ErrorCodes
    {
        SUCCESS,
        OVERFLOW,
        DIVBYZERO,
    };

    static const char *errors[] =
    {
        [SUCCESS] = "Success",
        [OVERFLOW] = "Integer overflow",
        [DIVBYZERO] = "Division by zero",
    };

    class MyException: public std::exception
    {
    public:
        MyException(const char *);
        const char* what() const noexcept;
    private:
        const char *msg_error;
    };

    MyException::MyException(const char *str): msg_error(str) {}

    const char * MyException::what() const noexcept {
        return msg_error;
    } 

    struct Expression
    {
        virtual int get_value() const = 0;
        virtual ~Expression() = default;
    };

    class IntVariable 
    {
    public:
        IntVariable();
        void set_value(int);
        int get_value() const;
    private:
        int var; 
    };

    IntVariable::IntVariable(): var(0) {}

    void IntVariable::set_value(int x) {
        var = x;
    }

    int IntVariable::get_value() const {
        return var;
    }

    struct VariableExpression: Expression
    {
        const IntVariable &var;
        VariableExpression(const IntVariable &);
        int get_value() const;  
    };

    VariableExpression::VariableExpression(const IntVariable& var_): var(var_) {}

    int VariableExpression::get_value() const {
        return var.get_value();
    }

    struct LiteralExpression: Expression
    {
        int lit;
        LiteralExpression(int);
        int get_value() const;
    };

    LiteralExpression::LiteralExpression(int lit_): lit(lit_) {}

    int LiteralExpression::get_value() const {
        return lit;
    }

    struct BinaryExpression: Expression
    {
        Expression const & left;
        Expression const & right;
        BinaryExpression(Expression const &left_, Expression const &right_);
    };

    BinaryExpression::BinaryExpression(Expression const &left_, Expression const &right_): 
    left(left_), right(right_) {}

    struct SumExpression: BinaryExpression
    {
        SumExpression(Expression const &left_, Expression const &right_);
        int get_value() const;
    };

    SumExpression::SumExpression(Expression const &left_, Expression const &right_):
    BinaryExpression(left_, right_) {}

    int
    SumExpression::get_value() const
    {
        int left_value = left.get_value();
        int right_value = right.get_value();

        if (((left_value >= 0) && (right_value > INT_MAX - left_value))
            || ((left_value < 0) && (right_value < INT_MIN - left_value))) {
            throw MyException(errors[1]);
        }

        return left_value + right_value;
    }

    struct MultExpression: BinaryExpression
    {
        MultExpression(Expression const &left_, Expression const &right_);
        int get_value() const;
    };

    MultExpression::MultExpression(Expression const &left_, Expression const &right_):
    BinaryExpression(left_, right_) {}

    int MultExpression::get_value() const {
        int left_value = left.get_value();
        int right_value = right.get_value();

        if (((left_value > 0) && (right_value > INT_MAX / left_value || right_value < INT_MIN / left_value))
            || ((left_value < 0) && (right_value < INT_MAX / left_value || right_value > INT_MIN / left_value))) {
            throw MyException(errors[1]);;
        }

        return left_value * right_value;
    }

    struct DivExpression: BinaryExpression
    {
        DivExpression(Expression const &left_, Expression const &right_);
        int get_value() const; 
    };

    DivExpression::DivExpression(Expression const &left_, Expression const &right_):
    BinaryExpression(left_, right_) {}

    int DivExpression::get_value() const {
        int left_value = left.get_value();
        int right_value = right.get_value();
        
        if (right_value == 0) {
            throw MyException(errors[2]);;
        }

        if (left_value == INT_MIN && right_value == -1) {
            throw MyException(errors[1]);;
        }

        return left_value / right_value;
    }
}

int main()
{
    {
        using namespace no_exceptions;
        IntVariable x, y, z;
        VariableExpression ex(x);
        VariableExpression ey(y);
        VariableExpression ez(z);
        LiteralExpression c(2);
        MultExpression e1(c, ey); // 2 * y
        SumExpression e2(ex, e1); // x + (2 * y)
        DivExpression e3(ez, e2); // z / (x + 2*y)
        x.set_value(10);
        y.set_value(20);
        z.set_value(130);
        int value, ret;
        if ((ret = e3.get_value(value)) == 0) {
            std::cout << value << std::endl;
        } else {
            std::cout << errors[ret] << std::endl;
        }
    }
    {
        using namespace with_exceptions;
        try 
        {
            IntVariable x, y, z;
            VariableExpression ex(x);
            VariableExpression ey(y);
            VariableExpression ez(z);
            LiteralExpression c(2);
            MultExpression e1(c, ey); // 2 * y
            SumExpression e2(ex, e1); // x + (2 * y)
            DivExpression e3(ez, e2); // z / (x + 2*y)
            x.set_value(10);
            y.set_value(20);
            z.set_value(130);
            std::cout << e3.get_value() << std::endl;
        }
        catch (std::exception& arg) {
            std::cout << arg.what() << std::endl;
        }
        try     // OVERFLOW 
        {
            IntVariable x;
            VariableExpression ex(x);
            LiteralExpression c(INT_MIN);
            MultExpression e1(c, ex);
            x.set_value(5);
            std::cout << e1.get_value() << std::endl;
        }
        catch (std::exception& arg) {
            std::cout << arg.what() << std::endl;
        }
        try    // DIVBYZERO
        {
            IntVariable x;
            VariableExpression ex(x);
            LiteralExpression c(2);
            DivExpression e1(c, ex);
            x.set_value(0);
            std::cout << e1.get_value() << std::endl;
        }
        catch (std::exception& arg) {
            std::cout << arg.what() << std::endl;
        }
    }
}