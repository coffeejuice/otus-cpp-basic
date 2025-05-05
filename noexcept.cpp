#include "tracer.hpp"

#include <string>
#include <vector>

void func() noexcept {

}

struct Some {
	void func() noexcept {}
};

int main() {

	std::vector<Tracer> tracers;
	for(int i = 0; i < 10; ++i) {
		std::cout << "*** append [" << i << "] element:" << std::endl;
		tracers.emplace_back( Tracer{std::to_string(i)} );
	}

	Tracer array[2] = { /*1*/ /*2*/  };

	return 0;
}

// Exception safety
// - no
// - basic
// - strong
// - no exception

// 1. Tracer tr3;
// tr3 = 3;

// 2. new (array[3]) Tracer{"3"};