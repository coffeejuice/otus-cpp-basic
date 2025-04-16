#include <iostream>

class Base {
public:
	Base() { 
		// pure virtual function call
		doInitialize(); 
	}

	virtual ~Base() = default;

	virtual void doSomething() {};
private:
	static void doInitialize() {
		std::cout << "Base::doInitialize()" << std::endl;
		// doSomething();
	}
};

class Derived final : public Base {
public:
	Derived() = default;
	~Derived() override = default;

	void doSomething() override { 
		std::cout << "Hello from Derived!" << std::endl; 
	}
};

int main(int argc, char *argv[]) {
	Derived d;
	d.doSomething();
	return 0;
}