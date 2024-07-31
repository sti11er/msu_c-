#include <cstring>
#include <iostream>

class String
{
private:
    char *str;
public:
    String();
    String(char c);
    String(const char *s);
    String(const String &obj);
    ~String();
    const char * get(void) const;
    void append(const String &obj);
    int compare(const String &obj);
    void assign(const String &obj);
};

String::String() {
    str = static_cast<char *>(calloc(1, sizeof *str));
};

String::String(char c) {
    str = static_cast<char *>(calloc(2, sizeof *str));
    str[0] = c;
    str[1] = '\0';
};

String::String(const char *s) {
    str = static_cast<char *>(calloc((strlen(s) + 1), sizeof *str));
    strcpy(str,s);
};

String::String(const String &obj) {
    const char *s = obj.get();
    str = static_cast<char *>(calloc((strlen(s) + 1), sizeof *str));
    strcpy(str,s);
};

String::~String()
{
    free(str);
}

const char *String::get(void) const {
    return str;
}

void String::append(const String &obj) {
    const char *s = obj.get();
    str = static_cast<char *>(realloc(str, strlen(str)+strlen(s)+1));
    strcat(str, s);
}

int String::compare(const String &obj) {
    const char *s = obj.get();
    return strcmp(str, s);
}

void String::assign(const String &obj) {
    free(str);
    const char *s = obj.get();
    str = static_cast<char *>(calloc((strlen(s) + 1), sizeof *str));
    strcpy(str, s);
}