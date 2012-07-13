void blub()
{
        MyClass obj;
        MyClass2 obj2;
        MyClass3 * obj3 = new MyClass3();
        throw std::runtime_error("kat cilled");
        MyClass4 obj4;
}

try{
    MyClass1 obj1;
    blub();
} catch(...) {
}

    
    MyClass1::MyClass1()
    MyClass::MyClass()
    MyClass2::MyClass2()
    MyClass3::MyClass3()
    std::runtime_error(std::string)
    MyClass2::~MyClass2()
    MyClass::~MyClass()
    MyClass1::~MyClass1()
