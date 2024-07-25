#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

int countSolFiles(const fs::path& directoryPath) {
    int count = 0;

    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".sol") {
            count++;
        }
    }

    return count;
}

int main() {
    std::string directoryPath;

    std::cout << "Enter the directory path: ";
    std::cin >> directoryPath;

    try {
        int solFileCount = countSolFiles(directoryPath);
        std::cout << "Number of .sol files: " << solFileCount << std::endl;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error accessing directory: " << e.what() << std::endl;
    }

    return 0;
}
