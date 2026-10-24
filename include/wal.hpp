#pragma once

#ifndef WAL_H
#define WAL_H

#include <string>

void writeToWAL(const std::string &method, const std::string &key, const std::string &value, bool updateStatus);
void writeToMemtable();

#endif
