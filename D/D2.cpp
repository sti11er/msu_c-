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
    private:
        int *arr;
        int len;
        int capacity;
    };

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

// namespace algorithms
// {
// iterators::InserterIterator
// copy(
//     iterators::InputIterator iterator,
//     iterators::InputIterator end,
//     iterators::InserterIterator begin2)
//     {
//         iterators::InserterIterator iterator2 = begin2;
//         while (iterator != end) {
//             *iterator2++ = *iterator++;
//         }
//         return iterator2;
//     }
// }

// int
// main()
// {
//     containers::DynArray a;

//     algorithms::copy(
//         iterators::InputIterator(std::cin),
//         iterators::InputIterator(),
//         iterators::InserterIterator(a));
        
//     for (int i = 0; i < a.size(); ++i) {
//         std::cout << a[i] << std::endl;
//     }
// }