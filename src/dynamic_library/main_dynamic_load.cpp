#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __linux__
#include <dlfcn.h>
#endif

typedef int (*f_ptr)(int, int);

// main - 10 MB
// sumLib.dll - 300 MB
// Boost
void windows_example() {
	// 10 MB
#ifdef _WIN32
	HINSTANCE hDLL = ::LoadLibrary("sumLib.dll"); // 310 MB
	if (!hDLL) {
		std::cout << "Could not load the dynamic library" << std::endl;
		return;
	}

	f_ptr sumPtr = (f_ptr)::GetProcAddress(hDLL, "?sum@library@@YAHHH@Z");
	if (!sumPtr) {
		std::cout << "could not locate the function" << std::endl;
		return;
	}

	int result = sumPtr(1, 2);
	std::cout << "result = " << result << std::endl;

	::FreeLibrary(hDLL);
#endif
	// 10 MB
}

void linux_example() {
#ifdef __linux__ 
	void *hLibrary;
	hLibrary = dlopen("libSumLib.so", RTLD_LAZY);

	f_ptr sumPtr = (f_ptr)dlsym(hLibrary, "_ZN7library3sumEii");

	int result = sumPtr(1, 2);
	std::cout << "result = " << result << std::endl;

	dlclose(hLibrary);
#endif
}

int main() {

	windows_example();
	linux_example();

	return 0;
}