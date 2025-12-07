#include "SortData.h"
#include "Globals.h"
#include <chrono>
#include <sstream>
#include <iomanip>

SortData::SortData() {
    std::string arrayFolderPath = (ARRAY_FOLDER).string();
    if (!fs::exists(arrayFolderPath)) {
        fs::create_directories(arrayFolderPath);
    }
}

SortData::SortData(const SortableArray& first, const SortableArray& second, const SortResult& result, const SortParams& params)
    : firstArray(first), secondArray(second), sortResult(result), sortParams(params) {
    std::string arrayFolderPath = (ARRAY_FOLDER).string();
    if (!fs::exists(arrayFolderPath)) {
        fs::create_directories(arrayFolderPath);
    }
}

void SortData::setFirst(const SortableArray& arr) {
    firstArray = arr;
}

void SortData::setSecond(const SortableArray& arr) {
    secondArray = arr;
}

const SortableArray& SortData::getFirst() const {
    return firstArray;
}

const SortableArray& SortData::getSecond() const {
    return secondArray;
}

void SortData::setSortResult(const SortResult& result) {
    sortResult = result;
}

const SortResult& SortData::getSortResult() const {
    return sortResult;
}

void SortData::setSortParams(const SortParams& params) {
    sortParams = params;
}

const SortParams& SortData::getSortParams() const {
    return sortParams;
}

std::string SortData::getFileName() const {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    struct tm tm_now;
    localtime_s(&tm_now, &now_c);
    ss << "array"
        << std::put_time(&tm_now, "%Y%m%d_%H%M%S")
        << ".json";

    return ss.str();
}

std::string SortData::getFullName(std::string& fileName) const {
    return (ARRAY_FOLDER / fileName).string();
}

json SortData::toJson() const {
    json j;
    j["firstArray"] = firstArray.toJson();
    j["secondArray"] = secondArray.toJson();
    j["sortResult"] = json{
        {"elapsedTimeMs", sortResult.elapsedTimeMs.count()},
        {"comparisons", sortResult.comparisons},
        {"swaps", sortResult.swaps}
    };
    j["sortParams"] = json{
        {"N", sortParams.N},
        {"A", sortParams.A},
        {"C", sortParams.C}
    };
    return j;
}

void SortData::fromJson(const json& j) {
    if (j.contains("firstArray")) {
        firstArray.fromJson(j["firstArray"]);
    }
    else {
        firstArray.clearData();
        std::cerr << "Warning: JSON does not contain 'firstArray' key.\n";
    }

    if (j.contains("secondArray")) {
        secondArray.fromJson(j["secondArray"]);
    }
    else {
        secondArray.clearData();
        std::cerr << "Warning: JSON does not contain 'secondArray' key.\n";
    }

    if (j.contains("sortResult")) {
        const auto& sr = j["sortResult"];
        if (sr.contains("elapsedTimeMs") && sr.contains("comparisons") && sr.contains("swaps")) {
            sortResult.elapsedTimeMs = std::chrono::duration<double, std::milli>(sr["elapsedTimeMs"].get<double>());
            sortResult.comparisons = sr["comparisons"].get<long long>();
            sortResult.swaps = sr["swaps"].get<long long>();
        }
        else {
            sortResult = SortResult{};
            std::cerr << "Warning: JSON 'sortResult' missing some keys.\n";
        }
    }
    else {
        sortResult = SortResult{};
        std::cerr << "Warning: JSON does not contain 'sortResult' key.\n";
    }

    if (j.contains("sortParams")) {
        const auto& sp = j["sortParams"];
        if (sp.contains("N") && sp.contains("A") && sp.contains("C")) {
            sortParams.N = sp.value("N", 0LL);
            sortParams.A = sp.value("A", 0.0);
            sortParams.C = sp.value("C", 0.0);
        }
        else {
            sortParams = SortParams{};
            std::cerr << "Warning: JSON 'sortResult' missing some keys.\n";
        }
    }
    else {
        sortParams = SortParams{};
        std::cerr << "Warning: JSON does not contain 'sortParams' key.\n";
    }
}