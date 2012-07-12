
Werfer * test = nullptr;
try{
    test = new Werfer();
    assert(test != nullptr);
} catch(...) {
    assert(test == nullptr);
}
