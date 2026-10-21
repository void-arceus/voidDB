#ifndef DATABASE_H
#define DATABASE_H

#include <set>
#include <string>
#include <vector>

struct memTableEntry {
    std::string key;
    std::string value;
    std::string timeStamp;
    bool isDeleted;
    memTableEntry(std::string key, std::string value, std::string timeStamp, bool isDeleted) : key(key), value(value), timeStamp(timeStamp), isDeleted(isDeleted) {};
};

struct memTable {
    std::vector<memTableEntry *> entries;
    int size;
    memTable() : size(0) {};
};

inline const std::set<std::string> methods = {"set", "get", "delete", "keys", "--help", "exit"};

void setData(std::string &key, std::string &value);
void getData(std::string &key);
void deleteData(std::string &key);
void getKeys();

#endif
