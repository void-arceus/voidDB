#include "../include/db/database.hpp"

#include <iostream>

memTable table;

void setData(std::string key, std::string value) {
  if (key == "") {
    std::cout << "key not provided\n";
    return;
  }
  if (value == "") {
    std::cout << "value not provided\n";
    return;
  }
}

void getData(std::string &key) {}

void deleteData(std::string &key) {}

void getKeys() {}
