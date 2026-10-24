#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../include/db/database.hpp"
#include "../include/wal.hpp"

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

void getWalEntries() {
    std::fstream fs(filePath, std::ios::in);

    if (fs.is_open()) {
        fs.close();
    } else {
        std::cerr << "Error: Could not open the file." << std::endl;
    }
}

void writeToMemtable() {
    std::fstream fs(filePath, std::ios::in);
    std::vector<std::vector<std::string>> inputBuffer{};

    if (fs.is_open()) {
        std::string line;
        while (getline(fs, line)) {
            std::string word = "";
            std::vector<std::string> v{};
            for (char &c : line) {
                if (c == '-') {
                    v.push_back(word);
                    word = "";
                } else {
                    word += c;
                }
            }
            if (word != "")
                v.push_back(word);
            inputBuffer.push_back(v);
        }
        fs.close();
    } else {
        std::cerr << "Error: couldn't open the file!" << std::endl;
    }

    for (std::vector<std::string> &input : inputBuffer) {
        if ((int)input.size() < 3 || (int)input.size() > 4)
            continue;
        bool isValid = (input[(int)input.size() - 1] == "1" ? true : false);
        if (isValid) {
            loadData(input);
        }
    }
}

void writeToWAL(const std::string &method, const std::string &key, const std::string &value, bool updateStatus) {
    //..
    addRow(method, key, value, updateStatus);
}
