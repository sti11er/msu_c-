#include <iostream>
#include <exception>
#include <limits> 

template <typename T>
class Data 
{
public:
    Data(size_t capacity = 0);
    ~Data();

    void alloc();
    size_t size() const;
    void swap(Data &) noexcept;
    T& operator[] (size_t);
    const T& operator[] (size_t) const;
private:
    T* data;
    size_t capacity = 0;
};

template <typename T>
Data<T>::Data(size_t capacity_): 
    data(new T[capacity_]),
    capacity(capacity_) {
}

template <typename T>
Data<T>::~Data() {
    delete[] data;
}

template <typename T>
void Data<T>::alloc() {
    capacity = (capacity == 0) ? 1 : capacity*2;
    data = new T[capacity];
}

template<typename T>
size_t Data<T>::size() const {
    return capacity;
}

template <typename T>
T& Data<T>::operator[] (size_t i) {
    return data[i];
}

template <typename T>
const T& Data<T>::operator[] (size_t i) const {
    return data[i];
}

template <typename T>
void Data<T>::swap(Data& other) noexcept {
    T* tmp_ptr = data;
    data = other.data;
    other.data = tmp_ptr;
    
    size_t tmp = capacity;
    capacity = other.capacity;
    other.capacity = tmp;
}

template <typename T>
class Stack
{
public:
    explicit Stack(size_t capacity = 0);
    Stack(Stack const &);
    ~Stack() = default;
    Stack &operator=(Stack const &);

    void push(T const &);
    void pop(T &);
    bool empty() const noexcept;
    size_t size() const noexcept;
private:
    void swap(Stack &) noexcept;

    Data<T> stack;
    size_t max_size;
    size_t curr_size;
};

template <typename T>
void Stack<T>::swap(Stack& other) noexcept {
    stack.swap(other.stack);

    size_t tmp = max_size;
    max_size = other.max_size;
    other.max_size = tmp;

    tmp = curr_size;
    curr_size = other.curr_size;
    other.curr_size = tmp;
}

template <typename T>
Stack<T>::Stack(size_t capacity): 
    stack(capacity),
    max_size(capacity),
    curr_size(0) {
}

template <typename T>
Stack<T>::Stack(const Stack& other){
    Stack tmp(other.max_size);   
    tmp.curr_size = other.curr_size;  

    for (size_t i=0; i<tmp.curr_size; ++i) {            
        tmp.stack[i] = other.stack[i];
    }
    swap(tmp);
}

template <typename T>
Stack<T>& Stack<T>::operator= (const Stack& other) {
    if (&other == this) {
        return *this;
    }
    
    Stack tmp(other);
    swap(tmp);

    return *this;
}

template <typename T>
void Stack<T>::push(T const &data) {
    if (curr_size == max_size) {
        Stack tmp(*this);
        tmp.stack.alloc();
        tmp.max_size = tmp.stack.size();

        for (size_t i = 0; i < curr_size; ++i) {
            tmp.stack[i] = stack[i];
        }
        swap(tmp);
    }

    stack[curr_size] = data;
    curr_size++;
}

template <typename T>
void Stack<T>::pop(T &res) {
    if (curr_size == 0) {
        throw std::exception();
    }

    res = stack[curr_size-1];
    --curr_size;
}

template <typename T>
bool Stack<T>::empty() const noexcept {
    return curr_size == 0;
}

template <typename T>
size_t Stack<T>::size() const noexcept {
    return curr_size;
}