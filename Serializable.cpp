#pragma once
#include "Serializable.h"
#include <fstream>
#include <iostream>

bool Serializable::saveJSON(const std::string& filename) const {
    std::ofstream ofs(filename);
    if (!ofs.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << "\n";
        return false;
    }
    ofs << toJson().dump(4);
    return true;
}

bool Serializable::loadJSON(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        std::cerr << "Failed to open file for reading: " << filename << "\n";
        return false;
    }
    json j;
    try {
        ifs >> j;
        fromJson(j);
    }
    catch (const std::exception& e) {
        std::cerr << "Error parsing JSON: " << e.what() << "\n";
        return false;
    }
    return true;
}