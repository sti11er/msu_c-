#include <iostream>

namespace containers
{
    class DynArray {
    public:
        DynArray();
        DynArray(const DynArray &);
        ~DynArray();

        void resize();
        int size() const;
        int& operator[] (int);
        const int & operator[] (int) const;
        int* get_last() const;
        DynArray & operator= (const DynArray &);

        class Iterator 
        {
        public:
            int& operator* ();
            bool operator!= (Iterator);
            Iterator& operator++ ();
            Iterator(int*);
        private:
            int *ptr;
        };

        Iterator begin_iterator();
        Iterator end_iterator();
    private:
        int *arr;
        int len;
        int capacity;
    };

    DynArray::Iterator::Iterator(int* arr_): ptr(arr_){}

    int& DynArray::Iterator::operator*() {
        return *ptr;
    }

    bool DynArray::Iterator::operator!= (DynArray::Iterator other) {
        return ptr != other.ptr;
    }

    DynArray::Iterator& DynArray::Iterator::operator++ () {
        ++ptr;
        return *this;
    }

    DynArray::Iterator DynArray::begin_iterator() {
        return DynArray::Iterator(arr);
    }

    DynArray::Iterator DynArray::end_iterator() {
        return DynArray::Iterator(arr+len);
    }

    DynArray::DynArray(): 
    arr(nullptr), len(0), capacity(0) {}

    DynArray::DynArray(const DynArray & x) {
        len = x.len;
        capacity = x.capacity;
        if (len > 0) {
            arr = new int[capacity];
            for (int i = 0; i < len; ++i) {
                arr[i] = x.arr[i];
            }
        }
    }

    DynArray::~DynArray() {   
        delete [] arr;
    }

    void DynArray::resize() {
        if (len >= capacity) {
            capacity == 0 ? capacity = 100 : capacity *= 2;
            int *tmp = new int[capacity];
            for (int i = 0; i < len; ++i) {
                tmp[i] = arr[i];
            }
            delete[] arr;
            arr = tmp;
        }
        len++;
    }

    DynArray &
    DynArray::operator= (const DynArray & x) {
        if (&x == this) {
            return *this;
        }
        len = x.len;
        capacity = x.capacity;
        if (x.arr != nullptr) {
            delete[] arr;
            arr = new int[x.capacity];
            for (int i = 0; i < len; ++i) {
                arr[i] = x.arr[i];
            }
        }
        else {
            arr = nullptr;
        }
        return *this;
    }

    int DynArray::size() const {
        return len;
    }

    int& DynArray::operator[] (int index) {
        return arr[index];
    }
    
    const int & DynArray::operator[] (int index) const {
        return arr[index];
    }

    int* DynArray::get_last() const {
        return arr + (len-1);
    }
}

namespace iterators 
{
    class InserterIterator
    {
    public:
        InserterIterator(containers::DynArray&);

        int& operator* () const;
        InserterIterator operator++ (int);
    private:
        containers::DynArray *array;
    };

    InserterIterator::InserterIterator(containers::DynArray& arr_): array(&arr_) {}

    int& InserterIterator::operator* () const {
        return *(array->get_last());
    }
    
    InserterIterator
    InserterIterator::operator++ (int) {
        InserterIterator tmp = *this;

        array->resize();
        
        return tmp;
    }


    class InputIterator 
    {
    public:
        InputIterator();
        InputIterator(std::istream &);

        int& operator * ();
        InputIterator operator++ (int);
        bool operator!= (const InputIterator &) const;
    private:
        std::istream *stream;
        int val;
    };

    InputIterator:: InputIterator() {
        stream = nullptr;
    }

    InputIterator:: InputIterator(std::istream & cin) {
        stream = &cin;
        if (!(*stream >> val)) {
            stream = nullptr;
        }
    }

    int& InputIterator::operator* () {
        return val;
    }

    InputIterator InputIterator::operator++ (int) {
        InputIterator tmp(*this);
        if (!(*stream >> val)) {
            stream = nullptr;
        }
        return tmp;
    }

    bool InputIterator::operator!= (const InputIterator &other) const {
        return stream != other.stream;
    }
}

namespace algorithms
{
    iterators::InserterIterator
    copy(
        iterators::InputIterator iterator,
        iterators::InputIterator end,
        iterators::InserterIterator begin2)
    {
        iterators::InserterIterator iterator2 = begin2;
        while (iterator != end) {
            *iterator2++ = *iterator++;
        }
        return iterator2;
    }

    class IsEven {
    public:
        IsEven(bool);
        bool operator() (const int&);
    private:
        int is_even;
    };

    IsEven::IsEven(bool type): is_even(type) {}

    bool IsEven::operator() (const int& el) {
        return (el % 2 == !is_even) ? 1 : 0;
    }

    class AddTo {
    public:
        AddTo(int &);
        void operator() (const int&);
    private:
        int& res_sum;
    };

    AddTo::AddTo(int& res): res_sum(res) {}

    void AddTo::operator() (const int& el) {
        res_sum += el;
    }
}

// int
// main()
// {
//     containers::DynArray a;
//     algorithms::copy(
//         iterators::InputIterator(std::cin),
//         iterators::InputIterator(),
//         iterators::InserterIterator(a));

//     int even_summ = 0, odd_summ = 0;

//     algorithms::foreach_if(
//         a.begin_iterator(),
//         a.end_iterator(),
//         algorithms::IsEven(true),
//         algorithms::AddTo(even_summ));
//     algorithms::foreach_if(
//         a.begin_iterator(),
//         a.end_iterator(),
//         algorithms::IsEven(false),
//         algorithms::AddTo(odd_summ));

//     std::cout << even_summ << std::endl;
//     std::cout << odd_summ << std::endl;
// }