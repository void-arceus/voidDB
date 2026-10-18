/*
  author: void_arceus
*/

#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

std::unordered_map<std::string, std::string> data;
std::set<std::string> methods = {"set",    "get",  "delete",
                                 "--help", "exit", "keys"};

void displayHelp() {
  std::cout << "You've reached the help center. Be Patient!\n";
}

void getAllKeys() {
  if (data.empty()) {
    std::cout << "No keys found\n";
    return;
  }
  for (auto &[key, value] : data) {
    std::cout << key << "\n";
  }
}

void setData(std::string &key, std::string &value) {
  if (key == "" || value == "") {
    std::cout << "Cannot add empty key or value\n";
    return;
  }
  data[key] = value;
  std::cout << "OK\n";
}

void getData(std::string &key) {
  if (key == "") {
    std::cout << "key cannot be empty!\n";
    return;
  }
  if (!data.count(key)) {
    std::cout << "key doesn't exist!\n";
    return;
  }
  std::cout << data[key] << "\n";
}

void deleteData(std::string &key) {
  if (!data.count(key)) {
    std::cout << "key doesn't exist!\n";
    return;
  }
  data.erase(key);
  std::cout << "Ok\n";
}

void handleInput(bool &flag) {
  std::string inputBuffer;

  if (!std::getline(std::cin, inputBuffer)) {
    if (std::cin.eof()) {
      flag = true;
      return;
    }
  }

  std::istringstream input(inputBuffer);
  std::vector<std::string> inputStream;
  std::string currWord;
  char ch;
  while (input.get(ch)) {
    if ((int)inputStream.size() == 2) {
      currWord += ch;
      continue;
    }
    if (ch == ' ') {
      inputStream.push_back(currWord);
      currWord = "";
    } else {
      currWord += ch;
    }
  }

  // remove white spaces from front and back of the input
  int start = 0, end = (int)currWord.size() - 1;
  if (start == end && (currWord[start] == ' ' || currWord[start] == '\t')) {
    std::cout << "Invalid or missing value\n";
    return;
  }

  while ((start <= end) && (currWord[start] == ' ' || currWord[start] == '\t'))
    ++start;
  while ((start <= end) && (currWord[end] == ' ' || currWord[end] == '\t'))
    --end;

  if (start > end) {
    std::cout << "Invalid or missing value\n";
    return;
  }
  inputStream.push_back(currWord);

  int streamSize = (int)inputStream.size();
  if (streamSize == 0)
    return;

  std::string method = inputStream[0];

  if (!methods.count(method)) {
    std::cout << "Invalid method\n";
    return;
  }

  if (streamSize == 1) {
    if (method == "exit") {
      flag = true;
    } else if (method == "--help") {
      displayHelp();
    } else if (method == "keys") {
      getAllKeys();
    } else {
      std::cout << "Invalid method\n";
    }
    return;
  }

  if (method == "set") {
    if (streamSize != 3) {
      std::cout << "Missing key or value\n";
      return;
    }
    setData(inputStream[1], inputStream[2]);
  } else if (method == "get" || method == "delete") {
    if (streamSize == 1) {
      std::cout << "key not provided\n";
      return;
    }
    if (streamSize > 2) {
      std::cout << "too many arguments\n";
      return;
    }
    if (method == "get")
      getData(inputStream[1]);
    else {
      deleteData(inputStream[1]);
    }
  }
}

int main() {
  while (true) {
    std::cout << "-> ";
    bool flag = false;
    handleInput(flag);
    if (flag)
      break;
  }
  return 0;
}
