#include <iostream>
#include <new>

class DynArray {
public:
    DynArray(int c = 0, int summ2 = 1);
    DynArray(const DynArray&);
    ~DynArray();
    char * increase();
    DynArray & operator = (const DynArray &);
private:
    char * array;
    int summ;
    int capacity;
public:
    char * getter() const;
    int size() const;
    void clean_memory();
    void inc_after_use();
    int e_size;
};

DynArray::DynArray(int c, int summ2) {
    if (summ2 != 1) {
        summ = summ2 * c;
    }
    else {
        summ = 0;
    }
    e_size = c; 
    capacity = summ2 * e_size;
    array = static_cast<char*>(operator new[] (capacity * sizeof (char)));
    for (int i = 0; i < capacity; ++i) {
        new(array + i) char;
    }
}

DynArray::DynArray(const DynArray & x) {
    summ = x.summ;
    capacity = x.capacity;
    e_size = x.e_size;
    array = static_cast<char*>(operator new[] (capacity * sizeof (char)));
    for (int i = 0; i < capacity; ++i) {
        new(array + i) char;
    }
    for (int i = 0; i < summ; ++i) {
        array[i] = x.array[i];
    }
}

DynArray::~DynArray() {
    delete [] array;
}

char *
DynArray::increase() {
    while (capacity <= e_size + summ) {
        capacity *= 2;
        char * buf = static_cast<char*>(operator new[] (capacity * sizeof (char)));
        for (int i = 0; i < capacity; ++i) {
            new(buf + i) char;
        }
        for (int i = 0; i < summ; ++i) {
            buf[i] = array[i];
        }
        delete [] array;
        array = buf;
    }
    //not increase summ, that summ need as old value
    return array;
}

char *
DynArray::getter() const {
    return array;
}

DynArray & 
DynArray::operator = (const DynArray & x) {
    if (&x == this) {
        return *this;
    }
    summ = x.summ;
    capacity = x.capacity;
    e_size = x.e_size;
    delete [] array;
    arr = new int[capacity];
    for (int i = 0; i < summ; ++i) {
        array[i] = x.array[i];
    }
    return *this;
}

int 
DynArray::size() const {
    return summ / e_size;
}

void 
DynArray::inc_after_use() {
    summ += e_size;
}

void 
DynArray::clean_memory()
{
    delete [] array;
    summ = 0;
    capacity = e_size;
    array = static_cast<char*>(operator new[] (capacity * sizeof (char)));
    for (int i = 0; i < capacity; ++i) {
        new(array + i) char;
    }
}

class IntVector: private DynArray {
public:
    using DynArray::size;
    IntVector();
    void insert(int);
    int & operator[] (int);
    const int & operator[] (int) const;
};

IntVector::IntVector(): DynArray(sizeof(int)) {}

int & 
IntVector::operator[] (int n) {
    return *reinterpret_cast<int*>(getter() + n * sizeof(int));
}

const int & 
IntVector::operator[] (int n) const {
    return *reinterpret_cast<int*>(getter() + n * sizeof(int));
}

void 
IntVector::insert(int n)
{
    new (reinterpret_cast<int *>(increase() + size() * sizeof(int))) int(n);
    inc_after_use();
}

class DoubleVector: private DynArray {
public:
    using DynArray::size;
    DoubleVector();
    void insert(double);
    double & operator[] (int);
    const double & operator[] (int) const;
};

DoubleVector::DoubleVector(): DynArray(sizeof(double)) {}

double & 
DoubleVector::operator[] (int n) {
    return *reinterpret_cast<double*>(getter() + n * sizeof(double));
}

const double & 
DoubleVector::operator[] (int n) const {
    return *reinterpret_cast<double*>(getter() + n * sizeof(double));
}

void 
DoubleVector::insert(double n)
{
    new (reinterpret_cast<double *>(increase() + size() * sizeof(double))) double(n);
    inc_after_use();
}

class IntVectorVector: private DynArray {
public:
    using DynArray::size;
    IntVectorVector();
    void insert(IntVector);
    IntVector & operator[] (int);
    const IntVector & operator[] (int) const;
    IntVectorVector(const IntVectorVector&);
    ~IntVectorVector();
    IntVectorVector & operator = (const IntVectorVector &);
};

IntVectorVector::IntVectorVector(): DynArray(sizeof (IntVector)) {}

IntVector &
IntVectorVector::operator [] (int n) {
    return *reinterpret_cast<IntVector*>(getter() + n * sizeof(IntVector));
}

const IntVector &
IntVectorVector::operator [] (int n) const {
    return *reinterpret_cast<IntVector*>(getter() + n * sizeof(IntVector));
}

void 
IntVectorVector::insert(IntVector n) {
    int lim = size();
    new (reinterpret_cast<IntVector*>(increase() + lim * sizeof(IntVector))) IntVector(n);
    inc_after_use();
}

IntVectorVector::~IntVectorVector() {
    int lim = size();
    for (int i = 0; i < lim; ++i) {
        (*reinterpret_cast<IntVector*>(getter() + i * sizeof(IntVector))).~IntVector();
    }
}

IntVectorVector & 
IntVectorVector::operator = (const IntVectorVector & x)
{
    if (this == &x) {
        return *this;
    }
    int i, lim = size();;
    for (i = 0; i < lim; ++i) {
        reinterpret_cast<IntVector *>(getter())[i].~IntVector();
    }
    int lim2 = x.size();
    for (clean_memory(), i = 0; i < lim2; ++i) {
        new (reinterpret_cast<IntVector*>(increase()) + i) IntVector(*reinterpret_cast<IntVector*>(x.getter() + i * sizeof(IntVector)));
        inc_after_use();
    }
    return *this;
}

IntVectorVector::IntVectorVector(const IntVectorVector & x): DynArray(sizeof (IntVector), x.size()) {
    int lim = size();
    for (int i = 0; i < lim; ++i) {
        new (reinterpret_cast<IntVector*>(getter() + i * sizeof(IntVector))) IntVector(*reinterpret_cast<IntVector*>(x.getter() + i * sizeof(IntVector)));
    }
}

int
main()
{
    IntVector v;
    v.insert(1);
    v.insert(2);
    v.insert(3);
    v.insert(4);
    v.insert(5);
    v.insert(6);
    v.insert(7);
    v.insert(8);
    
    IntVector m(v);
    
    IntVector p;
    p = v;
    
    IntVector q;
    q = v;
    
    
    IntVectorVector k_vv;
    k_vv.insert(v);
    k_vv.insert(m);
    k_vv.insert(p);
    k_vv.insert(q);
    for (size_t i = 0; i < k_vv.size(); ++i) {
        for (size_t j = 0; j < k_vv[i].size(); ++j) {
            std::cout << k_vv[i][j] << ' ';
        }
    }
    std::cout << std::endl;
    
    IntVectorVector l_vv(k_vv);
    for (size_t i = 0; i < l_vv.size(); ++i) {
        for (size_t j = 0; j < l_vv[i].size(); ++j) {
            std::cout << l_vv[i][j] << ' ';
        }
    }
    std::cout << std::endl;
    
    
    
    IntVectorVector c_vv;
    c_vv = k_vv;
    for (size_t i = 0; i < c_vv.size(); ++i) {
        for (size_t j = 0; j < c_vv[i].size(); ++j) {
            std::cout << c_vv[i][j] << ' ';
        }
    }
    std::cout << '\n';
    
    c_vv.insert(IntVector());
    c_vv.insert(IntVector());
    
    std::cout << c_vv.size() << '\n';
    
}
