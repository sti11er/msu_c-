#include <iostream>
#include <new>

class Person
{
public:
    Person(const char*, int, bool);
    const char *name() const;
    int age() const;
    bool man() const;
private:
    const char *name_;
    int age_;
    bool man_;
};

Person::Person(const char*n, int a, bool m): 
name_(n), age_(a), man_(m) {}

const char *Person::name() const {
    return name_;
}

int Person::age() const {
    return age_;
}

bool Person::man() const {
    return man_;
}

class PersonView
{
public:
    PersonView(Person *, int);
    class Iterator 
    {
    public:
        Iterator(Person*, int, int, int);
        Iterator& operator++ ();
        const Person* operator->() const;
        bool is_type_valid(const Person) const;
        friend bool operator!= (const Iterator&, const Iterator&);
    private:
        int type;
        int size;
        Person* cur;
        Person* end;
    };
protected:
    Person *persons_;
    int size_;
};

bool PersonView::Iterator::is_type_valid(const Person p) const{
    if (type == 0) {
        // men
        return p.man() == true;
    } else {
        // young
        return ((p.age() >= 18) && (p.age() <= 35));
    }
}

PersonView::Iterator::Iterator(Person*p, int t, int i, int s): 
type(t), size(s), cur(p+i), end(p+s) {
    while (cur != end) {
        if (is_type_valid(*cur)) {
            break;
        }
        ++cur;
    }
}

PersonView::Iterator& PersonView::Iterator::operator++ () {
    if (cur == end) {
        return *this;
    }

    ++cur;
    while (cur != end) {
        if (is_type_valid(*cur)) {
            break;
        }
        ++cur;
    }
    return *this;
}

const Person* PersonView::Iterator::operator->() const {
    return cur;
}

bool operator!= (const PersonView::Iterator&p1, const PersonView::Iterator&p2) {
    return p1.cur != p2.cur;
}

PersonView::PersonView(Person *p, int s): persons_(p), size_(s) {}

class MenPersonView: public PersonView
{
public:
    MenPersonView(Person *, int);
    Iterator begin();
    Iterator end();
};

MenPersonView::MenPersonView(Person *p, int s): PersonView(p, s) {}

PersonView::Iterator MenPersonView::begin() {
    return PersonView::Iterator(persons_, 0, 0, size_);
}

PersonView::Iterator MenPersonView::end() {
    return PersonView::Iterator(persons_, 0, size_, size_);
}

class YoungPersonView: public PersonView
{
public:
    YoungPersonView(Person *, int);
    Iterator begin();
    Iterator end();
};

YoungPersonView::YoungPersonView(Person *p, int s): PersonView(p, s) {}

PersonView::Iterator YoungPersonView::begin() {
    return PersonView::Iterator(persons_, 1, 0, size_);
}

PersonView::Iterator YoungPersonView::end() {
    return PersonView::Iterator(persons_, 1, size_, size_);
}

class Persons
{
public:
    Persons();
    Persons(const Persons&);
    ~Persons();
    MenPersonView men() const;
    YoungPersonView young() const;
    void add(const Person&);
private:
    int size_; // amount
    int capacity_; // amount in byte
    int el_size_ = sizeof(Person);
    Person* persons_;
};

Persons::Persons(): size_(0), capacity_(0), persons_(0) {}

Persons::Persons(const Persons& other) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    persons_ = static_cast<Person *>(operator new[] (capacity_)); 
    for (int i=0; i<size_; ++i) {
        new (persons_+i) Person(other.persons_[i]);
    }
}

Persons::~Persons() {
    delete[] persons_;
    persons_ = 0;
}

MenPersonView Persons::men() const {
    return MenPersonView(persons_, size_); 
}

YoungPersonView Persons::young() const {
    return YoungPersonView(persons_, size_); 
}

void Persons::add(const Person& obj) {  
    if (size_*el_size_ >= capacity_) {
        capacity_ == 0 ? capacity_ = el_size_ : capacity_ *= 2;
        Person* tmp = static_cast<Person *>(operator new[] (capacity_)); 
        for (int i=0; i<size_; ++i) {
            new (tmp+i) Person(persons_[i]);
        }
        delete [] persons_;
        persons_ = tmp;
    }
    persons_[size_++] = obj;
}

// int 
// main() 
// {
//     Persons org;
//     org.add(Person("Ivanov", 20, true));
//     org.add(Person("Ivanova", 30, false));
//     org.add(Person("Petrov", 50, true));
//     org.add(Person("Sidorov", 32, true));

//     std::cout << "Men:" << std::endl;
//     MenPersonView men = org.men();
//     for (MenPersonView::Iterator it = men.begin(); it != men.end(); ++it) {
//         std::cout << it->name() << std::endl;
//     }

//     std::cout << "Young:" << std::endl;
//     YoungPersonView young = org.young();
//     for (YoungPersonView::Iterator it = young.begin(); it != young.end(); ++it) {
//         std::cout << it->name() << std::endl;
//     }   
// }