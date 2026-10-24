#pragma once

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

void setData(const std::string &key, const std::string &value, bool loadingData);
void getData(const std::string &key);
void deleteData(const std::string &key, bool loadingData);
void loadData(std::vector<std::string> &inputBuffer);
void getKeys();

#endif
