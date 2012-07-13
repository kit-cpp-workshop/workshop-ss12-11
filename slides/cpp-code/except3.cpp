class MyClass{
    int * arr;
public:
    MyClass(int size)
    {
        arr = nullptr;
        resize(size);
    }
    void resize(int size)
    {
        if(size <= 0) {
            throw std::runtime_error("invalid_size");
        }
        delete[] arr;
        arr = new int[size];
    }
};
