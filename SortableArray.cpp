#include "SortableArray.h"

SortableArray::SortableArray() = default;

SortableArray::SortableArray(const std::vector<double>& data)
    : data(data) {
}

void SortableArray::clearData() {
    data.clear();
}

SortableArray* SortableArray::clone() const {
    auto* newObj = new SortableArray();
    newObj->setData(this->data);
    return newObj;
}

const std::vector<double>& SortableArray::getData() const {
    return data;
}

void SortableArray::setData(const std::vector<double>& data) {
    this->data = data;
}

json SortableArray::toJson() const {
    json j;
    j["data"] = data;
    return j;
}

void SortableArray::fromJson(const json& j) {
    if (j.contains("data") && j["data"].is_array()) {
        data = j["data"].get<std::vector<double>>();
    }
    else {
        data.clear();
    }
}