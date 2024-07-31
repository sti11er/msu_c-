#include <iostream>

class Logger
{
public:
    static Logger& getLogger(int);
    static void set_global_severity(int);
    void set_severity(int);
    int get_severity() const;
    void log(const char *) const;
private:
    Logger();
    Logger(const Logger&) {};
    int local_severity;
    struct Elem {
        int key;
        Logger *obj;
    };
    class Array
    {
    public:
        Elem *p;
        int capacity;
        int global_severity;
        ~Array();
    };
    static Array arr;
    static void increase();
    static void add(int);
};