#include <filesystem>
#include <fstream>
#include <iostream>

/**
    Note: 
    use next compile option to compile:
    -lstdc++fs
**/

int main() {

    // 1.
    const std::filesystem::path currentDir = std::filesystem::current_path();
    std::cout << currentDir << std::endl;

    // 2.
    const std::filesystem::path someFile = currentDir / ".." / "readme.txt";
    std::cout << someFile << std::endl;
    
    const std::filesystem::path otherFile = currentDir / "otherFolder\\otherFile.txt";
    std::cout << otherFile << std::endl;
    
    // 3.
    for (auto const & entry : std::filesystem::directory_iterator(currentDir))
    {
        auto filename = entry.path().filename();
        std::cout << filename << std::endl;
    }

    // 4. parent folder
    std::cout << otherFile.parent_path() << std::endl;
    // filename with extenstion
    std::cout << otherFile.filename() << std::endl;
    // filename only
    std::cout << otherFile.stem() << std::endl;
    // extension
    std::cout << otherFile.extension() << std::endl;    

    // 5.
    const std::filesystem::path folder = currentDir / "folder";
    std::cout << "First exists: " << std::filesystem::exists(folder) << std::endl;
    try {
        std::filesystem::create_directories(folder);
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        std::cout << "Exception! " << e.what() << std::endl;
    }
    std::cout << "Second exists: " << std::filesystem::exists(folder) << std::endl;

    // 6.
    const std::filesystem::path wrongFolder = "SuperDir"; //"filedublicate"; //"SuperDir";
    std::error_code errCode;
    bool result = std::filesystem::create_directories(wrongFolder, errCode);
    if (errCode) {
        std::cout << "Creation failed! " << errCode.value() << std::endl;
    }
    std::cout << "errCode = " << errCode.value() << std::endl;
    std::cout << "result  = " << result << std::endl;

    // 7.
    const std::filesystem::path file = folder / "file.txt";
    {
        std::ofstream stream(file.native());
        if (!stream.is_open()) {
            std::cout << "Failed to create file: " << file << std::endl;
        }
        else {
            stream << "Hello, World!" << std::endl;
        }
    }
    auto last_write_time = std::filesystem::last_write_time(file);

    // 8
    // std::filesystem::remove(file);
    // std::cout << "File exists after remove: " << std::filesystem::exists(file) << std::endl;

    return 0;
}
