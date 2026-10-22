#include <fstream>
#include <iostream>
#include <string>

inline const std::string filePath = "../data/wal.txt";

void writeRow(std::string &method, std::string &key, std::string &value) {
    if (method != "set" && method != "delete") {
        std::cerr << "WAL Error: method not allowed to write in WAL." << std::endl;
        return;
    }
    if (method == "set" && value == "") {
        std::cerr << "WAL Error: value not provided." << std::endl;
        return;
    }
    if (key == "") {
        std::cerr << "WAL Error: key not provided." << std::endl;
        return;
    }

    std::fstream fs(filePath, std::ios::app);
    if (fs.is_open()) {
        if (fs.eof()) {
            fs << "\n";
        }
        fs << method + "-";
        fs << key + (method == "set" ? "-" : "\n");
        if (method == "set") {
            fs << value + "\n";
        }
        if (fs.fail()) {
            std::cerr << "Error: failed to write the WAL." << std::endl;
            return;
        }
        fs.close();
        if (fs.fail()) {
            std::cerr << "Error: something went wrong." << std::endl;
            return;
        }
        std::cout << "entry added to the WAL successfully\n";
    } else {
        std::cerr << "WAL Error: Could not open the file." << std::endl;
    }
}

void getWalEntries() { std::fstream fs(filePath, std::ios::in); }

void writeToWAL() {
    std::string method = "set", key = "hobby", value = "coding";
    writeRow(method, key, value);
}
