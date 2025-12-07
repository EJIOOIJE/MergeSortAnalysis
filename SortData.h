#pragma once
#ifndef SORT_DATA_H
#define SORT_DATA_H

#include "SortableArray.h"
#include "SortResult.h"
#include "SortParams.h"
#include <iostream>

/**
    \brief Класс для хранения данных о сортировке

    Данный класс предоставляет функционал для сериализации и сохранения данных о сортировке.
*/
class SortData : public Serializable {
public:
    SortData();

    /**
        \brief Конструктор класса, принимающий изначальный массив чисел, отсортированный массив чисел, характеристики выполнения сортировки, параметры выполнения сортировки

        \param [in] first изначальный массив чисел

        \param [in] second отсортированный массив чисел

        \param [in] result характеристики выполнения сортировки

        \param [in] params параметры выполнения сортировки
    */
    SortData(const SortableArray& first, const SortableArray& second, const SortResult& result, const SortParams& params);

    /**
        \brief Функция устанавливающая изначальный массив чисел

        \param [in] arr изначальный массив чисел
    */
    void setFirst(const SortableArray& arr);

    /**
        \brief Функция устанавливающая отсортированный массив чисел

        \param [in] arr отсортированный массив чисел
    */
    void setSecond(const SortableArray& arr);

    /**
        \brief Функция получения изначального массива чисел

        \return Изначальный массив чисел
    */
    const SortableArray& getFirst() const;

    /**
        \brief Функция получения отсортированного массива чисел

        \return Отсортированный массив чисел
    */
    const SortableArray& getSecond() const;

    /**
        \brief Функция устанавливающая характеристики выполнения сортировки

        \param [in] result характеристики выполнения сортировки
    */
    void setSortResult(const SortResult& result);

    /**
        \brief Функция получения характеристик выполнения сортировки

        \return Характеристики выполнения сортировки
    */
    const SortResult& getSortResult() const;

    /**
        \brief Функция устанавливающая параметры выполнения сортировки

        \param [in] params параметры выполнения сортировки
    */
    void setSortParams(const SortParams& params);

    /**
        \brief Функция получения параметров выполнения сортировки

        \return Параметры выполнения сортировки
    */
    const SortParams& getSortParams() const;

    /**
        \brief Функция получения имени файла для сохранения

        \return Имя файла
    */
    std::string getFileName() const;

    /**
        \brief Функция получения полного пути к файлу для сохранения

        \param [in] fileName имя файла

        \return Путь к файлу
    */
    std::string getFullName(std::string& fileName) const;

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
    SortableArray firstArray;
    SortableArray secondArray;
    SortResult sortResult;
    SortParams sortParams;
};

#endif // SORT_DATA_H