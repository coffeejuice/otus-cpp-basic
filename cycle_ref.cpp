#include <iostream>
#include <memory>

struct SomeStruct {
    SomeStruct() {
        std::cout << "Constructor!" << std::endl;
    }

    ~SomeStruct() {
        std::cout << "Desctructor!" << std::endl;
    }

    std::shared_ptr<SomeStruct> partner;
};

void function_with_leakage() {
    auto partnerA = std::make_shared<SomeStruct>();
    auto partnerB = std::make_shared<SomeStruct>();
    partnerA->partner = partnerB;
    partnerB->partner = partnerA;
}

class partnerA;
class partnerB;

class partnerA {
    std::shared_ptr<partnerB> partner_ptr;

  public:
    partnerA() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
    ~partnerA() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
    void setPartner(std::shared_ptr<partnerB> ptr) { partner_ptr = ptr; }
};

class partnerB {
    std::shared_ptr<partnerA> partner_ptr;

  public:
    partnerB() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
    ~partnerB() { std::cout << __PRETTY_FUNCTION__ << std::endl; }

    void setPartner(std::shared_ptr<partnerA> ptr) { partner_ptr = ptr; }
};

void cyclik_links() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    auto first  = std::make_shared<partnerA>();
    auto second = std::make_shared<partnerB>();

    first->setPartner(second); //second counter = 2
    second->setPartner(first); //first counter = 2

    //first.~shared_ptr() => counter = 1, but not destructor of partnerA will be called, second counter = 2
    //second.~shared_ptr() => counter = 1, but not destructor of partnerB will be called
}

int main() {

    cyclik_links();

    return 0;
}
