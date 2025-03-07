#include <fstream>
#include <iostream>

class FileManager {
private:
    std::fstream file;

public:
    FileManager(const std::string &filename) {
        file.open(filename, std::ios::out);
        if (!file) {
            std::cerr << "Failed to open file! " << filename << std::endl;
        }
    }

    ~FileManager() {
        if (file.is_open()) {
            file.close();
            std::cout << "File was closed. " << std::endl;
        }
    }

    void writeToFile(const std::string &text) {
        if (file) {
            file << text << std::endl;
        }
    }
};

int main() {
    FileManager fm("example.txt");
    fm.writeToFile("Text to write");
}
