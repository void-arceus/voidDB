#include "../include/db/database.hpp"
#include "../include/wal.hpp"
#include <ctime>
#include <iostream>

memTable *Table = new memTable();

void setData(const std::string &key, const std::string &value, bool loadingData) {
    std::vector<memTableEntry *> &entries = Table->entries;
    for (auto &entry : entries) {
        if (entry->key == key) {
            entry->value = value;
            if (entry->isDeleted)
                entry->isDeleted = false;
            if (!loadingData) {
                const std::string method = "set";
                writeToWAL(method, key, value, true);
                std::cout << "Ok\n";
            }
            return;
        }
    }

    try {
        std::time_t currentTime = std::time(nullptr);
        std::string timeString = std::ctime(&currentTime);
        memTableEntry *newEntry = new memTableEntry(key, value, timeString, false);
        Table->entries.push_back(newEntry);
        const std::string method = "set";
        if (!loadingData)
            writeToWAL(method, key, value, true);
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << "\n";
    }
    if (!loadingData)
        std::cout << "Ok\n";
}

void getData(const std::string &key) {
    std::vector<memTableEntry *> &entries = Table->entries;
    for (auto &entry : entries) {
        if (entry->key == key && entry->isDeleted == false) {
            std::cout << entry->value << "\n";
            return;
        }
    }
    std::cout << "key not found\n";
}

void deleteData(const std::string &key, bool loadingData) {
    std::vector<memTableEntry *> &entries = Table->entries;
    for (auto &entry : entries) {
        if (entry->key == key && entry->isDeleted == false) {
            entry->isDeleted = true;
            const std::string method = "delete", value = "";
            if (!loadingData) {
                writeToWAL(method, key, value, true);
                std::cout << "Ok\n";
            }
            return;
        }
    }
    if (!loadingData)
        std::cout << "key not found\n";
}

void getKeys() {
    std::vector<memTableEntry *> &entries = Table->entries;
    bool empty = true;
    for (auto &entry : entries) {
        if (!entry->isDeleted) {
            empty = false;
            std::cout << entry->key << "\n";
        }
    }
    if (empty)
        std::cout << "No keys found!" << std::endl;
}

void loadData(std::vector<std::string> &inputBuffer) {
    std::string method = inputBuffer[0], key = inputBuffer[1];

    if (method == "set") {
        std::string value = inputBuffer[2];
        setData(key, value, true);
    } else if (method == "delete") {
        deleteData(key, true);
    }
}
