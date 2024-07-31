class UniquePtr
{
public:
    UniquePtr();
    UniquePtr(UniquePtr &) = delete;
    ~UniquePtr();
    const char & get(int) const;
    char & get(int);
    static UniquePtr make(int);
private:
    UniquePtr(int);
    char * ptr;
    int size;  
};

UniquePtr::UniquePtr() {
    size = 0;
    ptr = 0;
}

UniquePtr::UniquePtr(UniquePtr &obj) {
    ptr = obj.ptr;
    obj.ptr = nullptr;
    size = obj.size;
    obj.size = 0;
}

UniquePtr::~UniquePtr() {
    delete []ptr;
}

const char & UniquePtr::get(int offset) const {
    return ptr[offset];
}

char & UniquePtr::get(int offset)  {
    return ptr[offset];
}

UniquePtr::UniquePtr(int s) {
    size = s;
    ptr = new char[s];
}

UniquePtr UniquePtr::make(int s) {
    UniquePtr obj(s);
    return obj;
}

int main(int argc, char const *argv[])
{
    return 0;
}
