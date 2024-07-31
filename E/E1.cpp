#include <iostream>
#include <new>

#include <iomanip>

class ByteArray
{
public:
    ByteArray();
    ByteArray(const ByteArray& );
    ByteArray(int size_, int el_size_);
    ~ByteArray();

    void resize();
    char* get_arr() const;
    int size() const;
    void up_len();
    ByteArray & operator= (const ByteArray &);
    void clean_byte_arr();
private:
    char *arr;
    int len;
    int capacity;
    int el_size;
};

ByteArray::ByteArray() {
    arr = nullptr;
    len = 0;
    capacity = 0;
    el_size = 1;
}

ByteArray::ByteArray(int size_, int el_size_) {
    len = size_ * el_size_;
    capacity = size_ * el_size_;
    el_size = el_size_;
    if (capacity != 0) {
        arr = static_cast<char *>(operator new[] (capacity));
    } else {
        arr = nullptr;
    }
}

ByteArray::ByteArray(const ByteArray& other) {
    len = other.len;
    capacity = other.capacity;
    el_size = other.el_size;
    
    arr = new char[capacity];
    for (int i = 0; i < len; ++i) {
        arr[i] = other.arr[i];
    }
}

void ByteArray::clean_byte_arr() {
    delete [] arr;
    len = 0;
    capacity = el_size;
    arr = static_cast<char*>(operator new[] (capacity));
}

ByteArray::~ByteArray() {  
    delete[] arr;
}

char* ByteArray::get_arr() const {
    return arr;
}

int ByteArray::size() const {
    return (len / el_size);
}

void ByteArray::up_len() {
    len += el_size;
}

void ByteArray::resize() {
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

ByteArray& ByteArray::operator= (const ByteArray& other) {
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

class IntVector: private ByteArray
{
public:
    IntVector();
    void clear();
    using ByteArray::size;
    void insert(int);
    int& operator[] (int);
    const int& operator[] (int) const;
};

IntVector::IntVector(): ByteArray(0, sizeof(int)) {}

void IntVector::insert(int el) {
    resize();
    new ((reinterpret_cast<int *>(get_arr()))+size()) int(el);
    up_len();
}

int& IntVector::operator[] (int index) {
    return reinterpret_cast<int *>(get_arr())[index];
}

const int& IntVector::operator[] (int index) const {
    return reinterpret_cast<int *>(get_arr())[index]; 
}

void IntVector::clear() {
    ByteArray::~ByteArray();
}

class DoubleVector: private ByteArray
{
public:
    DoubleVector();
    using ByteArray::size;
    void insert(double);
    double& operator[] (int);
    const double& operator[] (int) const;
    void clear();
};

DoubleVector::DoubleVector(): ByteArray(0, sizeof(double)) {}

void DoubleVector::insert(double el) {
    resize();
    new ((reinterpret_cast<double *>(get_arr()))+size()) double(el);
    up_len();
}

double& DoubleVector::operator[] (int index) {
    return reinterpret_cast<double *>(get_arr())[index];
}

const double& DoubleVector::operator[] (int index) const {
    return reinterpret_cast<double *>(get_arr())[index];
}

void DoubleVector::clear() {
    ByteArray::~ByteArray();
}

class IntVectorVector: private ByteArray
{
public:
    IntVectorVector();
    IntVectorVector(const IntVectorVector&);
    ~IntVectorVector();

    using ByteArray::size;
    void insert(IntVector );
    IntVector& operator[] (int);
    const IntVector& operator[] (int) const;
    IntVectorVector& operator= (const IntVectorVector&);
    void clear_vectors();
};

IntVectorVector::IntVectorVector(): ByteArray(0, sizeof(IntVector)) {}

IntVectorVector::IntVectorVector(const IntVectorVector& other):
ByteArray(other.size(), sizeof(IntVector)) {
    for (int i = 0; i < size(); ++i) {
        new (reinterpret_cast<IntVector *>(get_arr()) + i) IntVector(other[i]);
    }
}

void IntVectorVector::clear_vectors() {
    int s = size();
    for (int i = 0; i < s; ++i) {
        reinterpret_cast<IntVector *>(get_arr())[i].clear();
    }
    ByteArray::clean_byte_arr();
}

IntVectorVector::~IntVectorVector() {
    clear_vectors();
}

IntVectorVector& IntVectorVector::operator= (const IntVectorVector& other) {
    if (this == &other) {
        return *this;
    }

    clear_vectors();
    ByteArray::clean_byte_arr();
    for (int i = 0; i < other.size(); ++i) {
        insert(other[i]);
    }
    
    return *this;
}

void IntVectorVector::insert(IntVector other) {
    resize();
    new (reinterpret_cast<IntVector*>(get_arr())+size()) IntVector(other);
    up_len();
}

IntVector& IntVectorVector::operator[] (int index){
    return reinterpret_cast<IntVector*>(get_arr())[index];
}

const IntVector& IntVectorVector::operator[] (int index) const {
    return reinterpret_cast<IntVector*>(get_arr())[index];
}

// int 
// main() 
// {
//     IntVector v1;
//     v1.insert(1);
//     v1.insert(2);

//     IntVector v2(v1);
//     v2.insert(5);
//     v2.insert(6);

//     for(int i=0; i<v1.size(); ++i) {
//         std::cout << v1[i] << ' ';
//     }

//     std::cout << std::endl;

//     for(int i=0; i<v2.size(); ++i) {
//         std::cout << v2[i] << ' ';
//     }

//     std::cout << std::endl;

//     IntVectorVector m;
//     std::cout << "-------" << std::endl;
//     m.insert(v1);
//     m[0][0] = 30;
//     m.insert(IntVector());
//     m.insert(IntVector());
//     m.insert(v1);

//     IntVectorVector k(m);
//     k.insert(v1);
//     m = k;
    
//     std::cout << m.size() << std::endl;
//     for(int i=0; i<m.size(); ++i) {
//         for(int j=0; j<m[i].size(); ++j) {
//             std::cout << m[i][j] << ' ';
//         }
//     }

//     std::cout << std::endl;

//     std::cout << k.size() << std::endl;
//     for(int i=0; i<k.size(); ++i) {
//         for(int j=0; j<k[i].size(); ++j) {
//             std::cout << k[i][j] << ' ';
//         }
//     }

//     std::cout << std::endl;
// }