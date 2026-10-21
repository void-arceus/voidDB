#include "../include/db/database.hpp"

#include <ctime>
#include <iostream>
#include <stdexcept>

memTable *Table = new memTable();

void setData(std::string &key, std::string &value) {
    if (key == "") {
        std::cout << "key not provided\n";
        return;
    }
    if (value == "") {
        std::cout << "value not provided\n";
        return;
    }
    std::vector<memTableEntry *> &entries = Table->entries;
    for (auto &entry : entries) {
        if (entry->key == key) {
            entry->value = value;
            if (entry->isDeleted)
                entry->isDeleted = false;
            std::cout << "Ok\n";
            return;
        }
    }
    try {
        std::time_t currentTime = std::time(nullptr);
        std::string timeString = std::ctime(&currentTime);
        memTableEntry *newEntry = new memTableEntry(key, value, timeString, false);
        Table->entries.push_back(newEntry);
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << "\n";
    }
    std::cout << "Ok\n";
}

void getData(std::string &key) {
    std::vector<memTableEntry *> &entries = Table->entries;
    for (auto &entry : entries) {
        if (entry->key == key && entry->isDeleted == false) {
            std::cout << entry->value << "\n";
            return;
        }
    }
    std::cout << "key not found\n";
}

void deleteData(std::string &key) {
    std::vector<memTableEntry *> &entries = Table->entries;
    for (auto &entry : entries) {
        if (entry->key == key && entry->isDeleted == false) {
            entry->isDeleted = true;
            std::cout << "Ok\n";
            return;
        }
    }
    std::cout << "key not found\n";
}

void getKeys() {
    std::vector<memTableEntry *> &entries = Table->entries;
    if ((int)entries.size() == 0) {
        std::cout << "No keys found!\n";
        return;
    }
    for (auto &entry : entries) {
        if (!entry->isDeleted) {
            std::cout << entry->key << "\n";
        }
    }
}
