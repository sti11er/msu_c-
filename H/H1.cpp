#include <iostream>
#include <new>

#include <iomanip>

class Allocate
{
public:
    Allocate();
    Allocate(const Allocate& );
    Allocate(int size_, int el_size_);
    ~Allocate();

    void resize();
    char* get_arr() const;
    int size() const;
    void up_len();
    Allocate & operator= (const Allocate &);
    void clean_byte_arr();
private:
    char *arr;
    int len;
    int capacity;
    int el_size;
};

Allocate::Allocate() {
    arr = nullptr;
    len = 0;
    capacity = 0;
    el_size = 1;
}

Allocate::Allocate(int size_, int el_size_) {
    len = size_ * el_size_;
    capacity = size_ * el_size_;
    el_size = el_size_;
    if (capacity != 0) {
        arr = static_cast<char *>(operator new[] (capacity));
    } else {
        arr = nullptr;
    }
}

Allocate::Allocate(const Allocate& other) {
    len = other.len;
    capacity = other.capacity;
    el_size = other.el_size;
    
    arr = new char[capacity];
    for (int i = 0; i < len; ++i) {
        arr[i] = other.arr[i];
    }
}

void Allocate::clean_byte_arr() {
    delete [] arr;
    len = 0;
    capacity = el_size;
    arr = static_cast<char*>(operator new[] (capacity));
}

Allocate::~Allocate() {  
    delete[] arr;
}

char* Allocate::get_arr() const {
    return arr;
}

int Allocate::size() const {
    return (len / el_size);
}

void Allocate::up_len() {
    len += el_size;
}

void Allocate::resize() {
    if (len + el_size >= capacity) {
        capacity == 0 ? capacity = el_size : capacity *= 2;
        char *tmp = new char[capacity];
        for (int i = 0; i < len; ++i) {
            tmp[i] = arr[i];
        }
        delete[] arr;
        arr = tmp;
    }
}

Allocate& Allocate::operator= (const Allocate& other) {
    if (&other == this) {
        return *this;
    }

    len = other.len;
    capacity = other.capacity;
    el_size = other.el_size;
    if (other.arr != nullptr) {
        delete[] arr;
        arr = new char[capacity];
        for (int i = 0; i < len; ++i) {
            arr[i] = other.arr[i];
        }
    }
    else {
        arr = nullptr;
    }

    return *this;
}

template <typename T>
class Vector: private Allocate
{
public:
    Vector();
    Vector(const Vector&);
    ~Vector();

    using Allocate::size;
    void insert(T);
    T& operator[] (int);
    const T& operator[] (int) const;
    Vector& operator= (const Vector&);
    void clear();
};

template <typename T>
void Vector<T>::clear() {
    int s = size();
    for (int i = 0; i < s; ++i) {
        reinterpret_cast<T *>(get_arr())[i].~T();
    }
    Allocate::clean_byte_arr();
}

template <typename T>
Vector<T>::Vector(): Allocate(0, sizeof(T)) {}

template <typename T>
Vector<T>::Vector(const Vector& other): Allocate(other.size(), sizeof(T)) {
    for (int i = 0; i < size(); ++i) {
        new (reinterpret_cast<T *>(get_arr()) + i) T(other[i]);
    }
}

template <typename T>
Vector<T>::~Vector() {
    clear();
}

template <typename T>
void Vector<T>::insert(T t) {
    resize();
    new (reinterpret_cast<T*>(get_arr())+size()) T(t);
    up_len();
}

template <typename T>
T& Vector<T>::operator[] (int index) {
    return reinterpret_cast<T*>(get_arr())[index];
}

template <typename T>
const T& Vector<T>::operator[] (int index) const {
    return reinterpret_cast<T*>(get_arr())[index];
}

template <typename T>
Vector<T>& Vector<T>::operator= (const Vector<T>& other) {
    if (this == &other) {
        return *this;
    }

    clear();
    Allocate::clean_byte_arr();
    for (int i = 0; i < other.size(); ++i) {
        insert(other[i]);
    }
    
    return *this;
}