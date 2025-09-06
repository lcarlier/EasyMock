#pragma once

#include <string>

class Database {
public:
    bool connect(std::string path);
    int fetchData(std::string id);
};