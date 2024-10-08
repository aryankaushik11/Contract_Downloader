#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

bool isContractVulnerable(const string& output) {
    bool hasHighOrMediumIssues = false;
    size_t posMedium = output.find("Number of medium issues: ");
    size_t posHigh = output.find("Number of high issues: ");
    
    if (posMedium != string::npos) {
        int mediumIssues = stoi(output.substr(posMedium + 25, output.find("\n", posMedium) - (posMedium + 25)));
        if (mediumIssues > 0) hasHighOrMediumIssues = true;
    }
    
    if (posHigh != string::npos) {
        int highIssues = stoi(output.substr(posHigh + 23, output.find("\n", posHigh) - (posHigh + 23)));
        if (highIssues > 0) hasHighOrMediumIssues = true;
    }
    
    return hasHighOrMediumIssues;
}

int main() {
    string directory = "."; // Set the directory path here
    vector<string> contractFiles;

    // Iterate through the directory to find all .sol files
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.path().extension() == ".sol") {
            contractFiles.push_back(entry.path().string());
        }
    }

    int vulnerableCount = 0;
    int analyzedCount = 0;

    for (size_t i = 0; i < contractFiles.size(); ++i) {
        const string& file = contractFiles[i];

        string command = "slither " + file + " --print human-summary > temp_output.txt 2>&1";
        system(command.c_str());

        ifstream inputFile("temp_output.txt");
        string line, output;
        
        if (inputFile.is_open()) {
            while (getline(inputFile, line)) {
                output += line + "\n";
            }
            inputFile.close();

            if (isContractVulnerable(output)) {
                vulnerableCount++;
            }
        }

        analyzedCount++;
        cout << analyzedCount << "/" << contractFiles.size() << " files analyzed." << endl;
    }

    cout << vulnerableCount << "/" << contractFiles.size() << " are vulnerable." << endl;

    // Clean up
    fs::remove("temp_output.txt");

    return 0;
}
