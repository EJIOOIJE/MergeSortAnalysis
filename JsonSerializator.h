#pragma once
#ifndef JSON_SERIALIZATOR_H
#define JSON_SERIALIZATOR_H

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

/**
    \brief Интерфейс для JSON сериализации 

    Данный интерфейс предоставляет функционал для сериализации используя JSON.
*/
class JsonSerializator {
public:
    virtual ~JsonSerializator() = default;

    /**
        \brief Функция преобразования объекта класса в JSON

        \return Объект класса, преобразованный в JSON
    */
    virtual json toJson() const = 0;

    /**
        \brief Функция преобразования JSON в объект класса

        \param [in] j JSON

        \return Объект класса, восстановленный в JSON
    */
    virtual void fromJson(const json& j) = 0;
};

#endif // JSON_SERIALIZATOR_H