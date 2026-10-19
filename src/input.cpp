#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "../include/db/database.hpp"
#include "../include/db/input.hpp"

void getHelp() {
  std::cout << "Will display methods and their usage here...\n";
}

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
  while (i < (int)currWord.size() &&
         (currWord[i] == ' ' || currWord[i] == '\t')) {
    ++i;
  }
  if (i >= (int)currWord.size()) {
    std::cout << "invalid value\n";
    return;
  }
  inputStream.push_back(currWord);
  int streamSize = (int)inputStream.size();

  if (streamSize > 3) {
    std::cout << "too many arguments\n";
    return;
  }

  std::string method = inputStream[0];
  if (!methods.count(method)) {
    std::cout << "invalid method type\n";
    return;
  }

  if (streamSize == 1) {
    if (method == "keys") {
      getKeys();
    } else if (method == "--help") {
      getHelp();
    } else if (method == "exit") {
      flag = false;
    } else {
      std::cout << "invalid method\n";
    }
    return;
  }
}

void input() {
  bool flag = true;
  while (flag) {
    handleInput(flag);
  }
}
