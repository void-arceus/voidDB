#include "../include/wal.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

inline const std::string filePath = "../data/wal.txt";

void addRow(const std::string &method, const std::string &key, const std::string &value, bool updateStatus) {
    std::fstream fs(filePath, std::ios::app);
    if (fs.is_open()) {
        fs << method + "-";
        fs << key + "-";
        fs << (method == "set" ? value + "-" : "");
        fs << (updateStatus == true ? "1\n" : "0\n");
        fs.close();
        if (fs.fail()) {
            std::cerr << "Error: failed to write the WAL." << std::endl;
            return;
        }
    } else {
        std::cerr << "WAL Error: Could not open the file." << std::endl;
    }
}

void updateRow(const bool updateStatus) {
    // update the status of the last row
    // move to the last row
}

void getWalEntries() {
    std::vector<std::string> text;
    std::fstream fs(filePath, std::ios::in);

    if (fs.is_open()) {
        std::string line;
        while (getline(fs, line)) {
            text.push_back(line);
        }
    } else {
        std::cerr << "Error: Could not open the file." << std::endl;
    }

    for (auto &line : text)
        std::cout << line << "\n";
}

void writeToWAL(const std::string &method, const std::string &key, const std::string &value, std::string type, bool updateStatus) {
    if (type == "add") {
        addRow(method, key, value, updateStatus);
    } else if (type == "update") {
        updateRow(updateStatus);
    }
}
