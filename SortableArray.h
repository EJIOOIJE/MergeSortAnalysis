#pragma once
#ifndef SORTABLE_ARRAY_H
#define SORTABLE_ARRAY_H

#include "Serializable.h"
#include <vector>

/**
    \brief Класс для хранения массива чисел

    Данный класс предоставляет функционал для сериализации и сохранения массива чисел.
*/
class SortableArray : public Serializable {
public:
    SortableArray();

    /**
        \brief Функция очищающая массив чисел
    */
    void clearData();

    /**
        \brief Функция копирования данных

        \return Скопированный объект класса
    */
    virtual SortableArray* clone() const;

    /**
        \brief Конструктор класса, принимающий массив чисел

        \param [in] data массив чисел
    */
    explicit SortableArray(const std::vector<double>& data);

    /**
        \brief Функция получения данных

        \return Массив чисел
    */
    const std::vector<double>& getData() const;

    /**
        \brief Функция устанавливающая массив чисел

        \param [in] data массив чисел
    */
    void setData(const std::vector<double>& data);

    /**
        \brief Функция преобразования объекта класса в JSON

        \return Объект класса, преобразованный в JSON
    */
    json toJson() const override;

    /**
        \brief Функция преобразования JSON в объект класса

        \param [in] j JSON

        \return Объект класса, восстановленный в JSON
    */
    void fromJson(const json& j) override;

private:
    std::vector<double> data;
};

#endif // SORTABLE_ARRAY_H