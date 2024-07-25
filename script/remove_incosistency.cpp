#include <iostream>
#include <filesystem>
#include <cstdlib>
#include <string>

using namespace std;
namespace fs = filesystem;

void compileSolFiles(const string& folderPath) {
    int totalFiles = 0;
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.path().extension() == ".sol") {
            totalFiles++;
        }
    }

    int currentFile = 0;
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.path().extension() == ".sol") {
            currentFile++;
            string filePath = entry.path().string();
            string compileCommand = "solc --bin " + filePath + " 2> /dev/null";

            // Execute the compile command and get the return status
            int result = system(compileCommand.c_str());

            // Check if there was an error during compilation
            if (result != 0) {
                cout << "Compilation error in " << entry.path().filename() << endl;

                // Delete the file with compilation error
                fs::remove(filePath);
                cout << "Deleted " << entry.path().filename() << endl;
            } else {
                cout << "Successfully compiled " << entry.path().filename() << endl;
            }

            // Show progress
            cout << "Visited: " << currentFile << "/" << totalFiles << endl;
        }
    }
}

int main() {
    string folderPath;
    cout << "Enter the path to the folder containing .sol files: "<<endl;
    cin >> folderPath;

    compileSolFiles(folderPath);

    return 0;
}