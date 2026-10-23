#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../include/db/database.hpp"

void getHelp() { std::cout << "Will display methods and their usage here...\n"; }

void handleInput(bool &flag) {
    std::string inputBuffer;

    if (!std::getline(std::cin, inputBuffer)) {
        if (std::cin.eof()) {
            flag = false;
            return;
        }
    }

    std::istringstream input(inputBuffer);
    std::vector<std::string> inputStream;
    char ch;
    std::string currWord = "";
    while (input.get(ch)) {
        if ((int)inputStream.size() == 2) {
            currWord += ch;
            continue;
        }
        if (ch == ' ' && currWord != "") {
            inputStream.push_back(currWord);
            currWord = "";
        } else if (ch != ' ') {
            currWord += ch;
        }
    }

    int i = 0;
    while (i < (int)currWord.size() && (currWord[i] == ' ' || currWord[i] == '\t'))
        ++i;

    if (i < (int)currWord.size())
        inputStream.push_back(currWord);

    int streamSize = (int)inputStream.size();
    if (streamSize == 0) {
        return;
    }

    if (streamSize > 3) {
        std::cout << "too many arguments\n";
        return;
    }

    std::string method = inputStream[0];
    if (!methods.count(method)) {
        std::cout << "invalid method\n";
        return;
    }

    if (streamSize == 1) {
        if (method == "--help") {
            getHelp();
        } else if (method == "exit") {
            flag = false;
        } else if (method == "keys") {
            getKeys();
        }
        return;
    }

    std::string key = inputStream[1];
    if (key == "") {
        std::cout << "error: key cannot be empty string\n";
        return;
    }

    if (streamSize == 2) {
        if (method == "get") {
            getData(key);
        } else if (method == "delete") {
            deleteData(key);
        } else if (method == "set") {
            std::cout << "error: value not provided\n";
        }
        return;
    }

    if (streamSize == 3) {
        std::string value = inputStream[2];
        if (value == "") {
            std::cout << "error: value cannot be empty\n";
            return;
        }
        if (method == "set") {
            setData(key, value);
        }
    }
}

void input() {
    bool flag = true;
    while (flag) {
        handleInput(flag);
    }
}
