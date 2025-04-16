#include <iostream>

class Complex {
public:
	Complex() : m_rel{0}, m_im{0} {}

	Complex(float rel, float im) : m_rel{rel}, m_im{im} {
	}

	float rel() const { return m_rel; }
	float im() const { return m_im; }

	Complex sum(Complex rhs) const {
		Complex result{
			m_rel + rhs.m_rel,
			m_im + rhs.m_im};
		return result;
	}

private:
	float m_rel;
	float m_im;
};

int main() {
	Complex complex;
	complex.rel();
	complex.im();

	float rel, im;
	std::cout << "Enter the first complex number in the format: [real part] [image part]" << std::endl;
	std::cin >> rel >> im;

	Complex first{rel, im};
	// first.rel = 5;
	// first.im = 42;

	std::cout << "Enter the second complex number in the format: [real part] [image part]" << std::endl;
	std::cin >> rel >> im;
	Complex second{rel, im};

	Complex result = first.sum(second);

	std::cout << "The result: " << result.rel() << " + " << result.im() << "i" << std::endl;

	return 0;
}