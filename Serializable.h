#pragma once
#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include "Serializator.h"

/**
    \brief Класс для сериализации и сохранения

    Данный класс предоставляет функционал для сериализации и сохранения сериализованных объектов.
*/
class Serializable : public Serializator {
public:
    virtual ~Serializable() = default;

    /**
        \brief Функция преобразования объекта класса в JSON и сохранения его в файл

        \param [in] filename имя файла

        \return Результат операции
    */
    bool saveJSON(const std::string& filename) const;

    /**
        \brief Функция загрузки из файла и преобразования JSON в объект класса

        \param [in] filename имя файла

        \return Результат операции
    */
    bool loadJSON(const std::string& filename);
};

#endif // SERIALIZABLE_H